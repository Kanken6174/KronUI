# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/kanken/code/opengl-tests/KronUI/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kanken/code/opengl-tests/KronUI/src

# Include any dependencies generated for this target.
include KronUIGL/CMakeFiles/KronUIGL.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include KronUIGL/CMakeFiles/KronUIGL.dir/compiler_depend.make

# Include the progress variables for this target.
include KronUIGL/CMakeFiles/KronUIGL.dir/progress.make

# Include the compile flags for this target's objects.
include KronUIGL/CMakeFiles/KronUIGL.dir/flags.make

# Object files for target KronUIGL
KronUIGL_OBJECTS =

# External object files for target KronUIGL
KronUIGL_EXTERNAL_OBJECTS =

KronUIGL/libKronUIGL.a: KronUIGL/CMakeFiles/KronUIGL.dir/build.make
KronUIGL/libKronUIGL.a: KronUIGL/CMakeFiles/KronUIGL.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kanken/code/opengl-tests/KronUI/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Linking CXX static library libKronUIGL.a"
	cd /home/kanken/code/opengl-tests/KronUI/src/KronUIGL && $(CMAKE_COMMAND) -P CMakeFiles/KronUIGL.dir/cmake_clean_target.cmake
	cd /home/kanken/code/opengl-tests/KronUI/src/KronUIGL && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/KronUIGL.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
KronUIGL/CMakeFiles/KronUIGL.dir/build: KronUIGL/libKronUIGL.a
.PHONY : KronUIGL/CMakeFiles/KronUIGL.dir/build

KronUIGL/CMakeFiles/KronUIGL.dir/clean:
	cd /home/kanken/code/opengl-tests/KronUI/src/KronUIGL && $(CMAKE_COMMAND) -P CMakeFiles/KronUIGL.dir/cmake_clean.cmake
.PHONY : KronUIGL/CMakeFiles/KronUIGL.dir/clean

KronUIGL/CMakeFiles/KronUIGL.dir/depend:
	cd /home/kanken/code/opengl-tests/KronUI/src && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kanken/code/opengl-tests/KronUI/src /home/kanken/code/opengl-tests/KronUI/src/KronUIGL /home/kanken/code/opengl-tests/KronUI/src /home/kanken/code/opengl-tests/KronUI/src/KronUIGL /home/kanken/code/opengl-tests/KronUI/src/KronUIGL/CMakeFiles/KronUIGL.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : KronUIGL/CMakeFiles/KronUIGL.dir/depend

