# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = /opt/clion-2018.2.4/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /opt/clion-2018.2.4/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/muhammet/CLionProjects/psearch1a

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/muhammet/CLionProjects/psearch1a/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/psearch1a.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/psearch1a.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/psearch1a.dir/flags.make

CMakeFiles/psearch1a.dir/main.c.o: CMakeFiles/psearch1a.dir/flags.make
CMakeFiles/psearch1a.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/muhammet/CLionProjects/psearch1a/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/psearch1a.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/psearch1a.dir/main.c.o   -c /home/muhammet/CLionProjects/psearch1a/main.c

CMakeFiles/psearch1a.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/psearch1a.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/muhammet/CLionProjects/psearch1a/main.c > CMakeFiles/psearch1a.dir/main.c.i

CMakeFiles/psearch1a.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/psearch1a.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/muhammet/CLionProjects/psearch1a/main.c -o CMakeFiles/psearch1a.dir/main.c.s

CMakeFiles/psearch1a.dir/utilities.c.o: CMakeFiles/psearch1a.dir/flags.make
CMakeFiles/psearch1a.dir/utilities.c.o: ../utilities.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/muhammet/CLionProjects/psearch1a/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/psearch1a.dir/utilities.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/psearch1a.dir/utilities.c.o   -c /home/muhammet/CLionProjects/psearch1a/utilities.c

CMakeFiles/psearch1a.dir/utilities.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/psearch1a.dir/utilities.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/muhammet/CLionProjects/psearch1a/utilities.c > CMakeFiles/psearch1a.dir/utilities.c.i

CMakeFiles/psearch1a.dir/utilities.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/psearch1a.dir/utilities.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/muhammet/CLionProjects/psearch1a/utilities.c -o CMakeFiles/psearch1a.dir/utilities.c.s

# Object files for target psearch1a
psearch1a_OBJECTS = \
"CMakeFiles/psearch1a.dir/main.c.o" \
"CMakeFiles/psearch1a.dir/utilities.c.o"

# External object files for target psearch1a
psearch1a_EXTERNAL_OBJECTS =

psearch1a: CMakeFiles/psearch1a.dir/main.c.o
psearch1a: CMakeFiles/psearch1a.dir/utilities.c.o
psearch1a: CMakeFiles/psearch1a.dir/build.make
psearch1a: CMakeFiles/psearch1a.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/muhammet/CLionProjects/psearch1a/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable psearch1a"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/psearch1a.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/psearch1a.dir/build: psearch1a

.PHONY : CMakeFiles/psearch1a.dir/build

CMakeFiles/psearch1a.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/psearch1a.dir/cmake_clean.cmake
.PHONY : CMakeFiles/psearch1a.dir/clean

CMakeFiles/psearch1a.dir/depend:
	cd /home/muhammet/CLionProjects/psearch1a/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/muhammet/CLionProjects/psearch1a /home/muhammet/CLionProjects/psearch1a /home/muhammet/CLionProjects/psearch1a/cmake-build-debug /home/muhammet/CLionProjects/psearch1a/cmake-build-debug /home/muhammet/CLionProjects/psearch1a/cmake-build-debug/CMakeFiles/psearch1a.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/psearch1a.dir/depend

