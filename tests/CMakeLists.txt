cmake_minimum_required(VERSION 3.14)
project(test_set)

file(GLOB SOURCES "**/*.cpp")

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


add_executable(${PROJECT_NAME} ${SOURCES} ${SETLIB_HEADERS})
target_include_directories(${PROJECT_NAME} PUBLIC ${SETLIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} cpp_course_hw gtest_main)