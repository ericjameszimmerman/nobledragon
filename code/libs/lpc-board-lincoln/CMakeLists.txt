# CMake minimum version
cmake_minimum_required (VERSION 3.13)
set (TEST_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)
set (LIB_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../../output)

#add_custom_target(test-output-directory ALL 
#                   COMMAND ${CMAKE_COMMAND} -E make_directory ${TEST_OUTPUT_DIRECTORY})

#add_custom_target(lib-output-directory ALL 
#                   COMMAND ${CMAKE_COMMAND} -E make_directory ${LIB_OUTPUT_DIRECTORY})

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
  ../../app/shared/Boards/lpc_board/boards_17xx/lpc_board_lincoln/board.c
  ../../app/shared/Boards/lpc_board/boards_17xx/lpc_board_lincoln/board_sysinit.c
  ../../app/shared/Boards/lpc_board/boards_17xx/lpc_board_lincoln/lpc_phy_ksz80xx.c
)

target_include_directories(${prj}
  PUBLIC include
  PRIVATE .
  PRIVATE ../../app/shared/Chips/lpc_chip/chip_17xx_40xx/config_175x_6x/
  PRIVATE ../../app/shared/Chips/lpc_chip/chip_common/
  PRIVATE ../../app/shared/Chips/lpc_chip/chip_17xx_40xx/
  PRIVATE ../../app/shared/Boards/lpc_board/board_common/
  PRIVATE ../../app/shared/CMSIS/CMSIS/Include/
)


# Link the library to the target
#target_link_libraries (${prj})

#add_custom_command(TARGET ${prj} 
#                   POST_BUILD
#                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${prj}> ${TEST_OUTPUT_DIRECTORY})

#add_custom_command(TARGET ${prj} 
#                   POST_BUILD
#                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${prj}> ${LIB_OUTPUT_DIRECTORY})
