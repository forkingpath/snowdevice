cmake_minimum_required(VERSION 2.8.4)

project(snowdevice LANGUAGES CXX)

INCLUDE(BundleUtilities)
math(EXPR BITNESS "8*${CMAKE_SIZEOF_VOID_P}")

add_executable(snowdevice
        ${CMAKE_SOURCE_DIR}/src/start.cpp
        )
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -mwindows -m64")
target_include_directories(snowdevice
        PUBLIC ${CMAKE_SOURCE_DIR}/extern/BearLibTerminal/Include/C
        )
target_link_libraries(snowdevice
        ${CMAKE_SOURCE_DIR}/extern/BearLibTerminal/Windows64/BearLibTerminal.lib
        winmm.lib
        )
set_property(TARGET snowdevice PROPERTY CXX_STANDARD 11)
set_property(TARGET snowdevice PROPERTY CXX_STANDARD_REQUIRED ON)

set(OUTPUT_DIR ${CMAKE_SOURCE_DIR}/Output/${CMAKE_SYSTEM_NAME}${BITNESS})
set_target_properties(snowdevice PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})
