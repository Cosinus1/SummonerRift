# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/paul/Documents/REVA/OpenGL/SummonerRift

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/paul/Documents/REVA/OpenGL/SummonerRift/build

# Include any dependencies generated for this target.
include CMakeFiles/SummonerRift.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/SummonerRift.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/SummonerRift.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SummonerRift.dir/flags.make

CMakeFiles/SummonerRift.dir/Camera.cpp.o: CMakeFiles/SummonerRift.dir/flags.make
CMakeFiles/SummonerRift.dir/Camera.cpp.o: ../Camera.cpp
CMakeFiles/SummonerRift.dir/Camera.cpp.o: CMakeFiles/SummonerRift.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/paul/Documents/REVA/OpenGL/SummonerRift/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/SummonerRift.dir/Camera.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/SummonerRift.dir/Camera.cpp.o -MF CMakeFiles/SummonerRift.dir/Camera.cpp.o.d -o CMakeFiles/SummonerRift.dir/Camera.cpp.o -c /home/paul/Documents/REVA/OpenGL/SummonerRift/Camera.cpp

CMakeFiles/SummonerRift.dir/Camera.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SummonerRift.dir/Camera.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/paul/Documents/REVA/OpenGL/SummonerRift/Camera.cpp > CMakeFiles/SummonerRift.dir/Camera.cpp.i

CMakeFiles/SummonerRift.dir/Camera.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SummonerRift.dir/Camera.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/paul/Documents/REVA/OpenGL/SummonerRift/Camera.cpp -o CMakeFiles/SummonerRift.dir/Camera.cpp.s

CMakeFiles/SummonerRift.dir/Rift.cpp.o: CMakeFiles/SummonerRift.dir/flags.make
CMakeFiles/SummonerRift.dir/Rift.cpp.o: ../Rift.cpp
CMakeFiles/SummonerRift.dir/Rift.cpp.o: CMakeFiles/SummonerRift.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/paul/Documents/REVA/OpenGL/SummonerRift/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/SummonerRift.dir/Rift.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/SummonerRift.dir/Rift.cpp.o -MF CMakeFiles/SummonerRift.dir/Rift.cpp.o.d -o CMakeFiles/SummonerRift.dir/Rift.cpp.o -c /home/paul/Documents/REVA/OpenGL/SummonerRift/Rift.cpp

CMakeFiles/SummonerRift.dir/Rift.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SummonerRift.dir/Rift.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/paul/Documents/REVA/OpenGL/SummonerRift/Rift.cpp > CMakeFiles/SummonerRift.dir/Rift.cpp.i

CMakeFiles/SummonerRift.dir/Rift.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SummonerRift.dir/Rift.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/paul/Documents/REVA/OpenGL/SummonerRift/Rift.cpp -o CMakeFiles/SummonerRift.dir/Rift.cpp.s

CMakeFiles/SummonerRift.dir/Mesh.cpp.o: CMakeFiles/SummonerRift.dir/flags.make
CMakeFiles/SummonerRift.dir/Mesh.cpp.o: ../Mesh.cpp
CMakeFiles/SummonerRift.dir/Mesh.cpp.o: CMakeFiles/SummonerRift.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/paul/Documents/REVA/OpenGL/SummonerRift/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/SummonerRift.dir/Mesh.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/SummonerRift.dir/Mesh.cpp.o -MF CMakeFiles/SummonerRift.dir/Mesh.cpp.o.d -o CMakeFiles/SummonerRift.dir/Mesh.cpp.o -c /home/paul/Documents/REVA/OpenGL/SummonerRift/Mesh.cpp

CMakeFiles/SummonerRift.dir/Mesh.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SummonerRift.dir/Mesh.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/paul/Documents/REVA/OpenGL/SummonerRift/Mesh.cpp > CMakeFiles/SummonerRift.dir/Mesh.cpp.i

CMakeFiles/SummonerRift.dir/Mesh.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SummonerRift.dir/Mesh.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/paul/Documents/REVA/OpenGL/SummonerRift/Mesh.cpp -o CMakeFiles/SummonerRift.dir/Mesh.cpp.s

CMakeFiles/SummonerRift.dir/ShaderProgram.cpp.o: CMakeFiles/SummonerRift.dir/flags.make
CMakeFiles/SummonerRift.dir/ShaderProgram.cpp.o: ../ShaderProgram.cpp
CMakeFiles/SummonerRift.dir/ShaderProgram.cpp.o: CMakeFiles/SummonerRift.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/paul/Documents/REVA/OpenGL/SummonerRift/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/SummonerRift.dir/ShaderProgram.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/SummonerRift.dir/ShaderProgram.cpp.o -MF CMakeFiles/SummonerRift.dir/ShaderProgram.cpp.o.d -o CMakeFiles/SummonerRift.dir/ShaderProgram.cpp.o -c /home/paul/Documents/REVA/OpenGL/SummonerRift/ShaderProgram.cpp

CMakeFiles/SummonerRift.dir/ShaderProgram.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SummonerRift.dir/ShaderProgram.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/paul/Documents/REVA/OpenGL/SummonerRift/ShaderProgram.cpp > CMakeFiles/SummonerRift.dir/ShaderProgram.cpp.i

CMakeFiles/SummonerRift.dir/ShaderProgram.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SummonerRift.dir/ShaderProgram.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/paul/Documents/REVA/OpenGL/SummonerRift/ShaderProgram.cpp -o CMakeFiles/SummonerRift.dir/ShaderProgram.cpp.s

CMakeFiles/SummonerRift.dir/Texture2D.cpp.o: CMakeFiles/SummonerRift.dir/flags.make
CMakeFiles/SummonerRift.dir/Texture2D.cpp.o: ../Texture2D.cpp
CMakeFiles/SummonerRift.dir/Texture2D.cpp.o: CMakeFiles/SummonerRift.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/paul/Documents/REVA/OpenGL/SummonerRift/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/SummonerRift.dir/Texture2D.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/SummonerRift.dir/Texture2D.cpp.o -MF CMakeFiles/SummonerRift.dir/Texture2D.cpp.o.d -o CMakeFiles/SummonerRift.dir/Texture2D.cpp.o -c /home/paul/Documents/REVA/OpenGL/SummonerRift/Texture2D.cpp

CMakeFiles/SummonerRift.dir/Texture2D.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SummonerRift.dir/Texture2D.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/paul/Documents/REVA/OpenGL/SummonerRift/Texture2D.cpp > CMakeFiles/SummonerRift.dir/Texture2D.cpp.i

CMakeFiles/SummonerRift.dir/Texture2D.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SummonerRift.dir/Texture2D.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/paul/Documents/REVA/OpenGL/SummonerRift/Texture2D.cpp -o CMakeFiles/SummonerRift.dir/Texture2D.cpp.s

# Object files for target SummonerRift
SummonerRift_OBJECTS = \
"CMakeFiles/SummonerRift.dir/Camera.cpp.o" \
"CMakeFiles/SummonerRift.dir/Rift.cpp.o" \
"CMakeFiles/SummonerRift.dir/Mesh.cpp.o" \
"CMakeFiles/SummonerRift.dir/ShaderProgram.cpp.o" \
"CMakeFiles/SummonerRift.dir/Texture2D.cpp.o"

# External object files for target SummonerRift
SummonerRift_EXTERNAL_OBJECTS =

SummonerRift: CMakeFiles/SummonerRift.dir/Camera.cpp.o
SummonerRift: CMakeFiles/SummonerRift.dir/Rift.cpp.o
SummonerRift: CMakeFiles/SummonerRift.dir/Mesh.cpp.o
SummonerRift: CMakeFiles/SummonerRift.dir/ShaderProgram.cpp.o
SummonerRift: CMakeFiles/SummonerRift.dir/Texture2D.cpp.o
SummonerRift: CMakeFiles/SummonerRift.dir/build.make
SummonerRift: libtinygltf.a
SummonerRift: CMakeFiles/SummonerRift.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/paul/Documents/REVA/OpenGL/SummonerRift/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable SummonerRift"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SummonerRift.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SummonerRift.dir/build: SummonerRift
.PHONY : CMakeFiles/SummonerRift.dir/build

CMakeFiles/SummonerRift.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SummonerRift.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SummonerRift.dir/clean

CMakeFiles/SummonerRift.dir/depend:
	cd /home/paul/Documents/REVA/OpenGL/SummonerRift/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/paul/Documents/REVA/OpenGL/SummonerRift /home/paul/Documents/REVA/OpenGL/SummonerRift /home/paul/Documents/REVA/OpenGL/SummonerRift/build /home/paul/Documents/REVA/OpenGL/SummonerRift/build /home/paul/Documents/REVA/OpenGL/SummonerRift/build/CMakeFiles/SummonerRift.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/SummonerRift.dir/depend

