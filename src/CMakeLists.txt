project(FlvMuxer)

#preset some define
set(OUTPUT_DIR ${CMAKE_SOURCE_DIR}/output)
message("Current project name: ${PROJECT_NAME}")

#include
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/src)

#src file
file(GLOB IMPL_SRC ${CMAKE_SOURCE_DIR}/src/impl/*.cpp)
list(APPEND SRC_FILE ${IMPL_SRC})

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
    source_group("include" FILES ${CMAKE_SOURCE_DIR}/include/*)
    source_group("src\\impl" FILES ${CMAKE_SOURCE_DIR}/src/impl/*)
    source_group("src\\common" FILES ${CMAKE_SOURCE_DIR}/src/common/*)
    source_group("src\\util" FILES ${CMAKE_SOURCE_DIR}/src/util/*)
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