# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /home/dyh/app/clion-2020.2.3/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/dyh/app/clion-2020.2.3/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/dyh/workspace/cpp/cpp_socket_demo/server

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dyh/workspace/cpp/cpp_socket_demo/server/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/server.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/server.dir/flags.make

CMakeFiles/server.dir/test-server.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/test-server.cpp.o: ../test-server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dyh/workspace/cpp/cpp_socket_demo/server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/server.dir/test-server.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/test-server.cpp.o -c /home/dyh/workspace/cpp/cpp_socket_demo/server/test-server.cpp

CMakeFiles/server.dir/test-server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/test-server.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dyh/workspace/cpp/cpp_socket_demo/server/test-server.cpp > CMakeFiles/server.dir/test-server.cpp.i

CMakeFiles/server.dir/test-server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/test-server.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dyh/workspace/cpp/cpp_socket_demo/server/test-server.cpp -o CMakeFiles/server.dir/test-server.cpp.s

CMakeFiles/server.dir/server.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/server.cpp.o: ../server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dyh/workspace/cpp/cpp_socket_demo/server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/server.dir/server.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/server.cpp.o -c /home/dyh/workspace/cpp/cpp_socket_demo/server/server.cpp

CMakeFiles/server.dir/server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/server.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dyh/workspace/cpp/cpp_socket_demo/server/server.cpp > CMakeFiles/server.dir/server.cpp.i

CMakeFiles/server.dir/server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/server.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dyh/workspace/cpp/cpp_socket_demo/server/server.cpp -o CMakeFiles/server.dir/server.cpp.s

CMakeFiles/server.dir/message.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/message.cpp.o: ../message.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dyh/workspace/cpp/cpp_socket_demo/server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/server.dir/message.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/message.cpp.o -c /home/dyh/workspace/cpp/cpp_socket_demo/server/message.cpp

CMakeFiles/server.dir/message.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/message.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dyh/workspace/cpp/cpp_socket_demo/server/message.cpp > CMakeFiles/server.dir/message.cpp.i

CMakeFiles/server.dir/message.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/message.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dyh/workspace/cpp/cpp_socket_demo/server/message.cpp -o CMakeFiles/server.dir/message.cpp.s

# Object files for target server
server_OBJECTS = \
"CMakeFiles/server.dir/test-server.cpp.o" \
"CMakeFiles/server.dir/server.cpp.o" \
"CMakeFiles/server.dir/message.cpp.o"

# External object files for target server
server_EXTERNAL_OBJECTS =

server: CMakeFiles/server.dir/test-server.cpp.o
server: CMakeFiles/server.dir/server.cpp.o
server: CMakeFiles/server.dir/message.cpp.o
server: CMakeFiles/server.dir/build.make
server: /usr/lib/x86_64-linux-gnu/libopencv_shape.so.3.2.0
server: /usr/lib/x86_64-linux-gnu/libopencv_stitching.so.3.2.0
server: /usr/lib/x86_64-linux-gnu/libopencv_superres.so.3.2.0
server: /usr/lib/x86_64-linux-gnu/libopencv_videostab.so.3.2.0
server: /usr/lib/x86_64-linux-gnu/libopencv_aruco.so.3.2.0
server: /usr/lib/x86_64-linux-gnu/libopencv_bgsegm.so.3.2.0
server: /usr/lib/x86_64-linux-gnu/libopencv_bioinspired.so.3.2.0
server: /usr/lib/x86_64-linux-gnu/libopencv_ccalib.so.3.2.0
server: /usr/lib/x86_64-linux-gnu/libopencv_datasets.so.3.2.0
server: /usr/lib/x86_64-linux-gnu/libopencv_dpm.so.3.2.0
server: /usr/lib/x86_64-linux-gnu/libopencv_face.so.3.2.0
server: /usr/lib/x86_64-linux-gnu/libopencv_freetype.so.3.2.0
server: /usr/lib/x86_64-linux-gnu/libopencv_fuzzy.so.3.2.0
server: /usr/lib/x86_64-linux-gnu/libopencv_hdf.so.3.2.0
server: /usr/lib/x86_64-linux-gnu/libopencv_line_descriptor.so.3.2.0
server: /usr/lib/x86_64-linux-gnu/libopencv_optflow.so.3.2.0
server: /usr/lib/x86_64-linux-gnu/libopencv_plot.so.3.2.0
server: /usr/lib/x86_64-linux-gnu/libopencv_reg.so.3.2.0
server: /usr/lib/x86_64-linux-gnu/libopencv_saliency.so.3.2.0
server: /usr/lib/x86_64-linux-gnu/libopencv_stereo.so.3.2.0
server: /usr/lib/x86_64-linux-gnu/libopencv_structured_light.so.3.2.0
server: /usr/lib/x86_64-linux-gnu/libopencv_surface_matching.so.3.2.0
server: /usr/lib/x86_64-linux-gnu/libopencv_text.so.3.2.0
server: /usr/lib/x86_64-linux-gnu/libopencv_ximgproc.so.3.2.0
server: /usr/lib/x86_64-linux-gnu/libopencv_xobjdetect.so.3.2.0
server: /usr/lib/x86_64-linux-gnu/libopencv_xphoto.so.3.2.0
server: /usr/lib/x86_64-linux-gnu/libopencv_video.so.3.2.0
server: /usr/lib/x86_64-linux-gnu/libopencv_viz.so.3.2.0
server: /usr/lib/x86_64-linux-gnu/libopencv_phase_unwrapping.so.3.2.0
server: /usr/lib/x86_64-linux-gnu/libopencv_rgbd.so.3.2.0
server: /usr/lib/x86_64-linux-gnu/libopencv_calib3d.so.3.2.0
server: /usr/lib/x86_64-linux-gnu/libopencv_features2d.so.3.2.0
server: /usr/lib/x86_64-linux-gnu/libopencv_flann.so.3.2.0
server: /usr/lib/x86_64-linux-gnu/libopencv_objdetect.so.3.2.0
server: /usr/lib/x86_64-linux-gnu/libopencv_ml.so.3.2.0
server: /usr/lib/x86_64-linux-gnu/libopencv_highgui.so.3.2.0
server: /usr/lib/x86_64-linux-gnu/libopencv_photo.so.3.2.0
server: /usr/lib/x86_64-linux-gnu/libopencv_videoio.so.3.2.0
server: /usr/lib/x86_64-linux-gnu/libopencv_imgcodecs.so.3.2.0
server: /usr/lib/x86_64-linux-gnu/libopencv_imgproc.so.3.2.0
server: /usr/lib/x86_64-linux-gnu/libopencv_core.so.3.2.0
server: CMakeFiles/server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dyh/workspace/cpp/cpp_socket_demo/server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/server.dir/build: server

.PHONY : CMakeFiles/server.dir/build

CMakeFiles/server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/server.dir/clean

CMakeFiles/server.dir/depend:
	cd /home/dyh/workspace/cpp/cpp_socket_demo/server/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dyh/workspace/cpp/cpp_socket_demo/server /home/dyh/workspace/cpp/cpp_socket_demo/server /home/dyh/workspace/cpp/cpp_socket_demo/server/cmake-build-debug /home/dyh/workspace/cpp/cpp_socket_demo/server/cmake-build-debug /home/dyh/workspace/cpp/cpp_socket_demo/server/cmake-build-debug/CMakeFiles/server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/server.dir/depend
