# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/maks/Desktop/questina/cpp_hw/toys_catalog

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/maks/Desktop/questina/cpp_hw/toys_catalog/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/toys_catalog.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/toys_catalog.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/toys_catalog.dir/flags.make

CMakeFiles/toys_catalog.dir/main.c.o: CMakeFiles/toys_catalog.dir/flags.make
CMakeFiles/toys_catalog.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --progress-dir=/home/maks/Desktop/questina/cpp_hw/toys_catalog/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/toys_catalog.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/toys_catalog.dir/main.c.o   -c /home/maks/Desktop/questina/cpp_hw/toys_catalog/main.c

CMakeFiles/toys_catalog.dir/main.c.i: cmake_force
	@echo "Preprocessing C source to CMakeFiles/toys_catalog.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/maks/Desktop/questina/cpp_hw/toys_catalog/main.c > CMakeFiles/toys_catalog.dir/main.c.i

CMakeFiles/toys_catalog.dir/main.c.s: cmake_force
	@echo "Compiling C source to assembly CMakeFiles/toys_catalog.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/maks/Desktop/questina/cpp_hw/toys_catalog/main.c -o CMakeFiles/toys_catalog.dir/main.c.s

# Object files for target toys_catalog
toys_catalog_OBJECTS = \
"CMakeFiles/toys_catalog.dir/main.c.o"

# External object files for target toys_catalog
toys_catalog_EXTERNAL_OBJECTS =

toys_catalog: CMakeFiles/toys_catalog.dir/main.c.o
toys_catalog: CMakeFiles/toys_catalog.dir/build.make
toys_catalog: toys_lib/libtoys_lib.a
toys_catalog: CMakeFiles/toys_catalog.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --progress-dir=/home/maks/Desktop/questina/cpp_hw/toys_catalog/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable toys_catalog"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/toys_catalog.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/toys_catalog.dir/build: toys_catalog

.PHONY : CMakeFiles/toys_catalog.dir/build

CMakeFiles/toys_catalog.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/toys_catalog.dir/cmake_clean.cmake
.PHONY : CMakeFiles/toys_catalog.dir/clean

CMakeFiles/toys_catalog.dir/depend:
	cd /home/maks/Desktop/questina/cpp_hw/toys_catalog/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/maks/Desktop/questina/cpp_hw/toys_catalog /home/maks/Desktop/questina/cpp_hw/toys_catalog /home/maks/Desktop/questina/cpp_hw/toys_catalog/cmake-build-debug /home/maks/Desktop/questina/cpp_hw/toys_catalog/cmake-build-debug /home/maks/Desktop/questina/cpp_hw/toys_catalog/cmake-build-debug/CMakeFiles/toys_catalog.dir/DependInfo.cmake
.PHONY : CMakeFiles/toys_catalog.dir/depend

