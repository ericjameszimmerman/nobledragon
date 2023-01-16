# CMake minimum version
cmake_minimum_required (VERSION 3.13)


set(CMAKE_SYSTEM_NAME Generic)

# Trust user to have cross compiler properly setup
#set(CMAKE_C_COMPILER_WORKS TRUE CACHE INTERNAL "")
#set(CMAKE_CXX_COMPILER_WORKS TRUE CACHE INTERNAL "")
#set(CMAKE_C_ABI_COMPILED TRUE CACHE INTERNAL "")
#set(CMAKE_CXX_ABI_COMPILED TRUE CACHE INTERNAL "")

# Perform compiler test without linker, since we're cross-compiling
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# Project Infomation
set(prj lwip_freertos_test1)
project(${prj})

enable_language(ASM)
enable_language(C)

# STDLIB
set (CMAKE_SHARED_LIBRARY_LINK_C_FLAGS)

add_executable(${prj}
  freertos_idletest.c
  HardFaultHandler.c
  freertos_hooks.c
  ../shared/startup_code/sysinit.c
  ../shared/freertos/freertos/Source/croutine.c
  ../shared/freertos/freertos/Source/portable/MemMang/heap_3.c
  ../shared/freertos/freertos/Source/list.c
  ../shared/freertos/freertos/Source/queue.c
  ../shared/freertos/freertos/Source/tasks.c
  ../shared/freertos/freertos/Source/timers.c
  ../shared/freertos/freertos/Source/portable/IAR/ARM_CM3/port.c
  ../shared/lwip/lpclwip/arch/lpc17xx_40xx_emac.c
  ../shared/lwip/lpclwip/arch/lpc17xx_40xx_systick_arch.c
  ../shared/lwip/lpclwip/arch/lpc_debug.c
  ../shared/lwip/lwip/src/api/netbuf.c
  ../shared/lwip/lpclwip/arch/sys_arch_freertos.c
  ../shared/lwip/lwip/src/api/api_lib.c
  ../shared/lwip/lwip/src/api/api_msg.c
  ../shared/lwip/lwip/src/core/ipv4/autoip.c
  ../shared/lwip/lwip/src/core/def.c
  ../shared/lwip/lwip/src/core/dhcp.c
  ../shared/lwip/lwip/src/core/dns.c
  ../shared/lwip/lwip/src/api/err.c
  ../shared/lwip/lwip/src/netif/etharp.c
  ../shared/lwip/lwip/src/core/ipv4/icmp.c
  ../shared/lwip/lwip/src/core/ipv4/igmp.c
  ../shared/lwip/lwip/src/core/ipv4/inet.c
  ../shared/lwip/lwip/src/core/ipv4/inet_chksum.c
  ../shared/lwip/lwip/src/core/init.c
  ../shared/lwip/lwip/src/core/ipv4/ip.c
  ../shared/lwip/lwip/src/core/ipv4/ip_addr.c
  ../shared/lwip/lwip/src/core/ipv4/ip_frag.c
  ../shared/lwip/lwip/src/core/lwiptimers.c
  ../shared/lwip/lwip/src/core/mem.c
  ../shared/lwip/lwip/src/core/memp.c
  ../shared/lwip/lwip/src/api/netdb.c
  ../shared/lwip/lwip/src/core/netif.c
  ../shared/lwip/lwip/src/api/netifapi.c
  ../shared/lwip/lwip/src/core/pbuf.c
  ../shared/lwip/lwip/src/core/raw.c
  ../shared/lwip/lwip/src/api/sockets.c
  ../shared/lwip/lwip/src/core/stats.c
  ../shared/lwip/lwip/src/core/sys.c
  ../shared/lwip/lwip/src/core/tcp.c
  ../shared/lwip/lwip/src/core/tcp_in.c
  ../shared/lwip/lwip/src/core/tcp_out.c
  ../shared/lwip/lwip/src/api/tcpip.c
  ../shared/lwip/lwip/src/core/udp.c
)

target_include_directories(${prj}
  PUBLIC include
  PRIVATE .
  PRIVATE ../shared/Chips/lpc_chip/chip_17xx_40xx/config_175x_6x/
  
  PRIVATE ../shared/Chips/lpc_chip/chip_common/
  PRIVATE ../shared/Chips/lpc_chip/chip_17xx_40xx/
  PRIVATE ../shared/Boards/lpc_board/board_common/
  PRIVATE ../shared/Boards/lpc_board/boards_17xx/nxp_lpcxpresso_1769/
  PRIVATE ../shared/lwip/lwip/src/include/
  PRIVATE ../shared/lwip/lwip/src/include/ipv4/
  PRIVATE ../shared/lwip/contrib/apps/tcpecho/
  PRIVATE ../shared/lwip/contrib/apps/tcpecho_raw/
  PRIVATE ../shared/lwip/lpclwip/
  PRIVATE ../shared/freertos/
  PRIVATE ../shared/freertos/freertos/Source/include/
  PRIVATE ../shared/freertos/freertos/Source/portable/RVDS/ARM_CM3/
  PRIVATE ./configs/
  PRIVATE ../shared/CMSIS/CMSIS/Include/
)


# Link the library to the target
target_link_libraries (${prj})
