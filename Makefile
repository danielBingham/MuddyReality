# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
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

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/dbingham/Source/middle-earth-mud/alpha6

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dbingham/Source/middle-earth-mud/alpha6

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running interactive CMake command-line interface..."
	/usr/bin/cmake -i .
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/dbingham/Source/middle-earth-mud/alpha6/CMakeFiles /home/dbingham/Source/middle-earth-mud/alpha6/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/dbingham/Source/middle-earth-mud/alpha6/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named muddyreality

# Build rule for target.
muddyreality: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 muddyreality
.PHONY : muddyreality

# fast build rule for target.
muddyreality/fast:
	$(MAKE) -f CMakeFiles/muddyreality.dir/build.make CMakeFiles/muddyreality.dir/build
.PHONY : muddyreality/fast

# target to build an object file
src/Player/player.o:
	$(MAKE) -f CMakeFiles/muddyreality.dir/build.make CMakeFiles/muddyreality.dir/src/Player/player.o
.PHONY : src/Player/player.o

# target to preprocess a source file
src/Player/player.i:
	$(MAKE) -f CMakeFiles/muddyreality.dir/build.make CMakeFiles/muddyreality.dir/src/Player/player.i
.PHONY : src/Player/player.i

# target to generate assembly for a file
src/Player/player.s:
	$(MAKE) -f CMakeFiles/muddyreality.dir/build.make CMakeFiles/muddyreality.dir/src/Player/player.s
.PHONY : src/Player/player.s

# target to build an object file
src/interpreter/Account/accountCommands.o:
	$(MAKE) -f CMakeFiles/muddyreality.dir/build.make CMakeFiles/muddyreality.dir/src/interpreter/Account/accountCommands.o
.PHONY : src/interpreter/Account/accountCommands.o

# target to preprocess a source file
src/interpreter/Account/accountCommands.i:
	$(MAKE) -f CMakeFiles/muddyreality.dir/build.make CMakeFiles/muddyreality.dir/src/interpreter/Account/accountCommands.i
.PHONY : src/interpreter/Account/accountCommands.i

# target to generate assembly for a file
src/interpreter/Account/accountCommands.s:
	$(MAKE) -f CMakeFiles/muddyreality.dir/build.make CMakeFiles/muddyreality.dir/src/interpreter/Account/accountCommands.s
.PHONY : src/interpreter/Account/accountCommands.s

# target to build an object file
src/interpreter/Command/commandInterpreter.o:
	$(MAKE) -f CMakeFiles/muddyreality.dir/build.make CMakeFiles/muddyreality.dir/src/interpreter/Command/commandInterpreter.o
.PHONY : src/interpreter/Command/commandInterpreter.o

# target to preprocess a source file
src/interpreter/Command/commandInterpreter.i:
	$(MAKE) -f CMakeFiles/muddyreality.dir/build.make CMakeFiles/muddyreality.dir/src/interpreter/Command/commandInterpreter.i
.PHONY : src/interpreter/Command/commandInterpreter.i

# target to generate assembly for a file
src/interpreter/Command/commandInterpreter.s:
	$(MAKE) -f CMakeFiles/muddyreality.dir/build.make CMakeFiles/muddyreality.dir/src/interpreter/Command/commandInterpreter.s
.PHONY : src/interpreter/Command/commandInterpreter.s

# target to build an object file
src/interpreter/Creation/creationStates.o:
	$(MAKE) -f CMakeFiles/muddyreality.dir/build.make CMakeFiles/muddyreality.dir/src/interpreter/Creation/creationStates.o
.PHONY : src/interpreter/Creation/creationStates.o

# target to preprocess a source file
src/interpreter/Creation/creationStates.i:
	$(MAKE) -f CMakeFiles/muddyreality.dir/build.make CMakeFiles/muddyreality.dir/src/interpreter/Creation/creationStates.i
.PHONY : src/interpreter/Creation/creationStates.i

# target to generate assembly for a file
src/interpreter/Creation/creationStates.s:
	$(MAKE) -f CMakeFiles/muddyreality.dir/build.make CMakeFiles/muddyreality.dir/src/interpreter/Creation/creationStates.s
.PHONY : src/interpreter/Creation/creationStates.s

# target to build an object file
src/interpreter/Entrance/entranceCommands.o:
	$(MAKE) -f CMakeFiles/muddyreality.dir/build.make CMakeFiles/muddyreality.dir/src/interpreter/Entrance/entranceCommands.o
.PHONY : src/interpreter/Entrance/entranceCommands.o

# target to preprocess a source file
src/interpreter/Entrance/entranceCommands.i:
	$(MAKE) -f CMakeFiles/muddyreality.dir/build.make CMakeFiles/muddyreality.dir/src/interpreter/Entrance/entranceCommands.i
.PHONY : src/interpreter/Entrance/entranceCommands.i

# target to generate assembly for a file
src/interpreter/Entrance/entranceCommands.s:
	$(MAKE) -f CMakeFiles/muddyreality.dir/build.make CMakeFiles/muddyreality.dir/src/interpreter/Entrance/entranceCommands.s
.PHONY : src/interpreter/Entrance/entranceCommands.s

# target to build an object file
src/interpreter/State/stateInterpreter.o:
	$(MAKE) -f CMakeFiles/muddyreality.dir/build.make CMakeFiles/muddyreality.dir/src/interpreter/State/stateInterpreter.o
.PHONY : src/interpreter/State/stateInterpreter.o

# target to preprocess a source file
src/interpreter/State/stateInterpreter.i:
	$(MAKE) -f CMakeFiles/muddyreality.dir/build.make CMakeFiles/muddyreality.dir/src/interpreter/State/stateInterpreter.i
.PHONY : src/interpreter/State/stateInterpreter.i

# target to generate assembly for a file
src/interpreter/State/stateInterpreter.s:
	$(MAKE) -f CMakeFiles/muddyreality.dir/build.make CMakeFiles/muddyreality.dir/src/interpreter/State/stateInterpreter.s
.PHONY : src/interpreter/State/stateInterpreter.s

# target to build an object file
src/main.o:
	$(MAKE) -f CMakeFiles/muddyreality.dir/build.make CMakeFiles/muddyreality.dir/src/main.o
.PHONY : src/main.o

# target to preprocess a source file
src/main.i:
	$(MAKE) -f CMakeFiles/muddyreality.dir/build.make CMakeFiles/muddyreality.dir/src/main.i
.PHONY : src/main.i

# target to generate assembly for a file
src/main.s:
	$(MAKE) -f CMakeFiles/muddyreality.dir/build.make CMakeFiles/muddyreality.dir/src/main.s
.PHONY : src/main.s

# target to build an object file
src/models/Account/account.o:
	$(MAKE) -f CMakeFiles/muddyreality.dir/build.make CMakeFiles/muddyreality.dir/src/models/Account/account.o
.PHONY : src/models/Account/account.o

# target to preprocess a source file
src/models/Account/account.i:
	$(MAKE) -f CMakeFiles/muddyreality.dir/build.make CMakeFiles/muddyreality.dir/src/models/Account/account.i
.PHONY : src/models/Account/account.i

# target to generate assembly for a file
src/models/Account/account.s:
	$(MAKE) -f CMakeFiles/muddyreality.dir/build.make CMakeFiles/muddyreality.dir/src/models/Account/account.s
.PHONY : src/models/Account/account.s

# target to build an object file
src/models/Character/character.o:
	$(MAKE) -f CMakeFiles/muddyreality.dir/build.make CMakeFiles/muddyreality.dir/src/models/Character/character.o
.PHONY : src/models/Character/character.o

# target to preprocess a source file
src/models/Character/character.i:
	$(MAKE) -f CMakeFiles/muddyreality.dir/build.make CMakeFiles/muddyreality.dir/src/models/Character/character.i
.PHONY : src/models/Character/character.i

# target to generate assembly for a file
src/models/Character/character.s:
	$(MAKE) -f CMakeFiles/muddyreality.dir/build.make CMakeFiles/muddyreality.dir/src/models/Character/character.s
.PHONY : src/models/Character/character.s

# target to build an object file
src/models/ModelFactory/modelFactory.o:
	$(MAKE) -f CMakeFiles/muddyreality.dir/build.make CMakeFiles/muddyreality.dir/src/models/ModelFactory/modelFactory.o
.PHONY : src/models/ModelFactory/modelFactory.o

# target to preprocess a source file
src/models/ModelFactory/modelFactory.i:
	$(MAKE) -f CMakeFiles/muddyreality.dir/build.make CMakeFiles/muddyreality.dir/src/models/ModelFactory/modelFactory.i
.PHONY : src/models/ModelFactory/modelFactory.i

# target to generate assembly for a file
src/models/ModelFactory/modelFactory.s:
	$(MAKE) -f CMakeFiles/muddyreality.dir/build.make CMakeFiles/muddyreality.dir/src/models/ModelFactory/modelFactory.s
.PHONY : src/models/ModelFactory/modelFactory.s

# target to build an object file
src/models/model.o:
	$(MAKE) -f CMakeFiles/muddyreality.dir/build.make CMakeFiles/muddyreality.dir/src/models/model.o
.PHONY : src/models/model.o

# target to preprocess a source file
src/models/model.i:
	$(MAKE) -f CMakeFiles/muddyreality.dir/build.make CMakeFiles/muddyreality.dir/src/models/model.i
.PHONY : src/models/model.i

# target to generate assembly for a file
src/models/model.s:
	$(MAKE) -f CMakeFiles/muddyreality.dir/build.make CMakeFiles/muddyreality.dir/src/models/model.s
.PHONY : src/models/model.s

# target to build an object file
src/server/socket.o:
	$(MAKE) -f CMakeFiles/muddyreality.dir/build.make CMakeFiles/muddyreality.dir/src/server/socket.o
.PHONY : src/server/socket.o

# target to preprocess a source file
src/server/socket.i:
	$(MAKE) -f CMakeFiles/muddyreality.dir/build.make CMakeFiles/muddyreality.dir/src/server/socket.i
.PHONY : src/server/socket.i

# target to generate assembly for a file
src/server/socket.s:
	$(MAKE) -f CMakeFiles/muddyreality.dir/build.make CMakeFiles/muddyreality.dir/src/server/socket.s
.PHONY : src/server/socket.s

# target to build an object file
src/utilities/logger.o:
	$(MAKE) -f CMakeFiles/muddyreality.dir/build.make CMakeFiles/muddyreality.dir/src/utilities/logger.o
.PHONY : src/utilities/logger.o

# target to preprocess a source file
src/utilities/logger.i:
	$(MAKE) -f CMakeFiles/muddyreality.dir/build.make CMakeFiles/muddyreality.dir/src/utilities/logger.i
.PHONY : src/utilities/logger.i

# target to generate assembly for a file
src/utilities/logger.s:
	$(MAKE) -f CMakeFiles/muddyreality.dir/build.make CMakeFiles/muddyreality.dir/src/utilities/logger.s
.PHONY : src/utilities/logger.s

# target to build an object file
src/utilities/utilities.o:
	$(MAKE) -f CMakeFiles/muddyreality.dir/build.make CMakeFiles/muddyreality.dir/src/utilities/utilities.o
.PHONY : src/utilities/utilities.o

# target to preprocess a source file
src/utilities/utilities.i:
	$(MAKE) -f CMakeFiles/muddyreality.dir/build.make CMakeFiles/muddyreality.dir/src/utilities/utilities.i
.PHONY : src/utilities/utilities.i

# target to generate assembly for a file
src/utilities/utilities.s:
	$(MAKE) -f CMakeFiles/muddyreality.dir/build.make CMakeFiles/muddyreality.dir/src/utilities/utilities.s
.PHONY : src/utilities/utilities.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... muddyreality"
	@echo "... rebuild_cache"
	@echo "... src/Player/player.o"
	@echo "... src/Player/player.i"
	@echo "... src/Player/player.s"
	@echo "... src/interpreter/Account/accountCommands.o"
	@echo "... src/interpreter/Account/accountCommands.i"
	@echo "... src/interpreter/Account/accountCommands.s"
	@echo "... src/interpreter/Command/commandInterpreter.o"
	@echo "... src/interpreter/Command/commandInterpreter.i"
	@echo "... src/interpreter/Command/commandInterpreter.s"
	@echo "... src/interpreter/Creation/creationStates.o"
	@echo "... src/interpreter/Creation/creationStates.i"
	@echo "... src/interpreter/Creation/creationStates.s"
	@echo "... src/interpreter/Entrance/entranceCommands.o"
	@echo "... src/interpreter/Entrance/entranceCommands.i"
	@echo "... src/interpreter/Entrance/entranceCommands.s"
	@echo "... src/interpreter/State/stateInterpreter.o"
	@echo "... src/interpreter/State/stateInterpreter.i"
	@echo "... src/interpreter/State/stateInterpreter.s"
	@echo "... src/main.o"
	@echo "... src/main.i"
	@echo "... src/main.s"
	@echo "... src/models/Account/account.o"
	@echo "... src/models/Account/account.i"
	@echo "... src/models/Account/account.s"
	@echo "... src/models/Character/character.o"
	@echo "... src/models/Character/character.i"
	@echo "... src/models/Character/character.s"
	@echo "... src/models/ModelFactory/modelFactory.o"
	@echo "... src/models/ModelFactory/modelFactory.i"
	@echo "... src/models/ModelFactory/modelFactory.s"
	@echo "... src/models/model.o"
	@echo "... src/models/model.i"
	@echo "... src/models/model.s"
	@echo "... src/server/socket.o"
	@echo "... src/server/socket.i"
	@echo "... src/server/socket.s"
	@echo "... src/utilities/logger.o"
	@echo "... src/utilities/logger.i"
	@echo "... src/utilities/logger.s"
	@echo "... src/utilities/utilities.o"
	@echo "... src/utilities/utilities.i"
	@echo "... src/utilities/utilities.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system
