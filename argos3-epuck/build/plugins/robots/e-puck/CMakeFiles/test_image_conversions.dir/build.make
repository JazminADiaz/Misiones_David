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

# Include any dependencies generated for this target.
include plugins/robots/e-puck/CMakeFiles/test_image_conversions.dir/depend.make

# Include the progress variables for this target.
include plugins/robots/e-puck/CMakeFiles/test_image_conversions.dir/progress.make

# Include the compile flags for this target's objects.
include plugins/robots/e-puck/CMakeFiles/test_image_conversions.dir/flags.make

plugins/robots/e-puck/CMakeFiles/test_image_conversions.dir/test_image_conversions_autogen/mocs_compilation.cpp.o: plugins/robots/e-puck/CMakeFiles/test_image_conversions.dir/flags.make
plugins/robots/e-puck/CMakeFiles/test_image_conversions.dir/test_image_conversions_autogen/mocs_compilation.cpp.o: plugins/robots/e-puck/test_image_conversions_autogen/mocs_compilation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jazmin/tuttifrutti/argos3-epuck/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object plugins/robots/e-puck/CMakeFiles/test_image_conversions.dir/test_image_conversions_autogen/mocs_compilation.cpp.o"
	cd /home/jazmin/tuttifrutti/argos3-epuck/build/plugins/robots/e-puck && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_image_conversions.dir/test_image_conversions_autogen/mocs_compilation.cpp.o -c /home/jazmin/tuttifrutti/argos3-epuck/build/plugins/robots/e-puck/test_image_conversions_autogen/mocs_compilation.cpp

plugins/robots/e-puck/CMakeFiles/test_image_conversions.dir/test_image_conversions_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_image_conversions.dir/test_image_conversions_autogen/mocs_compilation.cpp.i"
	cd /home/jazmin/tuttifrutti/argos3-epuck/build/plugins/robots/e-puck && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jazmin/tuttifrutti/argos3-epuck/build/plugins/robots/e-puck/test_image_conversions_autogen/mocs_compilation.cpp > CMakeFiles/test_image_conversions.dir/test_image_conversions_autogen/mocs_compilation.cpp.i

plugins/robots/e-puck/CMakeFiles/test_image_conversions.dir/test_image_conversions_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_image_conversions.dir/test_image_conversions_autogen/mocs_compilation.cpp.s"
	cd /home/jazmin/tuttifrutti/argos3-epuck/build/plugins/robots/e-puck && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jazmin/tuttifrutti/argos3-epuck/build/plugins/robots/e-puck/test_image_conversions_autogen/mocs_compilation.cpp -o CMakeFiles/test_image_conversions.dir/test_image_conversions_autogen/mocs_compilation.cpp.s

plugins/robots/e-puck/CMakeFiles/test_image_conversions.dir/real_robot/vision/image.cpp.o: plugins/robots/e-puck/CMakeFiles/test_image_conversions.dir/flags.make
plugins/robots/e-puck/CMakeFiles/test_image_conversions.dir/real_robot/vision/image.cpp.o: /home/jazmin/tuttifrutti/argos3-epuck/src/plugins/robots/e-puck/real_robot/vision/image.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jazmin/tuttifrutti/argos3-epuck/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object plugins/robots/e-puck/CMakeFiles/test_image_conversions.dir/real_robot/vision/image.cpp.o"
	cd /home/jazmin/tuttifrutti/argos3-epuck/build/plugins/robots/e-puck && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_image_conversions.dir/real_robot/vision/image.cpp.o -c /home/jazmin/tuttifrutti/argos3-epuck/src/plugins/robots/e-puck/real_robot/vision/image.cpp

plugins/robots/e-puck/CMakeFiles/test_image_conversions.dir/real_robot/vision/image.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_image_conversions.dir/real_robot/vision/image.cpp.i"
	cd /home/jazmin/tuttifrutti/argos3-epuck/build/plugins/robots/e-puck && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jazmin/tuttifrutti/argos3-epuck/src/plugins/robots/e-puck/real_robot/vision/image.cpp > CMakeFiles/test_image_conversions.dir/real_robot/vision/image.cpp.i

plugins/robots/e-puck/CMakeFiles/test_image_conversions.dir/real_robot/vision/image.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_image_conversions.dir/real_robot/vision/image.cpp.s"
	cd /home/jazmin/tuttifrutti/argos3-epuck/build/plugins/robots/e-puck && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jazmin/tuttifrutti/argos3-epuck/src/plugins/robots/e-puck/real_robot/vision/image.cpp -o CMakeFiles/test_image_conversions.dir/real_robot/vision/image.cpp.s

plugins/robots/e-puck/CMakeFiles/test_image_conversions.dir/real_robot/vision/test_image_conversions.cpp.o: plugins/robots/e-puck/CMakeFiles/test_image_conversions.dir/flags.make
plugins/robots/e-puck/CMakeFiles/test_image_conversions.dir/real_robot/vision/test_image_conversions.cpp.o: /home/jazmin/tuttifrutti/argos3-epuck/src/plugins/robots/e-puck/real_robot/vision/test_image_conversions.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jazmin/tuttifrutti/argos3-epuck/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object plugins/robots/e-puck/CMakeFiles/test_image_conversions.dir/real_robot/vision/test_image_conversions.cpp.o"
	cd /home/jazmin/tuttifrutti/argos3-epuck/build/plugins/robots/e-puck && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_image_conversions.dir/real_robot/vision/test_image_conversions.cpp.o -c /home/jazmin/tuttifrutti/argos3-epuck/src/plugins/robots/e-puck/real_robot/vision/test_image_conversions.cpp

plugins/robots/e-puck/CMakeFiles/test_image_conversions.dir/real_robot/vision/test_image_conversions.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_image_conversions.dir/real_robot/vision/test_image_conversions.cpp.i"
	cd /home/jazmin/tuttifrutti/argos3-epuck/build/plugins/robots/e-puck && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jazmin/tuttifrutti/argos3-epuck/src/plugins/robots/e-puck/real_robot/vision/test_image_conversions.cpp > CMakeFiles/test_image_conversions.dir/real_robot/vision/test_image_conversions.cpp.i

plugins/robots/e-puck/CMakeFiles/test_image_conversions.dir/real_robot/vision/test_image_conversions.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_image_conversions.dir/real_robot/vision/test_image_conversions.cpp.s"
	cd /home/jazmin/tuttifrutti/argos3-epuck/build/plugins/robots/e-puck && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jazmin/tuttifrutti/argos3-epuck/src/plugins/robots/e-puck/real_robot/vision/test_image_conversions.cpp -o CMakeFiles/test_image_conversions.dir/real_robot/vision/test_image_conversions.cpp.s

# Object files for target test_image_conversions
test_image_conversions_OBJECTS = \
"CMakeFiles/test_image_conversions.dir/test_image_conversions_autogen/mocs_compilation.cpp.o" \
"CMakeFiles/test_image_conversions.dir/real_robot/vision/image.cpp.o" \
"CMakeFiles/test_image_conversions.dir/real_robot/vision/test_image_conversions.cpp.o"

# External object files for target test_image_conversions
test_image_conversions_EXTERNAL_OBJECTS =

plugins/robots/e-puck/test_image_conversions: plugins/robots/e-puck/CMakeFiles/test_image_conversions.dir/test_image_conversions_autogen/mocs_compilation.cpp.o
plugins/robots/e-puck/test_image_conversions: plugins/robots/e-puck/CMakeFiles/test_image_conversions.dir/real_robot/vision/image.cpp.o
plugins/robots/e-puck/test_image_conversions: plugins/robots/e-puck/CMakeFiles/test_image_conversions.dir/real_robot/vision/test_image_conversions.cpp.o
plugins/robots/e-puck/test_image_conversions: plugins/robots/e-puck/CMakeFiles/test_image_conversions.dir/build.make
plugins/robots/e-puck/test_image_conversions: plugins/robots/e-puck/CMakeFiles/test_image_conversions.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jazmin/tuttifrutti/argos3-epuck/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable test_image_conversions"
	cd /home/jazmin/tuttifrutti/argos3-epuck/build/plugins/robots/e-puck && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_image_conversions.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
plugins/robots/e-puck/CMakeFiles/test_image_conversions.dir/build: plugins/robots/e-puck/test_image_conversions

.PHONY : plugins/robots/e-puck/CMakeFiles/test_image_conversions.dir/build

plugins/robots/e-puck/CMakeFiles/test_image_conversions.dir/clean:
	cd /home/jazmin/tuttifrutti/argos3-epuck/build/plugins/robots/e-puck && $(CMAKE_COMMAND) -P CMakeFiles/test_image_conversions.dir/cmake_clean.cmake
.PHONY : plugins/robots/e-puck/CMakeFiles/test_image_conversions.dir/clean

plugins/robots/e-puck/CMakeFiles/test_image_conversions.dir/depend:
	cd /home/jazmin/tuttifrutti/argos3-epuck/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jazmin/tuttifrutti/argos3-epuck/src /home/jazmin/tuttifrutti/argos3-epuck/src/plugins/robots/e-puck /home/jazmin/tuttifrutti/argos3-epuck/build /home/jazmin/tuttifrutti/argos3-epuck/build/plugins/robots/e-puck /home/jazmin/tuttifrutti/argos3-epuck/build/plugins/robots/e-puck/CMakeFiles/test_image_conversions.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : plugins/robots/e-puck/CMakeFiles/test_image_conversions.dir/depend
