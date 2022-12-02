cmake_minimum_required(VERSION 3.16.3)
project(test_set)

file(GLOB SOURCES "speed_test.cpp")

find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES} ${SETLIB_HEADERS})
target_include_directories(${PROJECT_NAME} PUBLIC ${SETLIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} GTest::GTest gtest_main pthread)