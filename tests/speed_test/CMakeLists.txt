cmake_minimum_required(VERSION 3.14)
project(speed_test)

file(GLOB SOURCES "*.cpp")

find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES} ${SETLIB_HEADERS})
target_include_directories(${PROJECT_NAME} PUBLIC ${SETLIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} cpp_course_hw gtest_main)