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
CMAKE_SOURCE_DIR = /home/muhammet/CLionProjects/project1/psearch2d

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/muhammet/CLionProjects/project1/psearch2d/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/psearch2d.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/psearch2d.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/psearch2d.dir/flags.make

CMakeFiles/psearch2d.dir/main.c.o: CMakeFiles/psearch2d.dir/flags.make
CMakeFiles/psearch2d.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/muhammet/CLionProjects/project1/psearch2d/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/psearch2d.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/psearch2d.dir/main.c.o   -c /home/muhammet/CLionProjects/project1/psearch2d/main.c

CMakeFiles/psearch2d.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/psearch2d.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/muhammet/CLionProjects/project1/psearch2d/main.c > CMakeFiles/psearch2d.dir/main.c.i

CMakeFiles/psearch2d.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/psearch2d.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/muhammet/CLionProjects/project1/psearch2d/main.c -o CMakeFiles/psearch2d.dir/main.c.s

CMakeFiles/psearch2d.dir/utilities.c.o: CMakeFiles/psearch2d.dir/flags.make
CMakeFiles/psearch2d.dir/utilities.c.o: ../utilities.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/muhammet/CLionProjects/project1/psearch2d/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/psearch2d.dir/utilities.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/psearch2d.dir/utilities.c.o   -c /home/muhammet/CLionProjects/project1/psearch2d/utilities.c

CMakeFiles/psearch2d.dir/utilities.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/psearch2d.dir/utilities.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/muhammet/CLionProjects/project1/psearch2d/utilities.c > CMakeFiles/psearch2d.dir/utilities.c.i

CMakeFiles/psearch2d.dir/utilities.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/psearch2d.dir/utilities.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/muhammet/CLionProjects/project1/psearch2d/utilities.c -o CMakeFiles/psearch2d.dir/utilities.c.s

# Object files for target psearch2d
psearch2d_OBJECTS = \
"CMakeFiles/psearch2d.dir/main.c.o" \
"CMakeFiles/psearch2d.dir/utilities.c.o"

# External object files for target psearch2d
psearch2d_EXTERNAL_OBJECTS =

psearch2d: CMakeFiles/psearch2d.dir/main.c.o
psearch2d: CMakeFiles/psearch2d.dir/utilities.c.o
psearch2d: CMakeFiles/psearch2d.dir/build.make
psearch2d: CMakeFiles/psearch2d.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/muhammet/CLionProjects/project1/psearch2d/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable psearch2d"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/psearch2d.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/psearch2d.dir/build: psearch2d

.PHONY : CMakeFiles/psearch2d.dir/build

CMakeFiles/psearch2d.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/psearch2d.dir/cmake_clean.cmake
.PHONY : CMakeFiles/psearch2d.dir/clean

CMakeFiles/psearch2d.dir/depend:
	cd /home/muhammet/CLionProjects/project1/psearch2d/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/muhammet/CLionProjects/project1/psearch2d /home/muhammet/CLionProjects/project1/psearch2d /home/muhammet/CLionProjects/project1/psearch2d/cmake-build-debug /home/muhammet/CLionProjects/project1/psearch2d/cmake-build-debug /home/muhammet/CLionProjects/project1/psearch2d/cmake-build-debug/CMakeFiles/psearch2d.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/psearch2d.dir/depend

