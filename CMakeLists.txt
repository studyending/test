SET(so_path "./")

SET(TOOL_CHAIN_DIR "/toolchain/")
SET(CMAKE_SYSTEM_NAME  Linux)
SET(CMAKE_SYSTEM_PROCESSOR arm)
SET(CMAKE_FIND_ROOT_PATH "${TOOL_CHAIN_DIR}")
SET(CMAKE_C_COMPILER  "${TOOL_CHAIN_DIR}/bin/arm-openwrt-linux-gcc")

SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)

cmake_minimum_required(VERSION 2.8)
project(monitor)

add_executable(monitor
        monitor.c
        )


