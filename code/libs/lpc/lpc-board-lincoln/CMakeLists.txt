# CMake minimum version
cmake_minimum_required (VERSION 3.13)
set (TEST_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

set(CMAKE_SYSTEM_NAME Generic)

# Perform compiler test without linker, since we're cross-compiling
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# Project Infomation
set(prj board_lincoln)
project(${prj})

enable_language(ASM)
enable_language(C)

# STDLIB
set (CMAKE_SHARED_LIBRARY_LINK_C_FLAGS)

add_library(${prj} STATIC
  ../../../third-party/lpcopen/boards/lpc_board/boards_17xx/lpc_board_lincoln/board.c
  ../../../third-party/lpcopen/boards/lpc_board/boards_17xx/lpc_board_lincoln/board_sysinit.c
  ../../../third-party/lpcopen/boards/lpc_board/boards_17xx/lpc_board_lincoln/lpc_phy_ksz80xx.c
)

target_include_directories(${prj}
  PUBLIC include
  PRIVATE .
  PRIVATE ../../../third-party/lpcopen/chips/lpc_chip/chip_17xx_40xx/config_175x_6x/
  PRIVATE ../../../third-party/lpcopen/chips/lpc_chip/chip_common/
  PRIVATE ../../../third-party/lpcopen/chips/lpc_chip/chip_17xx_40xx/
  PRIVATE ../../../third-party/lpcopen/boards/lpc_board/board_common/
  PRIVATE ../../../third-party/CMSIS/Include/
)

# Link the library to the target
target_link_libraries (${prj}
  lpc_chip_175x_6x
)
