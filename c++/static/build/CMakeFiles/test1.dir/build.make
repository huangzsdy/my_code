# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/huangzesang/share/learning/my_code/c++/static

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/huangzesang/share/learning/my_code/c++/static/build

# Include any dependencies generated for this target.
include CMakeFiles/test1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/test1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test1.dir/flags.make

CMakeFiles/test1.dir/src/test1.o: CMakeFiles/test1.dir/flags.make
CMakeFiles/test1.dir/src/test1.o: ../src/test1.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/huangzesang/share/learning/my_code/c++/static/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/test1.dir/src/test1.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/test1.dir/src/test1.o -c /home/huangzesang/share/learning/my_code/c++/static/src/test1.cpp

CMakeFiles/test1.dir/src/test1.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test1.dir/src/test1.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/huangzesang/share/learning/my_code/c++/static/src/test1.cpp > CMakeFiles/test1.dir/src/test1.i

CMakeFiles/test1.dir/src/test1.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test1.dir/src/test1.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/huangzesang/share/learning/my_code/c++/static/src/test1.cpp -o CMakeFiles/test1.dir/src/test1.s

CMakeFiles/test1.dir/src/test1.o.requires:
.PHONY : CMakeFiles/test1.dir/src/test1.o.requires

CMakeFiles/test1.dir/src/test1.o.provides: CMakeFiles/test1.dir/src/test1.o.requires
	$(MAKE) -f CMakeFiles/test1.dir/build.make CMakeFiles/test1.dir/src/test1.o.provides.build
.PHONY : CMakeFiles/test1.dir/src/test1.o.provides

CMakeFiles/test1.dir/src/test1.o.provides.build: CMakeFiles/test1.dir/src/test1.o

# Object files for target test1
test1_OBJECTS = \
"CMakeFiles/test1.dir/src/test1.o"

# External object files for target test1
test1_EXTERNAL_OBJECTS =

../bin/test1: CMakeFiles/test1.dir/src/test1.o
../bin/test1: CMakeFiles/test1.dir/build.make
../bin/test1: CMakeFiles/test1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../bin/test1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test1.dir/build: ../bin/test1
.PHONY : CMakeFiles/test1.dir/build

CMakeFiles/test1.dir/requires: CMakeFiles/test1.dir/src/test1.o.requires
.PHONY : CMakeFiles/test1.dir/requires

CMakeFiles/test1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test1.dir/clean

CMakeFiles/test1.dir/depend:
	cd /home/huangzesang/share/learning/my_code/c++/static/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/huangzesang/share/learning/my_code/c++/static /home/huangzesang/share/learning/my_code/c++/static /home/huangzesang/share/learning/my_code/c++/static/build /home/huangzesang/share/learning/my_code/c++/static/build /home/huangzesang/share/learning/my_code/c++/static/build/CMakeFiles/test1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test1.dir/depend
