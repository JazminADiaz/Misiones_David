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
CMAKE_SOURCE_DIR = /home/jazmin/tuttifrutti/argos3-epuck/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jazmin/tuttifrutti/argos3-epuck/build

# Utility rule file for console_autogen.

# Include the progress variables for this target.
include testing/CMakeFiles/console_autogen.dir/progress.make

testing/CMakeFiles/console_autogen:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/jazmin/tuttifrutti/argos3-epuck/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC for target console"
	cd /home/jazmin/tuttifrutti/argos3-epuck/build/testing && /usr/bin/cmake -E cmake_autogen /home/jazmin/tuttifrutti/argos3-epuck/build/testing/CMakeFiles/console_autogen.dir/AutogenInfo.json Release

console_autogen: testing/CMakeFiles/console_autogen
console_autogen: testing/CMakeFiles/console_autogen.dir/build.make

.PHONY : console_autogen

# Rule to build all files generated by this target.
testing/CMakeFiles/console_autogen.dir/build: console_autogen

.PHONY : testing/CMakeFiles/console_autogen.dir/build

testing/CMakeFiles/console_autogen.dir/clean:
	cd /home/jazmin/tuttifrutti/argos3-epuck/build/testing && $(CMAKE_COMMAND) -P CMakeFiles/console_autogen.dir/cmake_clean.cmake
.PHONY : testing/CMakeFiles/console_autogen.dir/clean

testing/CMakeFiles/console_autogen.dir/depend:
	cd /home/jazmin/tuttifrutti/argos3-epuck/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jazmin/tuttifrutti/argos3-epuck/src /home/jazmin/tuttifrutti/argos3-epuck/src/testing /home/jazmin/tuttifrutti/argos3-epuck/build /home/jazmin/tuttifrutti/argos3-epuck/build/testing /home/jazmin/tuttifrutti/argos3-epuck/build/testing/CMakeFiles/console_autogen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : testing/CMakeFiles/console_autogen.dir/depend

