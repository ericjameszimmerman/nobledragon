/*
    The purpose of this example is to evaluate the idle task for a quick and
    dirty Idle% calculation debug tool.

NOTE: If you add commands into the Idle task, it will affect the maximum attainable
      count.. The goal is to have this section the same as the actual program
      and record a baseline.

NOTE: For whateever reason, if I don't launch the Ethernet thread, less idle
      time is available... not sure why at this time.
 */

#include "board.h"
#include "arch\lpc17xx_40xx_emac.h"
#include "arch\lpc_arch.h"
#include "arch\sys_arch.h"

#include "lwip/init.h"
#include "lwip/opt.h"
#include "lwip/sys.h"
#include "lwip/memp.h"
#include "lwip/tcpip.h"
#include "lwip/ip_addr.h"
#include "lwip/netif.h"
#include "lwip/lwiptimers.h"
#include "netif/etharp.h"

#if LWIP_DHCP
#include "lwip/dhcp.h"
#endif

#include "lpc_phy.h"/* For the PHY monitor support */

void vOneSecondTimerCallback( xTimerHandle pxTimer );

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/* NETIF data */
static struct netif lpc_netif;
volatile int g_IdleCount = 0;
int g_MaxIdleCount = 0;
int g_MinIdleCount = 0xffffff;
int g_NumCallbacks = 0;
volatile int g_IdleReset = 0;

xTimerHandle xOneSecondTimer = NULL;

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/* Sets up system hardware */
static void prvSetupHardware(void)
{
	SystemCoreClockUpdate();
	Board_Init();

	/* LED0 is used for the link status, on = PHY cable detected */
	/* Initial LED state is off to show an unconnected cable state */
	Board_LED_Set(0, false);
}

/* Callback for TCPIP thread to indicate TCPIP init is done */
static void tcpip_init_done_signal(void *arg)
{
	/* Tell main thread TCP/IP init is done */
	*(s32_t *) arg = 1;
}

/* LWIP kickoff and PHY link monitor thread */
static void vSetupIFTask (void *pvParameters) {
	ip_addr_t ipaddr, netmask, gw;
	volatile s32_t tcpipdone = 0;
	uint32_t physts;
	static int prt_ip = 0;

	/* Wait until the TCP/IP thread is finished before
	   continuing or wierd things may happen */
	LWIP_DEBUGF(LWIP_DBG_ON, ("Waiting for TCPIP thread to initialize...\n"));
	tcpip_init(tcpip_init_done_signal, (void *) &tcpipdone);
	while (!tcpipdone) {
		msDelay(1);
	}

	LWIP_DEBUGF(LWIP_DBG_ON, ("Starting LWIP TCP echo server...\n"));

	/* Static IP assignment */
#if LWIP_DHCP
	IP4_ADDR(&gw, 0, 0, 0, 0);
	IP4_ADDR(&ipaddr, 0, 0, 0, 0);
	IP4_ADDR(&netmask, 0, 0, 0, 0);
#else
	IP4_ADDR(&gw, 192, 168, 1, 1);
	IP4_ADDR(&ipaddr, 192, 168, 1, 6);
	IP4_ADDR(&netmask, 255, 255, 255, 0);
#endif

	/* Add netif interface for lpc17xx_8x */
	if (!netif_add(&lpc_netif, &ipaddr, &netmask, &gw, NULL, lpc_enetif_init,
				   tcpip_input)) {
		LWIP_ASSERT("Net interface failed to initialize\r\n", 0);
	}
	netif_set_default(&lpc_netif);
	netif_set_up(&lpc_netif);

	/* Enable MAC interrupts only after LWIP is ready */
	NVIC_SetPriority(ETHERNET_IRQn, config_ETHERNET_INTERRUPT_PRIORITY);
	NVIC_EnableIRQ(ETHERNET_IRQn);

#if LWIP_DHCP
	dhcp_start(&lpc_netif);
#endif

	// Do nothing in this example
	while (1) 
    {
		vTaskDelay(configTICK_RATE_HZ / 4);
	}
}

/* LED1 toggle thread */
static void vLEDTask1(void *pvParameters) {
	bool LedState = false;

	while (1) {
		Board_LED_Set(0, LedState);
		LedState = (bool) !LedState;

		/* About a 3Hz on/off toggle rate */
		vTaskDelay(configTICK_RATE_HZ / 6);
	}
}

/* LED2 toggle thread */
static void vLEDTask2(void *pvParameters) {
	bool LedState = false;

	while (1) {
		Board_LED_Set(1, LedState);
		LedState = (bool) !LedState;

		/* About a 7Hz on/off toggle rate */
		vTaskDelay(configTICK_RATE_HZ / 14);
	}
}

int g_dataarray[105];

void vOneSecondTimerCallback( xTimerHandle pxTimer )
{
    // The timer expired, therefore 1 seconds must have passed
    int idleCount;
    
    idleCount = g_IdleCount;
    g_IdleReset = 1;
    
    g_dataarray[g_NumCallbacks] = idleCount;
    
    g_NumCallbacks++;
    
    if (g_NumCallbacks > 10)
    {
        if (idleCount > g_MaxIdleCount)
        {
            g_MaxIdleCount = idleCount;
        }
        
        if (idleCount < g_MinIdleCount)
        {
            g_MinIdleCount = idleCount;
        }
    }
    
    if (g_NumCallbacks > 100)
    {
        for (int i = 0; i < g_NumCallbacks; i++)
        {
            DEBUGOUT("%d\r\n", g_dataarray[i]);
        }
        
        g_IdleCount = 0;
        g_NumCallbacks = 0;
    }
    
    
}

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/**
 * @brief	MilliSecond delay function based on FreeRTOS
 * @param	ms	: Number of milliSeconds to delay
 * @return	Nothing
 * Needed for some functions, do not use prior to FreeRTOS running
 */
void msDelay(uint32_t ms)
{
	vTaskDelay((configTICK_RATE_HZ * ms) / 1000);
}

/**
 * @brief	main routine for example_lwip_tcpecho_freertos_17xx40xx
 * @return	Function should not exit
 */
int main(void)
{
	prvSetupHardware();

     // Create then start the one-shot timer that is responsible for turning
     // the back-light off if no keys are pressed within a 5 second period.
     xOneSecondTimer = xTimerCreate( "OneSecondTimer",           // Just a text name, not used by the kernel.
                                     ( 1000 / portTICK_RATE_MS), // The timer period in ticks.
                                     pdTRUE,                     // The timer is a one-shot timer.
                                     0,                          // The id is not used by the callback so can take any value.
                                     vOneSecondTimerCallback     // The callback function that switches the LCD back-light off.
                                   );
     
     xTimerStart(xOneSecondTimer, 0);
     
	/* Add another thread for initializing physical interface. This
	   is delayed from the main LWIP initialization. */
	xTaskCreate(vSetupIFTask, (signed char *) "SetupIFx",
				configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
				(xTaskHandle *) NULL);

    /* LED1 toggle thread */
	//xTaskCreate(vLEDTask1, (signed char *) "vTaskLed1",
	//			configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
	//			(xTaskHandle *) NULL);

	/* LED2 toggle thread */
	//xTaskCreate(vLEDTask2, (signed char *) "vTaskLed2",
	//			configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
	//			(xTaskHandle *) NULL);
    
	/* Start the scheduler */
	vTaskStartScheduler();

	/* Should never arrive here */
	return 1;
}

/**
 * @}
 */
