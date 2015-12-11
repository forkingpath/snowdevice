cmake_minimum_required(VERSION 2.8.4)
project(snowdevice)

set(WIN32)

math(EXPR BITNESS "8*${CMAKE_SIZEOF_VOID_P}")
# assume 32bit windows

# Common flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
if(WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -mwindows")
else()
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")
endif()

set(SOURCE_FILES ./src/start.cpp
        ./extern/BearLibTerminal/Include/C/BearLibTerminal.h)

include_directories(${CMAKE_SOURCE_DIR}/extern/BearLibTerminal/Include/C)

add_executable(snowdevice ${SOURCE_FILES})
if(WIN32)
    target_link_libraries(snowdevice winmm.lib)
endif()

set(OUTPUT_DIR ${CMAKE_SOURCE_DIR}/Output/${CMAKE_SYSTEM_NAME}${BITNESS})
set_target_properties(snowdevice PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})