TEST_DIR = tests
BASE_TEST = base_test
SPEED_TEST = speed_test
UNIT_TEST = unit_test
BUILD_FILE = cmake-build-debug
TARGET_PROJECT = cpp_course_hw

all: build tests clean

tests: base_tests unit_tests speed_tests clean

build: build_main clean

clean:
	rm -rf ${BUILD_FILE}
	rm -f *.out
	rm -f coverage.info
	rm -rf report

build_main:
	cmake -DCMAKE_BUILD_TYPE=Debug -S ./ -B ./${BUILD_FILE}
	cmake --build ./${BUILD_FILE} --target ${TARGET_PROJECT}

base_tests:
	cmake -DCMAKE_BUILD_TYPE=Debug -S ./ -B ./${BUILD_FILE}
	cmake --build ./${BUILD_FILE} --target ${BASE_TEST}
	./${BUILD_FILE}/${TEST_DIR}/${BASE_TEST}/${BASE_TEST}

unit_tests:
	cmake -DCMAKE_BUILD_TYPE=Debug -S ./ -B ./${BUILD_FILE}
	cmake --build ./${BUILD_FILE} --target ${UNIT_TEST}
	./${BUILD_FILE}/${TEST_DIR}/${UNIT_TEST}/${UNIT_TEST}
	lcov -t "tests/unit_test" -o coverage.info -c -d ./${BUILD_FILE}/${TEST_DIR}/${UNIT_TEST}/
	lcov --remove coverage.info '/usr/include/*' '/usr/local/include/c++/*' '/project/tests/unit_test/unit_test.cpp' 'tests/unit_test/unit_test.cpp' -o coverage.info
	genhtml -o report coverage.info

speed_tests:
	cmake -DCMAKE_BUILD_TYPE=Debug -S ./ -B ./${BUILD_FILE}
	cmake --build ./${BUILD_FILE} --target ${SPEED_TEST}
	./${BUILD_FILE}/${TEST_DIR}/${SPEED_TEST}/${SPEED_TEST}
