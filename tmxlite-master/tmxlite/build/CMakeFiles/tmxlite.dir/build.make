# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /mnt/c/Users/Julie/Documents/Github/Genesis/tmxlite-master/tmxlite

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/Julie/Documents/Github/Genesis/tmxlite-master/tmxlite/build

# Include any dependencies generated for this target.
include CMakeFiles/tmxlite.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/tmxlite.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tmxlite.dir/flags.make

CMakeFiles/tmxlite.dir/src/detail/pugixml.cpp.o: CMakeFiles/tmxlite.dir/flags.make
CMakeFiles/tmxlite.dir/src/detail/pugixml.cpp.o: ../src/detail/pugixml.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Julie/Documents/Github/Genesis/tmxlite-master/tmxlite/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/tmxlite.dir/src/detail/pugixml.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tmxlite.dir/src/detail/pugixml.cpp.o -c /mnt/c/Users/Julie/Documents/Github/Genesis/tmxlite-master/tmxlite/src/detail/pugixml.cpp

CMakeFiles/tmxlite.dir/src/detail/pugixml.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tmxlite.dir/src/detail/pugixml.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/Julie/Documents/Github/Genesis/tmxlite-master/tmxlite/src/detail/pugixml.cpp > CMakeFiles/tmxlite.dir/src/detail/pugixml.cpp.i

CMakeFiles/tmxlite.dir/src/detail/pugixml.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tmxlite.dir/src/detail/pugixml.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/Julie/Documents/Github/Genesis/tmxlite-master/tmxlite/src/detail/pugixml.cpp -o CMakeFiles/tmxlite.dir/src/detail/pugixml.cpp.s

CMakeFiles/tmxlite.dir/src/detail/pugixml.cpp.o.requires:

.PHONY : CMakeFiles/tmxlite.dir/src/detail/pugixml.cpp.o.requires

CMakeFiles/tmxlite.dir/src/detail/pugixml.cpp.o.provides: CMakeFiles/tmxlite.dir/src/detail/pugixml.cpp.o.requires
	$(MAKE) -f CMakeFiles/tmxlite.dir/build.make CMakeFiles/tmxlite.dir/src/detail/pugixml.cpp.o.provides.build
.PHONY : CMakeFiles/tmxlite.dir/src/detail/pugixml.cpp.o.provides

CMakeFiles/tmxlite.dir/src/detail/pugixml.cpp.o.provides.build: CMakeFiles/tmxlite.dir/src/detail/pugixml.cpp.o


CMakeFiles/tmxlite.dir/src/FreeFuncs.cpp.o: CMakeFiles/tmxlite.dir/flags.make
CMakeFiles/tmxlite.dir/src/FreeFuncs.cpp.o: ../src/FreeFuncs.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Julie/Documents/Github/Genesis/tmxlite-master/tmxlite/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/tmxlite.dir/src/FreeFuncs.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tmxlite.dir/src/FreeFuncs.cpp.o -c /mnt/c/Users/Julie/Documents/Github/Genesis/tmxlite-master/tmxlite/src/FreeFuncs.cpp

CMakeFiles/tmxlite.dir/src/FreeFuncs.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tmxlite.dir/src/FreeFuncs.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/Julie/Documents/Github/Genesis/tmxlite-master/tmxlite/src/FreeFuncs.cpp > CMakeFiles/tmxlite.dir/src/FreeFuncs.cpp.i

CMakeFiles/tmxlite.dir/src/FreeFuncs.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tmxlite.dir/src/FreeFuncs.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/Julie/Documents/Github/Genesis/tmxlite-master/tmxlite/src/FreeFuncs.cpp -o CMakeFiles/tmxlite.dir/src/FreeFuncs.cpp.s

CMakeFiles/tmxlite.dir/src/FreeFuncs.cpp.o.requires:

.PHONY : CMakeFiles/tmxlite.dir/src/FreeFuncs.cpp.o.requires

CMakeFiles/tmxlite.dir/src/FreeFuncs.cpp.o.provides: CMakeFiles/tmxlite.dir/src/FreeFuncs.cpp.o.requires
	$(MAKE) -f CMakeFiles/tmxlite.dir/build.make CMakeFiles/tmxlite.dir/src/FreeFuncs.cpp.o.provides.build
.PHONY : CMakeFiles/tmxlite.dir/src/FreeFuncs.cpp.o.provides

CMakeFiles/tmxlite.dir/src/FreeFuncs.cpp.o.provides.build: CMakeFiles/tmxlite.dir/src/FreeFuncs.cpp.o


CMakeFiles/tmxlite.dir/src/ImageLayer.cpp.o: CMakeFiles/tmxlite.dir/flags.make
CMakeFiles/tmxlite.dir/src/ImageLayer.cpp.o: ../src/ImageLayer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Julie/Documents/Github/Genesis/tmxlite-master/tmxlite/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/tmxlite.dir/src/ImageLayer.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tmxlite.dir/src/ImageLayer.cpp.o -c /mnt/c/Users/Julie/Documents/Github/Genesis/tmxlite-master/tmxlite/src/ImageLayer.cpp

CMakeFiles/tmxlite.dir/src/ImageLayer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tmxlite.dir/src/ImageLayer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/Julie/Documents/Github/Genesis/tmxlite-master/tmxlite/src/ImageLayer.cpp > CMakeFiles/tmxlite.dir/src/ImageLayer.cpp.i

CMakeFiles/tmxlite.dir/src/ImageLayer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tmxlite.dir/src/ImageLayer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/Julie/Documents/Github/Genesis/tmxlite-master/tmxlite/src/ImageLayer.cpp -o CMakeFiles/tmxlite.dir/src/ImageLayer.cpp.s

CMakeFiles/tmxlite.dir/src/ImageLayer.cpp.o.requires:

.PHONY : CMakeFiles/tmxlite.dir/src/ImageLayer.cpp.o.requires

CMakeFiles/tmxlite.dir/src/ImageLayer.cpp.o.provides: CMakeFiles/tmxlite.dir/src/ImageLayer.cpp.o.requires
	$(MAKE) -f CMakeFiles/tmxlite.dir/build.make CMakeFiles/tmxlite.dir/src/ImageLayer.cpp.o.provides.build
.PHONY : CMakeFiles/tmxlite.dir/src/ImageLayer.cpp.o.provides

CMakeFiles/tmxlite.dir/src/ImageLayer.cpp.o.provides.build: CMakeFiles/tmxlite.dir/src/ImageLayer.cpp.o


CMakeFiles/tmxlite.dir/src/Map.cpp.o: CMakeFiles/tmxlite.dir/flags.make
CMakeFiles/tmxlite.dir/src/Map.cpp.o: ../src/Map.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Julie/Documents/Github/Genesis/tmxlite-master/tmxlite/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/tmxlite.dir/src/Map.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tmxlite.dir/src/Map.cpp.o -c /mnt/c/Users/Julie/Documents/Github/Genesis/tmxlite-master/tmxlite/src/Map.cpp

CMakeFiles/tmxlite.dir/src/Map.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tmxlite.dir/src/Map.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/Julie/Documents/Github/Genesis/tmxlite-master/tmxlite/src/Map.cpp > CMakeFiles/tmxlite.dir/src/Map.cpp.i

CMakeFiles/tmxlite.dir/src/Map.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tmxlite.dir/src/Map.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/Julie/Documents/Github/Genesis/tmxlite-master/tmxlite/src/Map.cpp -o CMakeFiles/tmxlite.dir/src/Map.cpp.s

CMakeFiles/tmxlite.dir/src/Map.cpp.o.requires:

.PHONY : CMakeFiles/tmxlite.dir/src/Map.cpp.o.requires

CMakeFiles/tmxlite.dir/src/Map.cpp.o.provides: CMakeFiles/tmxlite.dir/src/Map.cpp.o.requires
	$(MAKE) -f CMakeFiles/tmxlite.dir/build.make CMakeFiles/tmxlite.dir/src/Map.cpp.o.provides.build
.PHONY : CMakeFiles/tmxlite.dir/src/Map.cpp.o.provides

CMakeFiles/tmxlite.dir/src/Map.cpp.o.provides.build: CMakeFiles/tmxlite.dir/src/Map.cpp.o


CMakeFiles/tmxlite.dir/src/miniz.c.o: CMakeFiles/tmxlite.dir/flags.make
CMakeFiles/tmxlite.dir/src/miniz.c.o: ../src/miniz.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Julie/Documents/Github/Genesis/tmxlite-master/tmxlite/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/tmxlite.dir/src/miniz.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/tmxlite.dir/src/miniz.c.o   -c /mnt/c/Users/Julie/Documents/Github/Genesis/tmxlite-master/tmxlite/src/miniz.c

CMakeFiles/tmxlite.dir/src/miniz.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tmxlite.dir/src/miniz.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/Julie/Documents/Github/Genesis/tmxlite-master/tmxlite/src/miniz.c > CMakeFiles/tmxlite.dir/src/miniz.c.i

CMakeFiles/tmxlite.dir/src/miniz.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tmxlite.dir/src/miniz.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/Julie/Documents/Github/Genesis/tmxlite-master/tmxlite/src/miniz.c -o CMakeFiles/tmxlite.dir/src/miniz.c.s

CMakeFiles/tmxlite.dir/src/miniz.c.o.requires:

.PHONY : CMakeFiles/tmxlite.dir/src/miniz.c.o.requires

CMakeFiles/tmxlite.dir/src/miniz.c.o.provides: CMakeFiles/tmxlite.dir/src/miniz.c.o.requires
	$(MAKE) -f CMakeFiles/tmxlite.dir/build.make CMakeFiles/tmxlite.dir/src/miniz.c.o.provides.build
.PHONY : CMakeFiles/tmxlite.dir/src/miniz.c.o.provides

CMakeFiles/tmxlite.dir/src/miniz.c.o.provides.build: CMakeFiles/tmxlite.dir/src/miniz.c.o


CMakeFiles/tmxlite.dir/src/Object.cpp.o: CMakeFiles/tmxlite.dir/flags.make
CMakeFiles/tmxlite.dir/src/Object.cpp.o: ../src/Object.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Julie/Documents/Github/Genesis/tmxlite-master/tmxlite/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/tmxlite.dir/src/Object.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tmxlite.dir/src/Object.cpp.o -c /mnt/c/Users/Julie/Documents/Github/Genesis/tmxlite-master/tmxlite/src/Object.cpp

CMakeFiles/tmxlite.dir/src/Object.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tmxlite.dir/src/Object.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/Julie/Documents/Github/Genesis/tmxlite-master/tmxlite/src/Object.cpp > CMakeFiles/tmxlite.dir/src/Object.cpp.i

CMakeFiles/tmxlite.dir/src/Object.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tmxlite.dir/src/Object.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/Julie/Documents/Github/Genesis/tmxlite-master/tmxlite/src/Object.cpp -o CMakeFiles/tmxlite.dir/src/Object.cpp.s

CMakeFiles/tmxlite.dir/src/Object.cpp.o.requires:

.PHONY : CMakeFiles/tmxlite.dir/src/Object.cpp.o.requires

CMakeFiles/tmxlite.dir/src/Object.cpp.o.provides: CMakeFiles/tmxlite.dir/src/Object.cpp.o.requires
	$(MAKE) -f CMakeFiles/tmxlite.dir/build.make CMakeFiles/tmxlite.dir/src/Object.cpp.o.provides.build
.PHONY : CMakeFiles/tmxlite.dir/src/Object.cpp.o.provides

CMakeFiles/tmxlite.dir/src/Object.cpp.o.provides.build: CMakeFiles/tmxlite.dir/src/Object.cpp.o


CMakeFiles/tmxlite.dir/src/ObjectGroup.cpp.o: CMakeFiles/tmxlite.dir/flags.make
CMakeFiles/tmxlite.dir/src/ObjectGroup.cpp.o: ../src/ObjectGroup.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Julie/Documents/Github/Genesis/tmxlite-master/tmxlite/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/tmxlite.dir/src/ObjectGroup.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tmxlite.dir/src/ObjectGroup.cpp.o -c /mnt/c/Users/Julie/Documents/Github/Genesis/tmxlite-master/tmxlite/src/ObjectGroup.cpp

CMakeFiles/tmxlite.dir/src/ObjectGroup.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tmxlite.dir/src/ObjectGroup.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/Julie/Documents/Github/Genesis/tmxlite-master/tmxlite/src/ObjectGroup.cpp > CMakeFiles/tmxlite.dir/src/ObjectGroup.cpp.i

CMakeFiles/tmxlite.dir/src/ObjectGroup.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tmxlite.dir/src/ObjectGroup.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/Julie/Documents/Github/Genesis/tmxlite-master/tmxlite/src/ObjectGroup.cpp -o CMakeFiles/tmxlite.dir/src/ObjectGroup.cpp.s

CMakeFiles/tmxlite.dir/src/ObjectGroup.cpp.o.requires:

.PHONY : CMakeFiles/tmxlite.dir/src/ObjectGroup.cpp.o.requires

CMakeFiles/tmxlite.dir/src/ObjectGroup.cpp.o.provides: CMakeFiles/tmxlite.dir/src/ObjectGroup.cpp.o.requires
	$(MAKE) -f CMakeFiles/tmxlite.dir/build.make CMakeFiles/tmxlite.dir/src/ObjectGroup.cpp.o.provides.build
.PHONY : CMakeFiles/tmxlite.dir/src/ObjectGroup.cpp.o.provides

CMakeFiles/tmxlite.dir/src/ObjectGroup.cpp.o.provides.build: CMakeFiles/tmxlite.dir/src/ObjectGroup.cpp.o


CMakeFiles/tmxlite.dir/src/Property.cpp.o: CMakeFiles/tmxlite.dir/flags.make
CMakeFiles/tmxlite.dir/src/Property.cpp.o: ../src/Property.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Julie/Documents/Github/Genesis/tmxlite-master/tmxlite/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/tmxlite.dir/src/Property.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tmxlite.dir/src/Property.cpp.o -c /mnt/c/Users/Julie/Documents/Github/Genesis/tmxlite-master/tmxlite/src/Property.cpp

CMakeFiles/tmxlite.dir/src/Property.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tmxlite.dir/src/Property.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/Julie/Documents/Github/Genesis/tmxlite-master/tmxlite/src/Property.cpp > CMakeFiles/tmxlite.dir/src/Property.cpp.i

CMakeFiles/tmxlite.dir/src/Property.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tmxlite.dir/src/Property.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/Julie/Documents/Github/Genesis/tmxlite-master/tmxlite/src/Property.cpp -o CMakeFiles/tmxlite.dir/src/Property.cpp.s

CMakeFiles/tmxlite.dir/src/Property.cpp.o.requires:

.PHONY : CMakeFiles/tmxlite.dir/src/Property.cpp.o.requires

CMakeFiles/tmxlite.dir/src/Property.cpp.o.provides: CMakeFiles/tmxlite.dir/src/Property.cpp.o.requires
	$(MAKE) -f CMakeFiles/tmxlite.dir/build.make CMakeFiles/tmxlite.dir/src/Property.cpp.o.provides.build
.PHONY : CMakeFiles/tmxlite.dir/src/Property.cpp.o.provides

CMakeFiles/tmxlite.dir/src/Property.cpp.o.provides.build: CMakeFiles/tmxlite.dir/src/Property.cpp.o


CMakeFiles/tmxlite.dir/src/TileLayer.cpp.o: CMakeFiles/tmxlite.dir/flags.make
CMakeFiles/tmxlite.dir/src/TileLayer.cpp.o: ../src/TileLayer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Julie/Documents/Github/Genesis/tmxlite-master/tmxlite/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/tmxlite.dir/src/TileLayer.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tmxlite.dir/src/TileLayer.cpp.o -c /mnt/c/Users/Julie/Documents/Github/Genesis/tmxlite-master/tmxlite/src/TileLayer.cpp

CMakeFiles/tmxlite.dir/src/TileLayer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tmxlite.dir/src/TileLayer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/Julie/Documents/Github/Genesis/tmxlite-master/tmxlite/src/TileLayer.cpp > CMakeFiles/tmxlite.dir/src/TileLayer.cpp.i

CMakeFiles/tmxlite.dir/src/TileLayer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tmxlite.dir/src/TileLayer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/Julie/Documents/Github/Genesis/tmxlite-master/tmxlite/src/TileLayer.cpp -o CMakeFiles/tmxlite.dir/src/TileLayer.cpp.s

CMakeFiles/tmxlite.dir/src/TileLayer.cpp.o.requires:

.PHONY : CMakeFiles/tmxlite.dir/src/TileLayer.cpp.o.requires

CMakeFiles/tmxlite.dir/src/TileLayer.cpp.o.provides: CMakeFiles/tmxlite.dir/src/TileLayer.cpp.o.requires
	$(MAKE) -f CMakeFiles/tmxlite.dir/build.make CMakeFiles/tmxlite.dir/src/TileLayer.cpp.o.provides.build
.PHONY : CMakeFiles/tmxlite.dir/src/TileLayer.cpp.o.provides

CMakeFiles/tmxlite.dir/src/TileLayer.cpp.o.provides.build: CMakeFiles/tmxlite.dir/src/TileLayer.cpp.o


CMakeFiles/tmxlite.dir/src/LayerGroup.cpp.o: CMakeFiles/tmxlite.dir/flags.make
CMakeFiles/tmxlite.dir/src/LayerGroup.cpp.o: ../src/LayerGroup.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Julie/Documents/Github/Genesis/tmxlite-master/tmxlite/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/tmxlite.dir/src/LayerGroup.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tmxlite.dir/src/LayerGroup.cpp.o -c /mnt/c/Users/Julie/Documents/Github/Genesis/tmxlite-master/tmxlite/src/LayerGroup.cpp

CMakeFiles/tmxlite.dir/src/LayerGroup.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tmxlite.dir/src/LayerGroup.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/Julie/Documents/Github/Genesis/tmxlite-master/tmxlite/src/LayerGroup.cpp > CMakeFiles/tmxlite.dir/src/LayerGroup.cpp.i

CMakeFiles/tmxlite.dir/src/LayerGroup.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tmxlite.dir/src/LayerGroup.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/Julie/Documents/Github/Genesis/tmxlite-master/tmxlite/src/LayerGroup.cpp -o CMakeFiles/tmxlite.dir/src/LayerGroup.cpp.s

CMakeFiles/tmxlite.dir/src/LayerGroup.cpp.o.requires:

.PHONY : CMakeFiles/tmxlite.dir/src/LayerGroup.cpp.o.requires

CMakeFiles/tmxlite.dir/src/LayerGroup.cpp.o.provides: CMakeFiles/tmxlite.dir/src/LayerGroup.cpp.o.requires
	$(MAKE) -f CMakeFiles/tmxlite.dir/build.make CMakeFiles/tmxlite.dir/src/LayerGroup.cpp.o.provides.build
.PHONY : CMakeFiles/tmxlite.dir/src/LayerGroup.cpp.o.provides

CMakeFiles/tmxlite.dir/src/LayerGroup.cpp.o.provides.build: CMakeFiles/tmxlite.dir/src/LayerGroup.cpp.o


CMakeFiles/tmxlite.dir/src/Tileset.cpp.o: CMakeFiles/tmxlite.dir/flags.make
CMakeFiles/tmxlite.dir/src/Tileset.cpp.o: ../src/Tileset.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Julie/Documents/Github/Genesis/tmxlite-master/tmxlite/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/tmxlite.dir/src/Tileset.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tmxlite.dir/src/Tileset.cpp.o -c /mnt/c/Users/Julie/Documents/Github/Genesis/tmxlite-master/tmxlite/src/Tileset.cpp

CMakeFiles/tmxlite.dir/src/Tileset.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tmxlite.dir/src/Tileset.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/Julie/Documents/Github/Genesis/tmxlite-master/tmxlite/src/Tileset.cpp > CMakeFiles/tmxlite.dir/src/Tileset.cpp.i

CMakeFiles/tmxlite.dir/src/Tileset.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tmxlite.dir/src/Tileset.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/Julie/Documents/Github/Genesis/tmxlite-master/tmxlite/src/Tileset.cpp -o CMakeFiles/tmxlite.dir/src/Tileset.cpp.s

CMakeFiles/tmxlite.dir/src/Tileset.cpp.o.requires:

.PHONY : CMakeFiles/tmxlite.dir/src/Tileset.cpp.o.requires

CMakeFiles/tmxlite.dir/src/Tileset.cpp.o.provides: CMakeFiles/tmxlite.dir/src/Tileset.cpp.o.requires
	$(MAKE) -f CMakeFiles/tmxlite.dir/build.make CMakeFiles/tmxlite.dir/src/Tileset.cpp.o.provides.build
.PHONY : CMakeFiles/tmxlite.dir/src/Tileset.cpp.o.provides

CMakeFiles/tmxlite.dir/src/Tileset.cpp.o.provides.build: CMakeFiles/tmxlite.dir/src/Tileset.cpp.o


# Object files for target tmxlite
tmxlite_OBJECTS = \
"CMakeFiles/tmxlite.dir/src/detail/pugixml.cpp.o" \
"CMakeFiles/tmxlite.dir/src/FreeFuncs.cpp.o" \
"CMakeFiles/tmxlite.dir/src/ImageLayer.cpp.o" \
"CMakeFiles/tmxlite.dir/src/Map.cpp.o" \
"CMakeFiles/tmxlite.dir/src/miniz.c.o" \
"CMakeFiles/tmxlite.dir/src/Object.cpp.o" \
"CMakeFiles/tmxlite.dir/src/ObjectGroup.cpp.o" \
"CMakeFiles/tmxlite.dir/src/Property.cpp.o" \
"CMakeFiles/tmxlite.dir/src/TileLayer.cpp.o" \
"CMakeFiles/tmxlite.dir/src/LayerGroup.cpp.o" \
"CMakeFiles/tmxlite.dir/src/Tileset.cpp.o"

# External object files for target tmxlite
tmxlite_EXTERNAL_OBJECTS =

libtmxlite.so: CMakeFiles/tmxlite.dir/src/detail/pugixml.cpp.o
libtmxlite.so: CMakeFiles/tmxlite.dir/src/FreeFuncs.cpp.o
libtmxlite.so: CMakeFiles/tmxlite.dir/src/ImageLayer.cpp.o
libtmxlite.so: CMakeFiles/tmxlite.dir/src/Map.cpp.o
libtmxlite.so: CMakeFiles/tmxlite.dir/src/miniz.c.o
libtmxlite.so: CMakeFiles/tmxlite.dir/src/Object.cpp.o
libtmxlite.so: CMakeFiles/tmxlite.dir/src/ObjectGroup.cpp.o
libtmxlite.so: CMakeFiles/tmxlite.dir/src/Property.cpp.o
libtmxlite.so: CMakeFiles/tmxlite.dir/src/TileLayer.cpp.o
libtmxlite.so: CMakeFiles/tmxlite.dir/src/LayerGroup.cpp.o
libtmxlite.so: CMakeFiles/tmxlite.dir/src/Tileset.cpp.o
libtmxlite.so: CMakeFiles/tmxlite.dir/build.make
libtmxlite.so: CMakeFiles/tmxlite.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/Julie/Documents/Github/Genesis/tmxlite-master/tmxlite/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Linking CXX shared library libtmxlite.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tmxlite.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tmxlite.dir/build: libtmxlite.so

.PHONY : CMakeFiles/tmxlite.dir/build

CMakeFiles/tmxlite.dir/requires: CMakeFiles/tmxlite.dir/src/detail/pugixml.cpp.o.requires
CMakeFiles/tmxlite.dir/requires: CMakeFiles/tmxlite.dir/src/FreeFuncs.cpp.o.requires
CMakeFiles/tmxlite.dir/requires: CMakeFiles/tmxlite.dir/src/ImageLayer.cpp.o.requires
CMakeFiles/tmxlite.dir/requires: CMakeFiles/tmxlite.dir/src/Map.cpp.o.requires
CMakeFiles/tmxlite.dir/requires: CMakeFiles/tmxlite.dir/src/miniz.c.o.requires
CMakeFiles/tmxlite.dir/requires: CMakeFiles/tmxlite.dir/src/Object.cpp.o.requires
CMakeFiles/tmxlite.dir/requires: CMakeFiles/tmxlite.dir/src/ObjectGroup.cpp.o.requires
CMakeFiles/tmxlite.dir/requires: CMakeFiles/tmxlite.dir/src/Property.cpp.o.requires
CMakeFiles/tmxlite.dir/requires: CMakeFiles/tmxlite.dir/src/TileLayer.cpp.o.requires
CMakeFiles/tmxlite.dir/requires: CMakeFiles/tmxlite.dir/src/LayerGroup.cpp.o.requires
CMakeFiles/tmxlite.dir/requires: CMakeFiles/tmxlite.dir/src/Tileset.cpp.o.requires

.PHONY : CMakeFiles/tmxlite.dir/requires

CMakeFiles/tmxlite.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tmxlite.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tmxlite.dir/clean

CMakeFiles/tmxlite.dir/depend:
	cd /mnt/c/Users/Julie/Documents/Github/Genesis/tmxlite-master/tmxlite/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/Julie/Documents/Github/Genesis/tmxlite-master/tmxlite /mnt/c/Users/Julie/Documents/Github/Genesis/tmxlite-master/tmxlite /mnt/c/Users/Julie/Documents/Github/Genesis/tmxlite-master/tmxlite/build /mnt/c/Users/Julie/Documents/Github/Genesis/tmxlite-master/tmxlite/build /mnt/c/Users/Julie/Documents/Github/Genesis/tmxlite-master/tmxlite/build/CMakeFiles/tmxlite.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tmxlite.dir/depend

