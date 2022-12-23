BUILD_FILE = cmake-build-debug
TARGET_PROJECT = cpp_course_hw
TIME_TEST = time_test
UNIT_TEST = unit_test
TEST_DIR = tests
INPUT_FILE = input.txt
OUTPUT_FILE = output.txt
SOURCE_FILES = main.cpp ./include/*.cpp
HEADER_FILES = ./include/*.hpp

all: check build

build: build_main clean

tests: time_tests test-with-coverage clean

clean:
	rm -rf ${BUILD_FILE}
	rm -f *.out
	rm -f coverage.info
	rm -rf report
	rm -f input.txt
	rm -rf boost_1_80_0
	rm -f boost_1_80_0.tar.bz2

build_main:
	cmake -DCMAKE_BUILD_TYPE=Debug -S ./ -B ./${BUILD_FILE}
	cmake --build ./${BUILD_FILE} --target ${TARGET_PROJECT}
	touch ${OUTPUT_FILE}
	g++ -std=c++20 ./example/sequential.cpp -o seq.out
	./${BUILD_FILE}/${TARGET_PROJECT} "parallel" ${INPUT_FILE} ${OUTPUT_FILE} "seq.out" 10000000

time_tests:
	cmake -DCMAKE_BUILD_TYPE=Debug -S ./ -B ./${BUILD_FILE}
	cmake --build ./${BUILD_FILE} --target ${TIME_TEST}
	g++ -std=c++20 ./example/sequential.cpp -o seq.out
	./${BUILD_FILE}/${TEST_DIR}/${TIME_TEST}/${TIME_TEST}

unit_tests:
	cmake -DCMAKE_BUILD_TYPE=Debug -S ./ -B ./${BUILD_FILE}
	cmake --build ./${BUILD_FILE} --target ${UNIT_TEST}
	g++ -std=c++20 ./example/sequential.cpp -o seq.out
	./${BUILD_FILE}/${TEST_DIR}/${UNIT_TEST}/${UNIT_TEST}

check: check-stat-analysis check-linters check-sanitizer clean check-valgrind clean

check-sanitizer:
	echo "Run sanitizer"
	cmake -DCMAKE_BUILD_TYPE=Debug SANITIZER_BUILD=ON -S ./ -B ./${BUILD_FILE}
	cmake --build ./${BUILD_FILE} --target ${TARGET_PROJECT}
	touch ${OUTPUT_FILE}
	g++ -std=c++20 ./example/sequential.cpp -o seq.out
	./${BUILD_FILE}/${TARGET_PROJECT} "parallel" ${INPUT_FILE} ${OUTPUT_FILE} "seq.out" 10000000

check-valgrind:
	echo "Run valgrind"
	cmake -DCMAKE_BUILD_TYPE=Debug -S ./ -B ./${BUILD_FILE}
	cmake --build ./${BUILD_FILE} --target ${TARGET_PROJECT}
	touch ${OUTPUT_FILE}
	g++ -std=c++20 ./example/sequential.cpp -o seq.out
	valgrind --tool=memcheck --leak-check=yes --exit-on-first-error=yes --error-exitcode=1 ./${BUILD_FILE}/${TARGET_PROJECT} "parallel" ${INPUT_FILE} ${OUTPUT_FILE} "seq.out" 10000000

check-stat-analysis:
	echo "Run static analysis cppcheck and cpplint"
	cppcheck ${SOURCE_FILES} ${HEADER_FILES} ${TEST_FILES} --enable=all --inconclusive --error-exitcode=1 --suppress=missingInclude
	cpplint --extensions=c ${SOURCE_FILES} ${HEADER_FILES}

check-linters:
	echo "Running linter clang-tidy"
	clang-tidy ${SOURCE_FILES} ${HEADER_FILES} --fix-errors -warnings-as-errors=* -extra-arg=-std=c++20 --

test-with-coverage:
	echo "Running tests with coverage"
	cmake -DCMAKE_BUILD_TYPE=Debug -S ./ -B ./${BUILD_FILE}
	cmake --build ./${BUILD_FILE} --target ${UNIT_TEST}
	g++ -std=c++20 ./example/sequential.cpp -o seq.out
	./${BUILD_FILE}/${TEST_DIR}/${UNIT_TEST}/${UNIT_TEST}
	lcov -t "tests/unit_test" -o coverage.info -c -d ./${BUILD_FILE}/${TEST_DIR}/${UNIT_TEST}/
	lcov --remove coverage.info '/usr/include/*' '/usr/local/include/c++/*' '/project/tests/unit_test/unit_test.cpp' 'tests/unit_test/unit_test.cpp' '/project/cmake-build-debug/*' '/include/boost/*' 'gtest/*' '/__w/cpp_course_hw/cpp_course_hw/tests/*' -o coverage.info
	genhtml -o report coverage.info

