cmake_minimum_required(VERSION 3.14)
project(tests)

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

add_executable(${PROJECT_NAME} ${SOURCES} ${LIB_HEADERS})
target_include_directories(${PROJECT_NAME} PUBLIC ${LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${LIB_LIBRARIES} ${Boost_LIBRARIES} gtest_main)