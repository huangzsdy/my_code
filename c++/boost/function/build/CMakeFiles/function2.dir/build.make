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
CMAKE_SOURCE_DIR = /home/huangzesang/share/learning/my_code/c++/boost/function

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/huangzesang/share/learning/my_code/c++/boost/function/build

# Include any dependencies generated for this target.
include CMakeFiles/function2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/function2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/function2.dir/flags.make

CMakeFiles/function2.dir/function2.o: CMakeFiles/function2.dir/flags.make
CMakeFiles/function2.dir/function2.o: ../function2.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/huangzesang/share/learning/my_code/c++/boost/function/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/function2.dir/function2.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/function2.dir/function2.o -c /home/huangzesang/share/learning/my_code/c++/boost/function/function2.cpp

CMakeFiles/function2.dir/function2.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/function2.dir/function2.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/huangzesang/share/learning/my_code/c++/boost/function/function2.cpp > CMakeFiles/function2.dir/function2.i

CMakeFiles/function2.dir/function2.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/function2.dir/function2.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/huangzesang/share/learning/my_code/c++/boost/function/function2.cpp -o CMakeFiles/function2.dir/function2.s

CMakeFiles/function2.dir/function2.o.requires:
.PHONY : CMakeFiles/function2.dir/function2.o.requires

CMakeFiles/function2.dir/function2.o.provides: CMakeFiles/function2.dir/function2.o.requires
	$(MAKE) -f CMakeFiles/function2.dir/build.make CMakeFiles/function2.dir/function2.o.provides.build
.PHONY : CMakeFiles/function2.dir/function2.o.provides

CMakeFiles/function2.dir/function2.o.provides.build: CMakeFiles/function2.dir/function2.o

# Object files for target function2
function2_OBJECTS = \
"CMakeFiles/function2.dir/function2.o"

# External object files for target function2
function2_EXTERNAL_OBJECTS =

../bin/function2: CMakeFiles/function2.dir/function2.o
../bin/function2: CMakeFiles/function2.dir/build.make
../bin/function2: CMakeFiles/function2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../bin/function2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/function2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/function2.dir/build: ../bin/function2
.PHONY : CMakeFiles/function2.dir/build

CMakeFiles/function2.dir/requires: CMakeFiles/function2.dir/function2.o.requires
.PHONY : CMakeFiles/function2.dir/requires

CMakeFiles/function2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/function2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/function2.dir/clean

CMakeFiles/function2.dir/depend:
	cd /home/huangzesang/share/learning/my_code/c++/boost/function/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/huangzesang/share/learning/my_code/c++/boost/function /home/huangzesang/share/learning/my_code/c++/boost/function /home/huangzesang/share/learning/my_code/c++/boost/function/build /home/huangzesang/share/learning/my_code/c++/boost/function/build /home/huangzesang/share/learning/my_code/c++/boost/function/build/CMakeFiles/function2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/function2.dir/depend
