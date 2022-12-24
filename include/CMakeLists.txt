cmake_minimum_required(VERSION 3.0.0)
project(lib)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-arcs -ftest-coverage -fPIC -O0")

find_package(Boost 1.80.0)
include_directories(${Boost_INCLUDE_DIR})

if(NOT Boost_FOUND)
    message(FATAL_ERROR "Could not find boost!")
endif()

file(GLOB SOURCES *.cpp)
file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})

add_library(${PROJECT_NAME} ${SOURCES})

set(LIB_LIBRARIES ${PROJECT_NAME} PARENT_SCOPE)
set(LIB_INCLUDE_DIRS ${INCLUDE_DIRS} PARENT_SCOPE)

