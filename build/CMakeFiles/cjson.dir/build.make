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
include CMakeFiles/cjson.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/cjson.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/cjson.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cjson.dir/flags.make

CMakeFiles/cjson.dir/leptjson.c.o: CMakeFiles/cjson.dir/flags.make
CMakeFiles/cjson.dir/leptjson.c.o: ../leptjson.c
CMakeFiles/cjson.dir/leptjson.c.o: CMakeFiles/cjson.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yanghl/cJson/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/cjson.dir/leptjson.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/cjson.dir/leptjson.c.o -MF CMakeFiles/cjson.dir/leptjson.c.o.d -o CMakeFiles/cjson.dir/leptjson.c.o -c /home/yanghl/cJson/leptjson.c

CMakeFiles/cjson.dir/leptjson.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cjson.dir/leptjson.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/yanghl/cJson/leptjson.c > CMakeFiles/cjson.dir/leptjson.c.i

CMakeFiles/cjson.dir/leptjson.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cjson.dir/leptjson.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/yanghl/cJson/leptjson.c -o CMakeFiles/cjson.dir/leptjson.c.s

# Object files for target cjson
cjson_OBJECTS = \
"CMakeFiles/cjson.dir/leptjson.c.o"

# External object files for target cjson
cjson_EXTERNAL_OBJECTS =

libcjson.a: CMakeFiles/cjson.dir/leptjson.c.o
libcjson.a: CMakeFiles/cjson.dir/build.make
libcjson.a: CMakeFiles/cjson.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/yanghl/cJson/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libcjson.a"
	$(CMAKE_COMMAND) -P CMakeFiles/cjson.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cjson.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cjson.dir/build: libcjson.a
.PHONY : CMakeFiles/cjson.dir/build

CMakeFiles/cjson.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cjson.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cjson.dir/clean

CMakeFiles/cjson.dir/depend:
	cd /home/yanghl/cJson/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yanghl/cJson /home/yanghl/cJson /home/yanghl/cJson/build /home/yanghl/cJson/build /home/yanghl/cJson/build/CMakeFiles/cjson.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/cjson.dir/depend

