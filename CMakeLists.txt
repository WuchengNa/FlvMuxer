cmake_minimum_required(VERSION 3.15)
project(FlvMuxer)

message("Current Platform is ${CMAKE_SYSTEM_NAME}")

#flag
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(BUILD_SHARED_LIBS ON)

message("Current build type is :${CMAKE_BUILD_TYPE}")
if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    add_compile_options(-g)
elseif("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    message("Current build type is Release")
    add_compile_options(-O3)
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    SET(PLF_WINDOWS 1)
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        SET(PLF_DIR  "win/x64")
    else()
        set(PLF_DIR "win/x86")
    endif()
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    SET(PLF_LINUX 1)
    SET(PLF_DIR  linux)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    SET(PLF_MAC 1)
    SET(PLF_DIR mac) 
endif()
message("Current platform dir is ${PLF_DIR}")



add_subdirectory(src sdk)
add_subdirectory(unittest unittest)