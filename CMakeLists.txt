cmake_minimum_required(VERSION 3.14)
project(cpp_course_hw)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-g --coverage -O0 -Werror -Wall -Wpedantic")

set(LIB_HEADERS ${LIB_HEADERS} ${CMAKE_HOME_DIRECTORY}/include/buffer_reader.hpp
        ${CMAKE_HOME_DIRECTORY}/include/buffer_writer.hpp
        ${CMAKE_HOME_DIRECTORY}/include/file_manager.hpp
        ${CMAKE_HOME_DIRECTORY}/include/process_manager.hpp)

set(CMAKE_THREAD_LIBS_INIT "-lpthread")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_WIN32_THREADS_INIT 0)
set(CMAKE_USE_PTHREADS_INIT 1)
set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Boost 1.80.0 REQUIRED COMPONENTS filesystem chrono)
include_directories(${Boost_INCLUDE_DIR})

if(NOT Boost_FOUND)
    message(FATAL_ERROR "Could not find boost!")
endif()

option(SANITIZER_BUILD "Build app with sanitizer flags" OFF)

if (SANITIZER_BUILD)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address,undefined -fno-sanitize-recover=all -fsanitize-undefined-trap-on-error ")
endif()

add_subdirectory(include)

message("LIB_INCLUDE_DIRS = ${LIB_INCLUDE_DIRS}")
message("LIB_LIBRARIES = ${LIB_LIBRARIES}")

add_executable(${PROJECT_NAME} main.cpp)


set_target_properties(cpp_course_hw PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(${PROJECT_NAME} PUBLIC ${LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIB_LIBRARIES} ${Boost_LIBRARIES} -lpthread -lm)

add_subdirectory(tests)
add_subdirectory(tests/time_test)
add_subdirectory(tests/unit_test)