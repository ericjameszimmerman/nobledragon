# CMake minimum version
cmake_minimum_required (VERSION 3.13)

set (TEST_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

set(CMAKE_SYSTEM_NAME Generic)

# Perform compiler test without linker, since we're cross-compiling
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# Project Infomation
set(prj lpc_chip_175x_6x)
project(${prj})

enable_language(ASM)
enable_language(C)

# STDLIB
set (CMAKE_SHARED_LIBRARY_LINK_C_FLAGS)

add_library(${prj} STATIC
  ../../../third-party/lpcopen/chips/lpc_chip/chip_17xx_40xx/adc_17xx_40xx.c
  ../../../third-party/lpcopen/chips/lpc_chip/chip_17xx_40xx/can_17xx_40xx.c
  ../../../third-party/lpcopen/chips/lpc_chip/chip_17xx_40xx/chip_17xx_40xx.c
  ../../../third-party/lpcopen/chips/lpc_chip/chip_17xx_40xx/clock_17xx_40xx.c
  ../../../third-party/lpcopen/chips/lpc_chip/chip_17xx_40xx/dac_17xx_40xx.c
  ../../../third-party/lpcopen/chips/lpc_chip/chip_17xx_40xx/enet_17xx_40xx.c
  ../../../third-party/lpcopen/chips/lpc_chip/chip_17xx_40xx/gpdma_17xx_40xx.c
  ../../../third-party/lpcopen/chips/lpc_chip/chip_17xx_40xx/gpio_17xx_40xx.c
  ../../../third-party/lpcopen/chips/lpc_chip/chip_17xx_40xx/i2c_17xx_40xx.c
  ../../../third-party/lpcopen/chips/lpc_chip/chip_common/iap.c
  ../../../third-party/lpcopen/chips/lpc_chip/chip_17xx_40xx/iocon_17xx_40xx.c
  ../../../third-party/lpcopen/chips/lpc_chip/chip_17xx_40xx/pmu_17xx_40xx.c
  ../../../third-party/lpcopen/chips/lpc_chip/chip_common/ring_buffer.c
  ../../../third-party/lpcopen/chips/lpc_chip/chip_17xx_40xx/ritimer_17xx_40xx.c
  ../../../third-party/lpcopen/chips/lpc_chip/chip_17xx_40xx/rtc_17xx_40xx.c
  ../../../third-party/lpcopen/chips/lpc_chip/chip_17xx_40xx/spi_17xx_40xx.c
  ../../../third-party/lpcopen/chips/lpc_chip/chip_17xx_40xx/ssp_17xx_40xx.c
  ../../../third-party/lpcopen/chips/lpc_chip/chip_17xx_40xx/stopwatch_17xx_40xx.c
  ../../../third-party/lpcopen/chips/lpc_chip/chip_17xx_40xx/sysctl_17xx_40xx.c
  ../../../third-party/lpcopen/chips/lpc_chip/chip_17xx_40xx/sysinit_17xx_40xx.c
  ../../../third-party/lpcopen/chips/lpc_chip/chip_17xx_40xx/timer_17xx_40xx.c
  ../../../third-party/lpcopen/chips/lpc_chip/chip_17xx_40xx/uart_17xx_40xx.c
  ../../../third-party/lpcopen/chips/lpc_chip/chip_17xx_40xx/wwdt_17xx_40xx.c
)

target_include_directories(${prj}
  PUBLIC include
  PRIVATE .
  PRIVATE ../../../third-party/lpcopen/chips/lpc_chip/chip_17xx_40xx/config_175x_6x/
  PRIVATE ../../../third-party/lpcopen/chips/lpc_chip/chip_common/
  PRIVATE ../../../third-party/lpcopen/chips/lpc_chip/chip_17xx_40xx/
  PRIVATE ../../../third-party/CMSIS/Include/
)

# Link the library to the target
#target_link_libraries (${prj})
