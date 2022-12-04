TEST_DIR = tests
TEST_FILE = test_structures.cpp
BUILD_FILE = cmake-build-debug
TARGET_PROJECT = cpp_course_hw
TARGET_TEST = test

all: build matrtests clean

clean:
	rm -rf ${BUILD_FILE}
	rm -f *.out

build:
	cmake -DCMAKE_BUILD_TYPE=Debug -S ./ -B ./${BUILD_FILE}
	cmake --build ./${BUILD_FILE} --target ${TARGET_PROJECT}
	./${BUILD_FILE}/${TARGET_PROJECT}

matrtests:
	cmake -DCMAKE_BUILD_TYPE=Debug -S ./ -B ./${BUILD_FILE}
	cmake --build ./${BUILD_FILE} --target ${TARGET_TEST}
	./${BUILD_FILE}/${TEST_DIR}/${TARGET_TEST}
