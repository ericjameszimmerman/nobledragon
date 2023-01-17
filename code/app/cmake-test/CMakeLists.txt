# CMake minimum version
cmake_minimum_required (VERSION 3.13)

set (LIB_SRC_DIRECTORY ${CMAKE_BINARY_DIR}/../../../libs)
set (LIB_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../../../libs/output)

set(CMAKE_SYSTEM_NAME Generic)

# Perform compiler test without linker, since we're cross-compiling
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# Project Information
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
  ../../third-party/startup_code/sysinit.c
  ../../third-party/freertos/freertos/Source/croutine.c
  ../../third-party/freertos/freertos/Source/portable/MemMang/heap_3.c
  ../../third-party/freertos/freertos/Source/list.c
  ../../third-party/freertos/freertos/Source/queue.c
  ../../third-party/freertos/freertos/Source/tasks.c
  ../../third-party/freertos/freertos/Source/timers.c
  ../../third-party/freertos/freertos/Source/portable/gcc/ARM_CM3/port.c
  ../../third-party/lwip/lpclwip/arch/lpc17xx_40xx_emac.c
  ../../third-party/lwip/lpclwip/arch/lpc17xx_40xx_systick_arch.c
  ../../third-party/lwip/lpclwip/arch/lpc_debug.c
  ../../third-party/lwip/lwip/src/api/netbuf.c
  ../../third-party/lwip/lpclwip/arch/sys_arch_freertos.c
  ../../third-party/lwip/lwip/src/api/api_lib.c
  ../../third-party/lwip/lwip/src/api/api_msg.c
  ../../third-party/lwip/lwip/src/core/ipv4/autoip.c
  ../../third-party/lwip/lwip/src/core/def.c
  ../../third-party/lwip/lwip/src/core/dhcp.c
  ../../third-party/lwip/lwip/src/core/dns.c
  ../../third-party/lwip/lwip/src/api/err.c
  ../../third-party/lwip/lwip/src/netif/etharp.c
  ../../third-party/lwip/lwip/src/core/ipv4/icmp.c
  ../../third-party/lwip/lwip/src/core/ipv4/igmp.c
  ../../third-party/lwip/lwip/src/core/ipv4/inet.c
  ../../third-party/lwip/lwip/src/core/ipv4/inet_chksum.c
  ../../third-party/lwip/lwip/src/core/init.c
  ../../third-party/lwip/lwip/src/core/ipv4/ip.c
  ../../third-party/lwip/lwip/src/core/ipv4/ip_addr.c
  ../../third-party/lwip/lwip/src/core/ipv4/ip_frag.c
  ../../third-party/lwip/lwip/src/core/lwiptimers.c
  ../../third-party/lwip/lwip/src/core/mem.c
  ../../third-party/lwip/lwip/src/core/memp.c
  ../../third-party/lwip/lwip/src/api/netdb.c
  ../../third-party/lwip/lwip/src/core/netif.c
  ../../third-party/lwip/lwip/src/api/netifapi.c
  ../../third-party/lwip/lwip/src/core/pbuf.c
  ../../third-party/lwip/lwip/src/core/raw.c
  ../../third-party/lwip/lwip/src/api/sockets.c
  ../../third-party/lwip/lwip/src/core/stats.c
  ../../third-party/lwip/lwip/src/core/sys.c
  ../../third-party/lwip/lwip/src/core/tcp.c
  ../../third-party/lwip/lwip/src/core/tcp_in.c
  ../../third-party/lwip/lwip/src/core/tcp_out.c
  ../../third-party/lwip/lwip/src/api/tcpip.c
  ../../third-party/lwip/lwip/src/core/udp.c
)

target_include_directories(${prj}
  PUBLIC include
  PRIVATE .
  PRIVATE ../../third-party/lpcopen/chips/lpc_chip/chip_17xx_40xx/config_175x_6x/
  PRIVATE ../../third-party/lpcopen/chips/lpc_chip/chip_common/
  PRIVATE ../../third-party/lpcopen/chips/lpc_chip/chip_17xx_40xx/
  PRIVATE ../../third-party/lpcopen/boards/lpc_board/board_common/
  PRIVATE ../../third-party/lpcopen/boards/lpc_board/boards_17xx/nxp_lpcxpresso_1769/
  PRIVATE ../../third-party/lwip/lwip/src/include/
  PRIVATE ../../third-party/lwip/lwip/src/include/ipv4/
  PRIVATE ../../third-party/lwip/contrib/apps/tcpecho/
  PRIVATE ../../third-party/lwip/contrib/apps/tcpecho_raw/
  PRIVATE ../../third-party/lwip/lpclwip/
  PRIVATE ../../third-party/freertos/
  PRIVATE ../../third-party/freertos/freertos/Source/include/
  PRIVATE ../../third-party/freertos/freertos/Source/portable/gcc/ARM_CM3/
  PRIVATE ./configs/
  PRIVATE ../../third-party/CMSIS/Include/
)

add_subdirectory(${LIB_SRC_DIRECTORY}/lpc/lpc-chip-175x-6x libchip/build)
add_subdirectory(${LIB_SRC_DIRECTORY}/lpc/lpc-board-lincoln libboard/build)

# Link the library to the target
target_link_libraries (${prj}
  lpc_chip_175x_6x
  board_lincoln
)
