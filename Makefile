TARGET = main
LIB_DIR = toys_lib
TEST_DIR = tests
SOURCE_FILES = main.c \
			   libs/*/*.c
HEADER_FILES = libs/*/*.h
TEST_FILES = ${TEST_DIR}/tests.cpp
BUILD_FILE = cmake-build-debug
MAIN_PROJECT_NAME = toys_catalog
TEST_PROJECT_NAME = test_toys_store
INPUT_FILE = input.txt

clean:
	rm -rf cmake-build-debug
	rm -rf report
	rm -f coverage.info
	rm -f main
	rm -rf main.dSYM

build_and_run: build run clean

build:
	cmake -DCMAKE_BUILD_TYPE=Debug SANITIZER_BUILD=ON -S ./ -B ./${BUILD_FILE}
	cmake --build ./${BUILD_FILE} --target ${MAIN_PROJECT_NAME}

run:
	./${BUILD_FILE}/${MAIN_PROJECT_NAME} < ${INPUT_FILE}

check: check-stat-analysis check-linters check-sanitizer clean check-valgrind clean

check-sanitizer:
	echo "Run sanitizer"
	cmake -DCMAKE_BUILD_TYPE=Debug SANITIZER_BUILD=ON -S ./ -B ./${BUILD_FILE}
	cmake --build ./${BUILD_FILE} --target ${MAIN_PROJECT_NAME}
	./${BUILD_FILE}/${MAIN_PROJECT_NAME}

check-valgrind:
	echo "Run valgrind"
	cmake -DCMAKE_BUILD_TYPE=Debug -S ./ -B ./${BUILD_FILE}
	cmake --build ./${BUILD_FILE} --target ${MAIN_PROJECT_NAME}
	valgrind --tool=memcheck --leak-check=yes --exit-on-first-error=yes --error-exitcode=1 ./${BUILD_FILE}/${MAIN_PROJECT_NAME}

check-stat-analysis:
	echo "Run static analysis cppcheck and cpplint"
	cppcheck ${SOURCE_FILES} ${HEADER_FILES} ${TEST_FILES} --enable=all --inconclusive --error-exitcode=1 --suppress=missingInclude
	cpplint --extensions=c ${SOURCE_FILES} ${HEADER_FILES}

check-linters:
	echo "Running linter clang-tidy"
	clang-tidy ${SOURCE_FILES} ${HEADER_FILES} --fix-errors -warnings-as-errors=* -extra-arg=-std=c99 --

test: test-with-valgrind test-with-coverage clean

test-with-coverage:
	echo "Running tests with coverage"
	cmake -DCMAKE_BUILD_TYPE=Debug -S ./ -B ./${BUILD_FILE}
	cmake --build ./${BUILD_FILE} --target ${TEST_PROJECT_NAME}
	./${BUILD_FILE}/${TEST_DIR}/${TEST_PROJECT_NAME}
	lcov -t "tests/tests" -o coverage.info -c -d ./${BUILD_FILE}/${LIB_DIR}/
	genhtml -o report coverage.info

test-with-valgrind:
	echo "Running tests in valgrind"
	cmake -DCMAKE_BUILD_TYPE=Debug -S ./ -B ./${BUILD_FILE}
	cmake --build ./${BUILD_FILE} --target  ${TEST_PROJECT_NAME}
	valgrind --tool=memcheck --leak-check=yes --exit-on-first-error=yes --error-exitcode=1 ./${BUILD_FILE}/${TEST_DIR}/${TEST_PROJECT_NAME}

test-with-sanitizer:
	echo "Running tests with sanitizer"
	cmake -DCMAKE_BUILD_TYPE=Debug SANITIZER_BUILD=ON -S ./ -B ./${BUILD_FILE}
	cmake --build ./${BUILD_FILE} --target ${TEST_PROJECT_NAME}