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
CMAKE_SOURCE_DIR = /home/huangzesang/share/learning/my_code/c++/data_structure

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/huangzesang/share/learning/my_code/c++/data_structure/build

# Include any dependencies generated for this target.
include CMakeFiles/sort.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/sort.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/sort.dir/flags.make

CMakeFiles/sort.dir/src/sort.o: CMakeFiles/sort.dir/flags.make
CMakeFiles/sort.dir/src/sort.o: ../src/sort.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/huangzesang/share/learning/my_code/c++/data_structure/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/sort.dir/src/sort.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/sort.dir/src/sort.o -c /home/huangzesang/share/learning/my_code/c++/data_structure/src/sort.cpp

CMakeFiles/sort.dir/src/sort.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sort.dir/src/sort.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/huangzesang/share/learning/my_code/c++/data_structure/src/sort.cpp > CMakeFiles/sort.dir/src/sort.i

CMakeFiles/sort.dir/src/sort.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sort.dir/src/sort.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/huangzesang/share/learning/my_code/c++/data_structure/src/sort.cpp -o CMakeFiles/sort.dir/src/sort.s

CMakeFiles/sort.dir/src/sort.o.requires:
.PHONY : CMakeFiles/sort.dir/src/sort.o.requires

CMakeFiles/sort.dir/src/sort.o.provides: CMakeFiles/sort.dir/src/sort.o.requires
	$(MAKE) -f CMakeFiles/sort.dir/build.make CMakeFiles/sort.dir/src/sort.o.provides.build
.PHONY : CMakeFiles/sort.dir/src/sort.o.provides

CMakeFiles/sort.dir/src/sort.o.provides.build: CMakeFiles/sort.dir/src/sort.o

# Object files for target sort
sort_OBJECTS = \
"CMakeFiles/sort.dir/src/sort.o"

# External object files for target sort
sort_EXTERNAL_OBJECTS =

../bin/sort: CMakeFiles/sort.dir/src/sort.o
../bin/sort: CMakeFiles/sort.dir/build.make
../bin/sort: CMakeFiles/sort.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../bin/sort"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sort.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/sort.dir/build: ../bin/sort
.PHONY : CMakeFiles/sort.dir/build

CMakeFiles/sort.dir/requires: CMakeFiles/sort.dir/src/sort.o.requires
.PHONY : CMakeFiles/sort.dir/requires

CMakeFiles/sort.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/sort.dir/cmake_clean.cmake
.PHONY : CMakeFiles/sort.dir/clean

CMakeFiles/sort.dir/depend:
	cd /home/huangzesang/share/learning/my_code/c++/data_structure/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/huangzesang/share/learning/my_code/c++/data_structure /home/huangzesang/share/learning/my_code/c++/data_structure /home/huangzesang/share/learning/my_code/c++/data_structure/build /home/huangzesang/share/learning/my_code/c++/data_structure/build /home/huangzesang/share/learning/my_code/c++/data_structure/build/CMakeFiles/sort.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/sort.dir/depend

