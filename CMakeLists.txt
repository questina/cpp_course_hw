cmake_minimum_required(VERSION 3.0.0)
project(cpp_course_hw)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-g --coverage -O0 -Werror -Wall")

# set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} --coverage -shared -lgcov" )

set(SETLIB_INCLUDE_DIRS ${SETLIB_INCLUDE_DIRS} ${CMAKE_HOME_DIRECTORY}/include/)
set(SETLIB_HEADERS ${SETLIB_HEADERS} ${CMAKE_HOME_DIRECTORY}/include/Set.hpp)

add_library(${PROJECT_NAME} STATIC ${SETLIB_HEADERS})
set_target_properties(cpp_course_hw PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(${PROJECT_NAME} PUBLIC ${SETLIB_INCLUDE_DIRS})

add_subdirectory(tests)
add_subdirectory(tests/base_test)
add_subdirectory(tests/speed_test)
add_subdirectory(tests/unit_test)