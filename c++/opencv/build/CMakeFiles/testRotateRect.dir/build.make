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
CMAKE_SOURCE_DIR = /home/huangzesang/share/learning/my_code/c++/opencv

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/huangzesang/share/learning/my_code/c++/opencv/build

# Include any dependencies generated for this target.
include CMakeFiles/testRotateRect.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/testRotateRect.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/testRotateRect.dir/flags.make

CMakeFiles/testRotateRect.dir/src/testRotateRect.cpp.o: CMakeFiles/testRotateRect.dir/flags.make
CMakeFiles/testRotateRect.dir/src/testRotateRect.cpp.o: ../src/testRotateRect.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/huangzesang/share/learning/my_code/c++/opencv/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/testRotateRect.dir/src/testRotateRect.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/testRotateRect.dir/src/testRotateRect.cpp.o -c /home/huangzesang/share/learning/my_code/c++/opencv/src/testRotateRect.cpp

CMakeFiles/testRotateRect.dir/src/testRotateRect.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testRotateRect.dir/src/testRotateRect.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/huangzesang/share/learning/my_code/c++/opencv/src/testRotateRect.cpp > CMakeFiles/testRotateRect.dir/src/testRotateRect.cpp.i

CMakeFiles/testRotateRect.dir/src/testRotateRect.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testRotateRect.dir/src/testRotateRect.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/huangzesang/share/learning/my_code/c++/opencv/src/testRotateRect.cpp -o CMakeFiles/testRotateRect.dir/src/testRotateRect.cpp.s

CMakeFiles/testRotateRect.dir/src/testRotateRect.cpp.o.requires:
.PHONY : CMakeFiles/testRotateRect.dir/src/testRotateRect.cpp.o.requires

CMakeFiles/testRotateRect.dir/src/testRotateRect.cpp.o.provides: CMakeFiles/testRotateRect.dir/src/testRotateRect.cpp.o.requires
	$(MAKE) -f CMakeFiles/testRotateRect.dir/build.make CMakeFiles/testRotateRect.dir/src/testRotateRect.cpp.o.provides.build
.PHONY : CMakeFiles/testRotateRect.dir/src/testRotateRect.cpp.o.provides

CMakeFiles/testRotateRect.dir/src/testRotateRect.cpp.o.provides.build: CMakeFiles/testRotateRect.dir/src/testRotateRect.cpp.o

# Object files for target testRotateRect
testRotateRect_OBJECTS = \
"CMakeFiles/testRotateRect.dir/src/testRotateRect.cpp.o"

# External object files for target testRotateRect
testRotateRect_EXTERNAL_OBJECTS =

../bin/testRotateRect: CMakeFiles/testRotateRect.dir/src/testRotateRect.cpp.o
../bin/testRotateRect: CMakeFiles/testRotateRect.dir/build.make
../bin/testRotateRect: CMakeFiles/testRotateRect.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../bin/testRotateRect"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/testRotateRect.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/testRotateRect.dir/build: ../bin/testRotateRect
.PHONY : CMakeFiles/testRotateRect.dir/build

CMakeFiles/testRotateRect.dir/requires: CMakeFiles/testRotateRect.dir/src/testRotateRect.cpp.o.requires
.PHONY : CMakeFiles/testRotateRect.dir/requires

CMakeFiles/testRotateRect.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/testRotateRect.dir/cmake_clean.cmake
.PHONY : CMakeFiles/testRotateRect.dir/clean

CMakeFiles/testRotateRect.dir/depend:
	cd /home/huangzesang/share/learning/my_code/c++/opencv/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/huangzesang/share/learning/my_code/c++/opencv /home/huangzesang/share/learning/my_code/c++/opencv /home/huangzesang/share/learning/my_code/c++/opencv/build /home/huangzesang/share/learning/my_code/c++/opencv/build /home/huangzesang/share/learning/my_code/c++/opencv/build/CMakeFiles/testRotateRect.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/testRotateRect.dir/depend

