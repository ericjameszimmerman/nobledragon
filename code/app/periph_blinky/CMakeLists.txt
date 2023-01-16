cmake_minimum_required(VERSION 3.13)
set(prj lwip_freertos_test1)
project(${prj})

add_executable(${prj}
               lwip_tcpecho_freertos.c)