# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_SOURCE_DIR = /home/admin/uni_parallel_computing/1_seminar/GUI_1_seminar

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/admin/uni_parallel_computing/1_seminar/GUI_1_seminar/build/Desktop-Debug

# Include any dependencies generated for this target.
include CMakeFiles/GUI_1_seminar.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/GUI_1_seminar.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/GUI_1_seminar.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/GUI_1_seminar.dir/flags.make

GUI_1_seminar_autogen/timestamp: /home/admin/anaconda3/bin/moc
GUI_1_seminar_autogen/timestamp: /home/admin/anaconda3/bin/uic
GUI_1_seminar_autogen/timestamp: CMakeFiles/GUI_1_seminar.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/admin/uni_parallel_computing/1_seminar/GUI_1_seminar/build/Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target GUI_1_seminar"
	/usr/bin/cmake -E cmake_autogen /home/admin/uni_parallel_computing/1_seminar/GUI_1_seminar/build/Desktop-Debug/CMakeFiles/GUI_1_seminar_autogen.dir/AutogenInfo.json Debug
	/usr/bin/cmake -E touch /home/admin/uni_parallel_computing/1_seminar/GUI_1_seminar/build/Desktop-Debug/GUI_1_seminar_autogen/timestamp

CMakeFiles/GUI_1_seminar.dir/GUI_1_seminar_autogen/mocs_compilation.cpp.o: CMakeFiles/GUI_1_seminar.dir/flags.make
CMakeFiles/GUI_1_seminar.dir/GUI_1_seminar_autogen/mocs_compilation.cpp.o: GUI_1_seminar_autogen/mocs_compilation.cpp
CMakeFiles/GUI_1_seminar.dir/GUI_1_seminar_autogen/mocs_compilation.cpp.o: CMakeFiles/GUI_1_seminar.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/admin/uni_parallel_computing/1_seminar/GUI_1_seminar/build/Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/GUI_1_seminar.dir/GUI_1_seminar_autogen/mocs_compilation.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/GUI_1_seminar.dir/GUI_1_seminar_autogen/mocs_compilation.cpp.o -MF CMakeFiles/GUI_1_seminar.dir/GUI_1_seminar_autogen/mocs_compilation.cpp.o.d -o CMakeFiles/GUI_1_seminar.dir/GUI_1_seminar_autogen/mocs_compilation.cpp.o -c /home/admin/uni_parallel_computing/1_seminar/GUI_1_seminar/build/Desktop-Debug/GUI_1_seminar_autogen/mocs_compilation.cpp

CMakeFiles/GUI_1_seminar.dir/GUI_1_seminar_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/GUI_1_seminar.dir/GUI_1_seminar_autogen/mocs_compilation.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/admin/uni_parallel_computing/1_seminar/GUI_1_seminar/build/Desktop-Debug/GUI_1_seminar_autogen/mocs_compilation.cpp > CMakeFiles/GUI_1_seminar.dir/GUI_1_seminar_autogen/mocs_compilation.cpp.i

CMakeFiles/GUI_1_seminar.dir/GUI_1_seminar_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/GUI_1_seminar.dir/GUI_1_seminar_autogen/mocs_compilation.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/admin/uni_parallel_computing/1_seminar/GUI_1_seminar/build/Desktop-Debug/GUI_1_seminar_autogen/mocs_compilation.cpp -o CMakeFiles/GUI_1_seminar.dir/GUI_1_seminar_autogen/mocs_compilation.cpp.s

CMakeFiles/GUI_1_seminar.dir/main.cpp.o: CMakeFiles/GUI_1_seminar.dir/flags.make
CMakeFiles/GUI_1_seminar.dir/main.cpp.o: /home/admin/uni_parallel_computing/1_seminar/GUI_1_seminar/main.cpp
CMakeFiles/GUI_1_seminar.dir/main.cpp.o: CMakeFiles/GUI_1_seminar.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/admin/uni_parallel_computing/1_seminar/GUI_1_seminar/build/Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/GUI_1_seminar.dir/main.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/GUI_1_seminar.dir/main.cpp.o -MF CMakeFiles/GUI_1_seminar.dir/main.cpp.o.d -o CMakeFiles/GUI_1_seminar.dir/main.cpp.o -c /home/admin/uni_parallel_computing/1_seminar/GUI_1_seminar/main.cpp

CMakeFiles/GUI_1_seminar.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/GUI_1_seminar.dir/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/admin/uni_parallel_computing/1_seminar/GUI_1_seminar/main.cpp > CMakeFiles/GUI_1_seminar.dir/main.cpp.i

CMakeFiles/GUI_1_seminar.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/GUI_1_seminar.dir/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/admin/uni_parallel_computing/1_seminar/GUI_1_seminar/main.cpp -o CMakeFiles/GUI_1_seminar.dir/main.cpp.s

CMakeFiles/GUI_1_seminar.dir/mainwindow.cpp.o: CMakeFiles/GUI_1_seminar.dir/flags.make
CMakeFiles/GUI_1_seminar.dir/mainwindow.cpp.o: /home/admin/uni_parallel_computing/1_seminar/GUI_1_seminar/mainwindow.cpp
CMakeFiles/GUI_1_seminar.dir/mainwindow.cpp.o: CMakeFiles/GUI_1_seminar.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/admin/uni_parallel_computing/1_seminar/GUI_1_seminar/build/Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/GUI_1_seminar.dir/mainwindow.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/GUI_1_seminar.dir/mainwindow.cpp.o -MF CMakeFiles/GUI_1_seminar.dir/mainwindow.cpp.o.d -o CMakeFiles/GUI_1_seminar.dir/mainwindow.cpp.o -c /home/admin/uni_parallel_computing/1_seminar/GUI_1_seminar/mainwindow.cpp

CMakeFiles/GUI_1_seminar.dir/mainwindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/GUI_1_seminar.dir/mainwindow.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/admin/uni_parallel_computing/1_seminar/GUI_1_seminar/mainwindow.cpp > CMakeFiles/GUI_1_seminar.dir/mainwindow.cpp.i

CMakeFiles/GUI_1_seminar.dir/mainwindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/GUI_1_seminar.dir/mainwindow.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/admin/uni_parallel_computing/1_seminar/GUI_1_seminar/mainwindow.cpp -o CMakeFiles/GUI_1_seminar.dir/mainwindow.cpp.s

CMakeFiles/GUI_1_seminar.dir/sorting_results_window.cpp.o: CMakeFiles/GUI_1_seminar.dir/flags.make
CMakeFiles/GUI_1_seminar.dir/sorting_results_window.cpp.o: /home/admin/uni_parallel_computing/1_seminar/GUI_1_seminar/sorting_results_window.cpp
CMakeFiles/GUI_1_seminar.dir/sorting_results_window.cpp.o: CMakeFiles/GUI_1_seminar.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/admin/uni_parallel_computing/1_seminar/GUI_1_seminar/build/Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/GUI_1_seminar.dir/sorting_results_window.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/GUI_1_seminar.dir/sorting_results_window.cpp.o -MF CMakeFiles/GUI_1_seminar.dir/sorting_results_window.cpp.o.d -o CMakeFiles/GUI_1_seminar.dir/sorting_results_window.cpp.o -c /home/admin/uni_parallel_computing/1_seminar/GUI_1_seminar/sorting_results_window.cpp

CMakeFiles/GUI_1_seminar.dir/sorting_results_window.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/GUI_1_seminar.dir/sorting_results_window.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/admin/uni_parallel_computing/1_seminar/GUI_1_seminar/sorting_results_window.cpp > CMakeFiles/GUI_1_seminar.dir/sorting_results_window.cpp.i

CMakeFiles/GUI_1_seminar.dir/sorting_results_window.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/GUI_1_seminar.dir/sorting_results_window.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/admin/uni_parallel_computing/1_seminar/GUI_1_seminar/sorting_results_window.cpp -o CMakeFiles/GUI_1_seminar.dir/sorting_results_window.cpp.s

# Object files for target GUI_1_seminar
GUI_1_seminar_OBJECTS = \
"CMakeFiles/GUI_1_seminar.dir/GUI_1_seminar_autogen/mocs_compilation.cpp.o" \
"CMakeFiles/GUI_1_seminar.dir/main.cpp.o" \
"CMakeFiles/GUI_1_seminar.dir/mainwindow.cpp.o" \
"CMakeFiles/GUI_1_seminar.dir/sorting_results_window.cpp.o"

# External object files for target GUI_1_seminar
GUI_1_seminar_EXTERNAL_OBJECTS =

GUI_1_seminar: CMakeFiles/GUI_1_seminar.dir/GUI_1_seminar_autogen/mocs_compilation.cpp.o
GUI_1_seminar: CMakeFiles/GUI_1_seminar.dir/main.cpp.o
GUI_1_seminar: CMakeFiles/GUI_1_seminar.dir/mainwindow.cpp.o
GUI_1_seminar: CMakeFiles/GUI_1_seminar.dir/sorting_results_window.cpp.o
GUI_1_seminar: CMakeFiles/GUI_1_seminar.dir/build.make
GUI_1_seminar: /home/admin/anaconda3/lib/libQt5Widgets.so.5.15.2
GUI_1_seminar: /home/admin/anaconda3/lib/libQt5Gui.so.5.15.2
GUI_1_seminar: /home/admin/anaconda3/lib/libQt5Core.so.5.15.2
GUI_1_seminar: CMakeFiles/GUI_1_seminar.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/admin/uni_parallel_computing/1_seminar/GUI_1_seminar/build/Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable GUI_1_seminar"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/GUI_1_seminar.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/GUI_1_seminar.dir/build: GUI_1_seminar
.PHONY : CMakeFiles/GUI_1_seminar.dir/build

CMakeFiles/GUI_1_seminar.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/GUI_1_seminar.dir/cmake_clean.cmake
.PHONY : CMakeFiles/GUI_1_seminar.dir/clean

CMakeFiles/GUI_1_seminar.dir/depend: GUI_1_seminar_autogen/timestamp
	cd /home/admin/uni_parallel_computing/1_seminar/GUI_1_seminar/build/Desktop-Debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/admin/uni_parallel_computing/1_seminar/GUI_1_seminar /home/admin/uni_parallel_computing/1_seminar/GUI_1_seminar /home/admin/uni_parallel_computing/1_seminar/GUI_1_seminar/build/Desktop-Debug /home/admin/uni_parallel_computing/1_seminar/GUI_1_seminar/build/Desktop-Debug /home/admin/uni_parallel_computing/1_seminar/GUI_1_seminar/build/Desktop-Debug/CMakeFiles/GUI_1_seminar.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/GUI_1_seminar.dir/depend

