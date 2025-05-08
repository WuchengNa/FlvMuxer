cmake_minimum_required(VERSION 3.15)

project(FlvPacker)

#preset some define
set(OUTPUT_DIR ${CMAKE_SOURCE_DIR}/output)
message("Current project name: ${PROJECT_NAME}")
message("Current Platform is ${CMAKE_SYSTEM_NAME}")

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

#include
include_directories(${CMAKE_SOURCE_DIR}/include)

#src file
file(GLOB IMPL_SRC ${CMAKE_SOURCE_DIR}/src/impl/*.cpp)
list(APPEND SRC_FILE ${IMPL_SRC})

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

#set link dir,must before add_executable()
link_directories(${CMAKE_SOURCE_DIR}/3rd/lib/${PLF_DIR})

add_library(${PROJECT_NAME} ${SRC_FILE})

#def
if(BUILD_SHARED_LIBS)
    message("Build shared libs, turn on FLVSDK_EXPORT")
    target_compile_definitions(${PROJECT_NAME} PRIVATE FLVSDK_EXPORT)
endif()
#set vs src group
if(PLF_WINDOWS)
    source_group("src\\impl" FILES ${IMPL_SRC})
endif()

#set /MTd or /MT
if(PLF_WINDOWS)
    message("set msvc property, for /MT or /MTD")
    set_property(TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

#do something after build
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMENT "Copying ... $<TARGET_FILE:${PROJECT_NAME}>"
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}> ${OUTPUT_DIR}/${PLF_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE_DIR:${PROJECT_NAME}>/${PROJECT_NAME}.lib ${OUTPUT_DIR}/${PLF_DIR}
)