# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.12

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2018.2.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2018.2.3\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\Alexander\Downloads\ADS 2019\HW 5\Horses B (Graphs)"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\Alexander\Downloads\ADS 2019\HW 5\Horses B (Graphs)\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/MAIN.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/MAIN.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MAIN.dir/flags.make

CMakeFiles/MAIN.dir/main.cpp.obj: CMakeFiles/MAIN.dir/flags.make
CMakeFiles/MAIN.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\Alexander\Downloads\ADS 2019\HW 5\Horses B (Graphs)\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/MAIN.dir/main.cpp.obj"
	C:\MinGW\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\MAIN.dir\main.cpp.obj -c "C:\Users\Alexander\Downloads\ADS 2019\HW 5\Horses B (Graphs)\main.cpp"

CMakeFiles/MAIN.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MAIN.dir/main.cpp.i"
	C:\MinGW\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\Alexander\Downloads\ADS 2019\HW 5\Horses B (Graphs)\main.cpp" > CMakeFiles\MAIN.dir\main.cpp.i

CMakeFiles/MAIN.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MAIN.dir/main.cpp.s"
	C:\MinGW\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\Alexander\Downloads\ADS 2019\HW 5\Horses B (Graphs)\main.cpp" -o CMakeFiles\MAIN.dir\main.cpp.s

# Object files for target MAIN
MAIN_OBJECTS = \
"CMakeFiles/MAIN.dir/main.cpp.obj"

# External object files for target MAIN
MAIN_EXTERNAL_OBJECTS =

MAIN.exe: CMakeFiles/MAIN.dir/main.cpp.obj
MAIN.exe: CMakeFiles/MAIN.dir/build.make
MAIN.exe: CMakeFiles/MAIN.dir/linklibs.rsp
MAIN.exe: CMakeFiles/MAIN.dir/objects1.rsp
MAIN.exe: CMakeFiles/MAIN.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\Alexander\Downloads\ADS 2019\HW 5\Horses B (Graphs)\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable MAIN.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\MAIN.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MAIN.dir/build: MAIN.exe

.PHONY : CMakeFiles/MAIN.dir/build

CMakeFiles/MAIN.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\MAIN.dir\cmake_clean.cmake
.PHONY : CMakeFiles/MAIN.dir/clean

CMakeFiles/MAIN.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\Alexander\Downloads\ADS 2019\HW 5\Horses B (Graphs)" "C:\Users\Alexander\Downloads\ADS 2019\HW 5\Horses B (Graphs)" "C:\Users\Alexander\Downloads\ADS 2019\HW 5\Horses B (Graphs)\cmake-build-debug" "C:\Users\Alexander\Downloads\ADS 2019\HW 5\Horses B (Graphs)\cmake-build-debug" "C:\Users\Alexander\Downloads\ADS 2019\HW 5\Horses B (Graphs)\cmake-build-debug\CMakeFiles\MAIN.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/MAIN.dir/depend

