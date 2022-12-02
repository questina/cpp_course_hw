cmake_minimum_required(VERSION 3.16.3)
project(cpp_course_hw)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g --coverage -O0 -Werror -Wall")

set(SETLIB_INCLUDE_DIRS ${SETLIB_INCLUDE_DIRS} ${CMAKE_HOME_DIRECTORY}/include/)
set(SETLIB_HEADERS ${SETLIB_HEADERS} ${CMAKE_HOME_DIRECTORY}/include/Set.hpp)

include(FetchContent)

include_directories(.)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG main
)

FetchContent_Declare(
        googlebenchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG v1.5.2
)

FetchContent_MakeAvailable(
        googletest
        googlebenchmark
)

add_library(${PROJECT_NAME} STATIC ${SETLIB_HEADERS})
set_target_properties(cpp_course_hw PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(${PROJECT_NAME} PUBLIC ${SETLIB_INCLUDE_DIRS})
add_subdirectory(tests)
