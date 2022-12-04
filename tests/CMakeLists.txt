add_dependencies(tests test)
add_executable(test test_structures.cpp)
target_link_libraries(test PUBLIC gtest gtest_main pthread)

