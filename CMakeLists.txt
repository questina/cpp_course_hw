set(CMAKE_GENERATOR "Ninja")
cmake_minimum_required(VERSION 3.16)
project(toys_catalog C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wpedantic -Wall -Wextra -Werror")

set(CMAKE_THREAD_LIBS_INIT "-lpthread")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_WIN32_THREADS_INIT 0)
set(CMAKE_USE_PTHREADS_INIT 1)
set(THREADS_PREFER_PTHREAD_FLAG ON)

option(SANITIZER_BUILD "Build app with sanitizer flags" OFF)

if (SANITIZER_BUILD)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address,undefined -fno-sanitize-recover=all -fsanitize-undefined-trap-on-error ")
endif()

add_subdirectory(libs)

message("TOYS_LIB_INCLUDE_DIRS = ${TOYS_LIB_INCLUDE_DIRS}")
message("TOYS_LIB_LIBRARIES = ${TOYS_LIB_LIBRARIES}")

add_executable(${PROJECT_NAME} main.c)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )

target_include_directories(${PROJECT_NAME} PUBLIC ${TOYS_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${TOYS_LIB_LIBRARIES})

add_subdirectory(tests)