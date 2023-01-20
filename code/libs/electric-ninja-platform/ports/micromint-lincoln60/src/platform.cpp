#include "electricninjaplatform/platform.h"
#include <stdio.h>
#include <stdarg.h>
#include <errno.h>
#include "electricninjaplatform/platformInternal.h"

namespace platform {

typedef void (*Vector)(void);
Vector ResetVector = 0x00000000;
xTimerHandle xOneSecondTimer = NULL;

void initialize()
{
  SystemCoreClockUpdate();
  Board_Init();
}

void start()
{
  vTaskStartScheduler();
}

void reboot()
{
  (*ResetVector)();
}

void blockPreemption()
{
  vTaskSuspendAll();
}

void resumePreemption()
{
  xTaskResumeAll();
}

void delay(size_t ticks)
{
  vTaskDelay(ticks);
}

int msleep(unsigned int milliseconds)
{
  xTickType xDelayTime = milliseconds / portTICK_RATE_MS;
  vTaskDelay(xDelayTime);
}

unsigned int sleep(unsigned int seconds)
{
  xTickType xDelayTime = (seconds * 1000) / portTICK_RATE_MS;
}

void disableInterrupts()
{
  taskDISABLE_INTERRUPTS();
}

void enableInterrupts()
{
  taskENABLE_INTERRUPTS();
}

void enterCriticalSection()
{
  taskENTER_CRITICAL();
}

void leaveCriticalSection()
{
  taskEXIT_CRITICAL();
}

} // namespace platform