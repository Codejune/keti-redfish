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
CMAKE_SOURCE_DIR = /root/CMM_SDK/source/keti-redfish

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/CMM_SDK/source/keti-redfish

# Include any dependencies generated for this target.
include src/CMakeFiles/keti-redfish.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/keti-redfish.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/keti-redfish.dir/flags.make

src/CMakeFiles/keti-redfish.dir/main.cpp.o: src/CMakeFiles/keti-redfish.dir/flags.make
src/CMakeFiles/keti-redfish.dir/main.cpp.o: src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/CMM_SDK/source/keti-redfish/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/keti-redfish.dir/main.cpp.o"
	cd /root/CMM_SDK/source/keti-redfish/src && /root/CMM_SDK/output/host/usr/bin/arm-linux-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/keti-redfish.dir/main.cpp.o -c /root/CMM_SDK/source/keti-redfish/src/main.cpp

src/CMakeFiles/keti-redfish.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/keti-redfish.dir/main.cpp.i"
	cd /root/CMM_SDK/source/keti-redfish/src && /root/CMM_SDK/output/host/usr/bin/arm-linux-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/CMM_SDK/source/keti-redfish/src/main.cpp > CMakeFiles/keti-redfish.dir/main.cpp.i

src/CMakeFiles/keti-redfish.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/keti-redfish.dir/main.cpp.s"
	cd /root/CMM_SDK/source/keti-redfish/src && /root/CMM_SDK/output/host/usr/bin/arm-linux-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/CMM_SDK/source/keti-redfish/src/main.cpp -o CMakeFiles/keti-redfish.dir/main.cpp.s

src/CMakeFiles/keti-redfish.dir/handler.cpp.o: src/CMakeFiles/keti-redfish.dir/flags.make
src/CMakeFiles/keti-redfish.dir/handler.cpp.o: src/handler.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/CMM_SDK/source/keti-redfish/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/keti-redfish.dir/handler.cpp.o"
	cd /root/CMM_SDK/source/keti-redfish/src && /root/CMM_SDK/output/host/usr/bin/arm-linux-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/keti-redfish.dir/handler.cpp.o -c /root/CMM_SDK/source/keti-redfish/src/handler.cpp

src/CMakeFiles/keti-redfish.dir/handler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/keti-redfish.dir/handler.cpp.i"
	cd /root/CMM_SDK/source/keti-redfish/src && /root/CMM_SDK/output/host/usr/bin/arm-linux-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/CMM_SDK/source/keti-redfish/src/handler.cpp > CMakeFiles/keti-redfish.dir/handler.cpp.i

src/CMakeFiles/keti-redfish.dir/handler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/keti-redfish.dir/handler.cpp.s"
	cd /root/CMM_SDK/source/keti-redfish/src && /root/CMM_SDK/output/host/usr/bin/arm-linux-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/CMM_SDK/source/keti-redfish/src/handler.cpp -o CMakeFiles/keti-redfish.dir/handler.cpp.s

src/CMakeFiles/keti-redfish.dir/resource.cpp.o: src/CMakeFiles/keti-redfish.dir/flags.make
src/CMakeFiles/keti-redfish.dir/resource.cpp.o: src/resource.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/CMM_SDK/source/keti-redfish/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/CMakeFiles/keti-redfish.dir/resource.cpp.o"
	cd /root/CMM_SDK/source/keti-redfish/src && /root/CMM_SDK/output/host/usr/bin/arm-linux-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/keti-redfish.dir/resource.cpp.o -c /root/CMM_SDK/source/keti-redfish/src/resource.cpp

src/CMakeFiles/keti-redfish.dir/resource.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/keti-redfish.dir/resource.cpp.i"
	cd /root/CMM_SDK/source/keti-redfish/src && /root/CMM_SDK/output/host/usr/bin/arm-linux-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/CMM_SDK/source/keti-redfish/src/resource.cpp > CMakeFiles/keti-redfish.dir/resource.cpp.i

src/CMakeFiles/keti-redfish.dir/resource.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/keti-redfish.dir/resource.cpp.s"
	cd /root/CMM_SDK/source/keti-redfish/src && /root/CMM_SDK/output/host/usr/bin/arm-linux-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/CMM_SDK/source/keti-redfish/src/resource.cpp -o CMakeFiles/keti-redfish.dir/resource.cpp.s

# Object files for target keti-redfish
keti__redfish_OBJECTS = \
"CMakeFiles/keti-redfish.dir/main.cpp.o" \
"CMakeFiles/keti-redfish.dir/handler.cpp.o" \
"CMakeFiles/keti-redfish.dir/resource.cpp.o"

# External object files for target keti-redfish
keti__redfish_EXTERNAL_OBJECTS =

src/keti-redfish: src/CMakeFiles/keti-redfish.dir/main.cpp.o
src/keti-redfish: src/CMakeFiles/keti-redfish.dir/handler.cpp.o
src/keti-redfish: src/CMakeFiles/keti-redfish.dir/resource.cpp.o
src/keti-redfish: src/CMakeFiles/keti-redfish.dir/build.make
src/keti-redfish: src/CMakeFiles/keti-redfish.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/CMM_SDK/source/keti-redfish/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable keti-redfish"
	cd /root/CMM_SDK/source/keti-redfish/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/keti-redfish.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/keti-redfish.dir/build: src/keti-redfish

.PHONY : src/CMakeFiles/keti-redfish.dir/build

src/CMakeFiles/keti-redfish.dir/clean:
	cd /root/CMM_SDK/source/keti-redfish/src && $(CMAKE_COMMAND) -P CMakeFiles/keti-redfish.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/keti-redfish.dir/clean

src/CMakeFiles/keti-redfish.dir/depend:
	cd /root/CMM_SDK/source/keti-redfish && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/CMM_SDK/source/keti-redfish /root/CMM_SDK/source/keti-redfish/src /root/CMM_SDK/source/keti-redfish /root/CMM_SDK/source/keti-redfish/src /root/CMM_SDK/source/keti-redfish/src/CMakeFiles/keti-redfish.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/keti-redfish.dir/depend
