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
CMAKE_SOURCE_DIR = /home/huangzesang/share/learning/my_code/c++/boost/thread

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/huangzesang/share/learning/my_code/c++/boost/thread/build

# Include any dependencies generated for this target.
include CMakeFiles/thread_test4.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/thread_test4.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/thread_test4.dir/flags.make

CMakeFiles/thread_test4.dir/thread_test4.o: CMakeFiles/thread_test4.dir/flags.make
CMakeFiles/thread_test4.dir/thread_test4.o: ../thread_test4.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/huangzesang/share/learning/my_code/c++/boost/thread/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/thread_test4.dir/thread_test4.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/thread_test4.dir/thread_test4.o -c /home/huangzesang/share/learning/my_code/c++/boost/thread/thread_test4.cpp

CMakeFiles/thread_test4.dir/thread_test4.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/thread_test4.dir/thread_test4.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/huangzesang/share/learning/my_code/c++/boost/thread/thread_test4.cpp > CMakeFiles/thread_test4.dir/thread_test4.i

CMakeFiles/thread_test4.dir/thread_test4.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/thread_test4.dir/thread_test4.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/huangzesang/share/learning/my_code/c++/boost/thread/thread_test4.cpp -o CMakeFiles/thread_test4.dir/thread_test4.s

CMakeFiles/thread_test4.dir/thread_test4.o.requires:
.PHONY : CMakeFiles/thread_test4.dir/thread_test4.o.requires

CMakeFiles/thread_test4.dir/thread_test4.o.provides: CMakeFiles/thread_test4.dir/thread_test4.o.requires
	$(MAKE) -f CMakeFiles/thread_test4.dir/build.make CMakeFiles/thread_test4.dir/thread_test4.o.provides.build
.PHONY : CMakeFiles/thread_test4.dir/thread_test4.o.provides

CMakeFiles/thread_test4.dir/thread_test4.o.provides.build: CMakeFiles/thread_test4.dir/thread_test4.o

# Object files for target thread_test4
thread_test4_OBJECTS = \
"CMakeFiles/thread_test4.dir/thread_test4.o"

# External object files for target thread_test4
thread_test4_EXTERNAL_OBJECTS =

../bin/thread_test4: CMakeFiles/thread_test4.dir/thread_test4.o
../bin/thread_test4: CMakeFiles/thread_test4.dir/build.make
../bin/thread_test4: CMakeFiles/thread_test4.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../bin/thread_test4"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/thread_test4.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/thread_test4.dir/build: ../bin/thread_test4
.PHONY : CMakeFiles/thread_test4.dir/build

CMakeFiles/thread_test4.dir/requires: CMakeFiles/thread_test4.dir/thread_test4.o.requires
.PHONY : CMakeFiles/thread_test4.dir/requires

CMakeFiles/thread_test4.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/thread_test4.dir/cmake_clean.cmake
.PHONY : CMakeFiles/thread_test4.dir/clean

CMakeFiles/thread_test4.dir/depend:
	cd /home/huangzesang/share/learning/my_code/c++/boost/thread/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/huangzesang/share/learning/my_code/c++/boost/thread /home/huangzesang/share/learning/my_code/c++/boost/thread /home/huangzesang/share/learning/my_code/c++/boost/thread/build /home/huangzesang/share/learning/my_code/c++/boost/thread/build /home/huangzesang/share/learning/my_code/c++/boost/thread/build/CMakeFiles/thread_test4.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/thread_test4.dir/depend
