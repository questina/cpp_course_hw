cmake_minimum_required(VERSION 3.16.3)
project(cpp_course_hw)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wpedantic -Wall -Wextra -Werror")

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

add_executable(${PROJECT_NAME}
        Matrix.cpp
)

add_custom_target(tests)
add_subdirectory(tests)