# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/yanghl/cmake-3.20.0-linux-x86_64/bin/cmake

# The command to remove a file.
RM = /home/yanghl/cmake-3.20.0-linux-x86_64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/yanghl/cJson

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yanghl/cJson/build

# Include any dependencies generated for this target.
include CMakeFiles/cjson_test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/cjson_test.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/cjson_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cjson_test.dir/flags.make

CMakeFiles/cjson_test.dir/test.c.o: CMakeFiles/cjson_test.dir/flags.make
CMakeFiles/cjson_test.dir/test.c.o: ../test.c
CMakeFiles/cjson_test.dir/test.c.o: CMakeFiles/cjson_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yanghl/cJson/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/cjson_test.dir/test.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/cjson_test.dir/test.c.o -MF CMakeFiles/cjson_test.dir/test.c.o.d -o CMakeFiles/cjson_test.dir/test.c.o -c /home/yanghl/cJson/test.c

CMakeFiles/cjson_test.dir/test.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cjson_test.dir/test.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/yanghl/cJson/test.c > CMakeFiles/cjson_test.dir/test.c.i

CMakeFiles/cjson_test.dir/test.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cjson_test.dir/test.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/yanghl/cJson/test.c -o CMakeFiles/cjson_test.dir/test.c.s

# Object files for target cjson_test
cjson_test_OBJECTS = \
"CMakeFiles/cjson_test.dir/test.c.o"

# External object files for target cjson_test
cjson_test_EXTERNAL_OBJECTS =

cjson_test: CMakeFiles/cjson_test.dir/test.c.o
cjson_test: CMakeFiles/cjson_test.dir/build.make
cjson_test: libcjson.a
cjson_test: CMakeFiles/cjson_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/yanghl/cJson/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable cjson_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cjson_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cjson_test.dir/build: cjson_test
.PHONY : CMakeFiles/cjson_test.dir/build

CMakeFiles/cjson_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cjson_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cjson_test.dir/clean

CMakeFiles/cjson_test.dir/depend:
	cd /home/yanghl/cJson/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yanghl/cJson /home/yanghl/cJson /home/yanghl/cJson/build /home/yanghl/cJson/build /home/yanghl/cJson/build/CMakeFiles/cjson_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/cjson_test.dir/depend

