TARGET = main
INCLUDE_DIRS = toys_lib
SOURCE_FILES = main.c \
			   toys_lib/*.c

build: ${TARGET}

${TARGET}: ${INCLUDE_DIRS} ${SOURCE_FILES}
	gcc -g -Wpedantic -Wall -Wextra -Werror -I ${INCLUDE_DIRS} ${SOURCE_FILES} -o ${TARGET}

run: ${TARGET}
	./${TARGET}

clean:
	rm -rf cmake-build-debug
	rm -rf report
	rm coverage.info

check: check-sanitizer check-valgrind clean

check-sanitizer:
	echo "Run with sanitizer"
	cmake -DCMAKE_BUILD_TYPE=Debug SANITIZER_BUILD=ON -S ./ -B ./cmake-build-debug
	cmake --build ./cmake-build-debug --target toys_catalog
	./cmake-build-debug/toys_catalog

check-valgrind:
	echo "Run valgrind"
	cmake -DCMAKE_BUILD_TYPE=Debug -S ./ -B ./cmake-build-debug
	cmake --build ./cmake-build-debug --target toys_catalog
	valgrind --tool=memcheck --leak-check=yes ./cmake-build-debug/toys_catalog

check-format:
	clang-format -i main.c
	clang-format -i toys_lib/toys.c
	clang-format -i toys_lib/toys.h

check-linters:
	chmod +x ./linters/run.sh
	./linters/run.sh

test: test-with-coverage clean

test-with-coverage:
	echo "Running tests"
	cmake -DCMAKE_BUILD_TYPE=Debug -S ./ -B ./cmake-build-debug
	cmake --build ./cmake-build-debug --target test_toys_store
	./cmake-build-debug/tests/test_toys_store
	lcov -t "tests/tests" -o coverage.info -c -d ./cmake-build-debug/toys_lib/
	genhtml -o report coverage.info
