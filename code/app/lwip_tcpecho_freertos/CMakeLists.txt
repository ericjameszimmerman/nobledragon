cmake_minimum_required(VERSION 3.13)
# Targeting an embedded system, no OS.
set(CMAKE_SYSTEM_NAME Generic)

# Trust user to have cross compiler properly setup
set(CMAKE_C_COMPILER_WORKS TRUE CACHE INTERNAL "")
set(CMAKE_CXX_COMPILER_WORKS TRUE CACHE INTERNAL "")
set(CMAKE_C_ABI_COMPILED TRUE CACHE INTERNAL "")
set(CMAKE_CXX_ABI_COMPILED TRUE CACHE INTERNAL "")

# Perform compiler test without linker, since we're cross-compiling
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(prj lwip_freertos_test1)
project(${prj})

add_executable(${prj}
  lwip_tcpecho_freertos.c
  cr_redlib_heap_fix.c
  tcpecho.c
  ../../libs/electric-ninja-platform/external/lwip/lpclwip/arch/sys_arch_freertos.c)

target_include_directories(${prj}
  PUBLIC include
  PRIVATE .
  PRIVATE ../../electric-ninja-platform/external/lwip/lpclwip/arch/
)
