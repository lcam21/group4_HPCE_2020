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
CMAKE_SOURCE_DIR = /home/luis/group4_HPCE_2020/project_2/Prototyping

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/luis/group4_HPCE_2020/project_2/Prototyping

# Include any dependencies generated for this target.
include CMakeFiles/rgb2yuv_OpenCV.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/rgb2yuv_OpenCV.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/rgb2yuv_OpenCV.dir/flags.make

CMakeFiles/rgb2yuv_OpenCV.dir/rgb2yuv_OpenCV.cpp.o: CMakeFiles/rgb2yuv_OpenCV.dir/flags.make
CMakeFiles/rgb2yuv_OpenCV.dir/rgb2yuv_OpenCV.cpp.o: rgb2yuv_OpenCV.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/luis/group4_HPCE_2020/project_2/Prototyping/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/rgb2yuv_OpenCV.dir/rgb2yuv_OpenCV.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/rgb2yuv_OpenCV.dir/rgb2yuv_OpenCV.cpp.o -c /home/luis/group4_HPCE_2020/project_2/Prototyping/rgb2yuv_OpenCV.cpp

CMakeFiles/rgb2yuv_OpenCV.dir/rgb2yuv_OpenCV.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rgb2yuv_OpenCV.dir/rgb2yuv_OpenCV.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/luis/group4_HPCE_2020/project_2/Prototyping/rgb2yuv_OpenCV.cpp > CMakeFiles/rgb2yuv_OpenCV.dir/rgb2yuv_OpenCV.cpp.i

CMakeFiles/rgb2yuv_OpenCV.dir/rgb2yuv_OpenCV.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rgb2yuv_OpenCV.dir/rgb2yuv_OpenCV.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/luis/group4_HPCE_2020/project_2/Prototyping/rgb2yuv_OpenCV.cpp -o CMakeFiles/rgb2yuv_OpenCV.dir/rgb2yuv_OpenCV.cpp.s

CMakeFiles/rgb2yuv_OpenCV.dir/rgb2yuv_OpenCV.cpp.o.requires:

.PHONY : CMakeFiles/rgb2yuv_OpenCV.dir/rgb2yuv_OpenCV.cpp.o.requires

CMakeFiles/rgb2yuv_OpenCV.dir/rgb2yuv_OpenCV.cpp.o.provides: CMakeFiles/rgb2yuv_OpenCV.dir/rgb2yuv_OpenCV.cpp.o.requires
	$(MAKE) -f CMakeFiles/rgb2yuv_OpenCV.dir/build.make CMakeFiles/rgb2yuv_OpenCV.dir/rgb2yuv_OpenCV.cpp.o.provides.build
.PHONY : CMakeFiles/rgb2yuv_OpenCV.dir/rgb2yuv_OpenCV.cpp.o.provides

CMakeFiles/rgb2yuv_OpenCV.dir/rgb2yuv_OpenCV.cpp.o.provides.build: CMakeFiles/rgb2yuv_OpenCV.dir/rgb2yuv_OpenCV.cpp.o


# Object files for target rgb2yuv_OpenCV
rgb2yuv_OpenCV_OBJECTS = \
"CMakeFiles/rgb2yuv_OpenCV.dir/rgb2yuv_OpenCV.cpp.o"

# External object files for target rgb2yuv_OpenCV
rgb2yuv_OpenCV_EXTERNAL_OBJECTS =

rgb2yuv_OpenCV: CMakeFiles/rgb2yuv_OpenCV.dir/rgb2yuv_OpenCV.cpp.o
rgb2yuv_OpenCV: CMakeFiles/rgb2yuv_OpenCV.dir/build.make
rgb2yuv_OpenCV: /usr/local/lib/libopencv_dnn.so.4.4.0
rgb2yuv_OpenCV: /usr/local/lib/libopencv_gapi.so.4.4.0
rgb2yuv_OpenCV: /usr/local/lib/libopencv_highgui.so.4.4.0
rgb2yuv_OpenCV: /usr/local/lib/libopencv_ml.so.4.4.0
rgb2yuv_OpenCV: /usr/local/lib/libopencv_objdetect.so.4.4.0
rgb2yuv_OpenCV: /usr/local/lib/libopencv_photo.so.4.4.0
rgb2yuv_OpenCV: /usr/local/lib/libopencv_stitching.so.4.4.0
rgb2yuv_OpenCV: /usr/local/lib/libopencv_video.so.4.4.0
rgb2yuv_OpenCV: /usr/local/lib/libopencv_videoio.so.4.4.0
rgb2yuv_OpenCV: /usr/local/lib/libopencv_imgcodecs.so.4.4.0
rgb2yuv_OpenCV: /usr/local/lib/libopencv_calib3d.so.4.4.0
rgb2yuv_OpenCV: /usr/local/lib/libopencv_features2d.so.4.4.0
rgb2yuv_OpenCV: /usr/local/lib/libopencv_flann.so.4.4.0
rgb2yuv_OpenCV: /usr/local/lib/libopencv_imgproc.so.4.4.0
rgb2yuv_OpenCV: /usr/local/lib/libopencv_core.so.4.4.0
rgb2yuv_OpenCV: CMakeFiles/rgb2yuv_OpenCV.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/luis/group4_HPCE_2020/project_2/Prototyping/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable rgb2yuv_OpenCV"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/rgb2yuv_OpenCV.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/rgb2yuv_OpenCV.dir/build: rgb2yuv_OpenCV

.PHONY : CMakeFiles/rgb2yuv_OpenCV.dir/build

CMakeFiles/rgb2yuv_OpenCV.dir/requires: CMakeFiles/rgb2yuv_OpenCV.dir/rgb2yuv_OpenCV.cpp.o.requires

.PHONY : CMakeFiles/rgb2yuv_OpenCV.dir/requires

CMakeFiles/rgb2yuv_OpenCV.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/rgb2yuv_OpenCV.dir/cmake_clean.cmake
.PHONY : CMakeFiles/rgb2yuv_OpenCV.dir/clean

CMakeFiles/rgb2yuv_OpenCV.dir/depend:
	cd /home/luis/group4_HPCE_2020/project_2/Prototyping && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/luis/group4_HPCE_2020/project_2/Prototyping /home/luis/group4_HPCE_2020/project_2/Prototyping /home/luis/group4_HPCE_2020/project_2/Prototyping /home/luis/group4_HPCE_2020/project_2/Prototyping /home/luis/group4_HPCE_2020/project_2/Prototyping/CMakeFiles/rgb2yuv_OpenCV.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/rgb2yuv_OpenCV.dir/depend

