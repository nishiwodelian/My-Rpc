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
CMAKE_SOURCE_DIR = /home/zcy/Cpp/My-Rpc

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zcy/Cpp/My-Rpc/build

# Include any dependencies generated for this target.
include test/CMakeFiles/client.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/client.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/client.dir/flags.make

test/CMakeFiles/client.dir/client.cc.o: test/CMakeFiles/client.dir/flags.make
test/CMakeFiles/client.dir/client.cc.o: ../test/client.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zcy/Cpp/My-Rpc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/client.dir/client.cc.o"
	cd /home/zcy/Cpp/My-Rpc/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/client.dir/client.cc.o -c /home/zcy/Cpp/My-Rpc/test/client.cc

test/CMakeFiles/client.dir/client.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client.dir/client.cc.i"
	cd /home/zcy/Cpp/My-Rpc/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zcy/Cpp/My-Rpc/test/client.cc > CMakeFiles/client.dir/client.cc.i

test/CMakeFiles/client.dir/client.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client.dir/client.cc.s"
	cd /home/zcy/Cpp/My-Rpc/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zcy/Cpp/My-Rpc/test/client.cc -o CMakeFiles/client.dir/client.cc.s

# Object files for target client
client_OBJECTS = \
"CMakeFiles/client.dir/client.cc.o"

# External object files for target client
client_EXTERNAL_OBJECTS =

../bin/client: test/CMakeFiles/client.dir/client.cc.o
../bin/client: test/CMakeFiles/client.dir/build.make
../bin/client: ../lib/libMyNetworkLib.so
../bin/client: test/CMakeFiles/client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zcy/Cpp/My-Rpc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../bin/client"
	cd /home/zcy/Cpp/My-Rpc/build/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/client.dir/build: ../bin/client

.PHONY : test/CMakeFiles/client.dir/build

test/CMakeFiles/client.dir/clean:
	cd /home/zcy/Cpp/My-Rpc/build/test && $(CMAKE_COMMAND) -P CMakeFiles/client.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/client.dir/clean

test/CMakeFiles/client.dir/depend:
	cd /home/zcy/Cpp/My-Rpc/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zcy/Cpp/My-Rpc /home/zcy/Cpp/My-Rpc/test /home/zcy/Cpp/My-Rpc/build /home/zcy/Cpp/My-Rpc/build/test /home/zcy/Cpp/My-Rpc/build/test/CMakeFiles/client.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/client.dir/depend
