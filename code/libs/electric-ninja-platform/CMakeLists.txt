# CMake minimum version
cmake_minimum_required (VERSION 3.13)

set (LIB_SRC_DIRECTORY ${CMAKE_BINARY_DIR}/../../../libs)
set (LIB_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../../../libs/output)

set(CMAKE_SYSTEM_NAME Generic)

# Perform compiler test without linker, since we're cross-compiling
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# Project Information
set(prj electricninjaplatform)
project(${prj})

option(PORT "choose which port to build" ON)
option(BUILD_TESTS "Run unit tests" OFF)

enable_language(ASM)
enable_language(C)
enable_language(CXX)

# STDLIB
set (CMAKE_SHARED_LIBRARY_LINK_C_FLAGS)

# -----------------------------------------------------------------------------
# Determine which port will be built
# -----------------------------------------------------------------------------
SET(ALL_PORTS micromint-lincoln60)

LIST(FIND ALL_PORTS ${PORT} RET)
IF (${RET} EQUAL -1)
    MESSAGE(FATAL_ERROR "Please choose which port to build (one of ${ALL_PORTS})")
ENDIF ()

STRING(TOLOWER ${PORT} PLATFORM_PORT_DIR)

if (PORT STREQUAL "micromint-lincoln60")
  set(portSOURCE
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

    set(portPrivateINCLUDES
      ../../third-party/lpcopen/chips/lpc_chip/chip_17xx_40xx/config_175x_6x/
      ../../third-party/lpcopen/chips/lpc_chip/chip_common/
      ../../third-party/lpcopen/chips/lpc_chip/chip_17xx_40xx/
      ../../third-party/lpcopen/boards/lpc_board/board_common/
      ../../third-party/lpcopen/boards/lpc_board/boards_17xx/nxp_lpcxpresso_1769/
      ../../third-party/lwip/lwip/src/include/
      ../../third-party/lwip/lwip/src/include/ipv4/
      ../../third-party/lwip/contrib/apps/tcpecho/
      ../../third-party/lwip/contrib/apps/tcpecho_raw/
      ../../third-party/lwip/lpclwip/
      ../../third-party/freertos/
      ../../third-party/freertos/freertos/Source/include/
      ../../third-party/freertos/freertos/Source/portable/gcc/ARM_CM3/
      ../../third-party/CMSIS/Include/
    )
endif()

# Add common source files... all ports must have these
set(electricninjaplatformSOURCE
    ports/${PLATFORM_PORT_DIR}/src/platform.cpp
    ports/${PLATFORM_PORT_DIR}/src/hardFaultHandler.c
    ${portSOURCE}
)

# Create target and set properties
add_library(${prj} STATIC
            ${electricninjaplatformSOURCE})

target_include_directories(${prj}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/ports/${PLATFORM_PORT_DIR}/include>
  PRIVATE
    src/include-private
    ports/${PLATFORM_PORT_DIR}/include-private
    ${portPrivateINCLUDES}
)

if (PORT STREQUAL "micromint-lincoln60")
  add_subdirectory(${LIB_SRC_DIRECTORY}/lpc/lpc-chip-175x-6x libchip/build)
  add_subdirectory(${LIB_SRC_DIRECTORY}/lpc/lpc-board-lincoln libboard/build)

  # Link the library to the target
  target_link_libraries (${prj}
    lpc_chip_175x_6x
    board_lincoln
  )
endif()
