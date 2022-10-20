cmake_minimum_required(VERSION 3.23)
project(toys_catalog C)

add_subdirectory(toys_lib)

message("TOYS_LIB_INCLUDE_DIRS = ${TOYS_LIB_INCLUDE_DIRS}")
message("TOYS_LIB_LIBRARIES = ${TOYS_LIB_LIBRARIES}")

add_executable(${PROJECT_NAME} main.c)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )

target_include_directories(${PROJECT_NAME} PUBLIC ${TOYS_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${TOYS_LIB_LIBRARIES})

add_subdirectory(tests)