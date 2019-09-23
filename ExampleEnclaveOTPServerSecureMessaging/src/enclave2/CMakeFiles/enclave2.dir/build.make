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
CMAKE_SOURCE_DIR = /home/shiv/Research/temp-del/ProgrammingEnclaves/ExampleEnclaveOTPServerSecureMessaging

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/shiv/Research/temp-del/ProgrammingEnclaves/ExampleEnclaveOTPServerSecureMessaging

# Include any dependencies generated for this target.
include src/enclave2/CMakeFiles/enclave2.dir/depend.make

# Include the progress variables for this target.
include src/enclave2/CMakeFiles/enclave2.dir/progress.make

# Include the compile flags for this target's objects.
include src/enclave2/CMakeFiles/enclave2.dir/flags.make

src/enclave2/enclave2_t.c: src/enclave2/enclave2.edl
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/shiv/Research/temp-del/ProgrammingEnclaves/ExampleEnclaveOTPServerSecureMessaging/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating enclave2_t.c"
	cd /home/shiv/Research/temp-del/ProgrammingEnclaves/ExampleEnclaveOTPServerSecureMessaging/src/enclave2 && /home/shiv/Research/Intel-SGX-Installation/linux-sgx/linux/installer/bin/sgxsdk/bin/x64/sgx_edger8r --trusted enclave2.edl --search-path /home/shiv/Research/Intel-SGX-Installation/linux-sgx/linux/installer/bin/sgxsdk/include --search-path /home/shiv/Research/temp-del/ProgrammingEnclaves/ExampleEnclaveOTPServerSecureMessaging/src/enclave2

src/enclave2/CMakeFiles/enclave2.dir/enclave2.cpp.o: src/enclave2/CMakeFiles/enclave2.dir/flags.make
src/enclave2/CMakeFiles/enclave2.dir/enclave2.cpp.o: src/enclave2/enclave2.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/shiv/Research/temp-del/ProgrammingEnclaves/ExampleEnclaveOTPServerSecureMessaging/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/enclave2/CMakeFiles/enclave2.dir/enclave2.cpp.o"
	cd /home/shiv/Research/temp-del/ProgrammingEnclaves/ExampleEnclaveOTPServerSecureMessaging/src/enclave2 && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/enclave2.dir/enclave2.cpp.o -c /home/shiv/Research/temp-del/ProgrammingEnclaves/ExampleEnclaveOTPServerSecureMessaging/src/enclave2/enclave2.cpp

src/enclave2/CMakeFiles/enclave2.dir/enclave2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/enclave2.dir/enclave2.cpp.i"
	cd /home/shiv/Research/temp-del/ProgrammingEnclaves/ExampleEnclaveOTPServerSecureMessaging/src/enclave2 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/shiv/Research/temp-del/ProgrammingEnclaves/ExampleEnclaveOTPServerSecureMessaging/src/enclave2/enclave2.cpp > CMakeFiles/enclave2.dir/enclave2.cpp.i

src/enclave2/CMakeFiles/enclave2.dir/enclave2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/enclave2.dir/enclave2.cpp.s"
	cd /home/shiv/Research/temp-del/ProgrammingEnclaves/ExampleEnclaveOTPServerSecureMessaging/src/enclave2 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/shiv/Research/temp-del/ProgrammingEnclaves/ExampleEnclaveOTPServerSecureMessaging/src/enclave2/enclave2.cpp -o CMakeFiles/enclave2.dir/enclave2.cpp.s

src/enclave2/CMakeFiles/enclave2.dir/enclave2.cpp.o.requires:

.PHONY : src/enclave2/CMakeFiles/enclave2.dir/enclave2.cpp.o.requires

src/enclave2/CMakeFiles/enclave2.dir/enclave2.cpp.o.provides: src/enclave2/CMakeFiles/enclave2.dir/enclave2.cpp.o.requires
	$(MAKE) -f src/enclave2/CMakeFiles/enclave2.dir/build.make src/enclave2/CMakeFiles/enclave2.dir/enclave2.cpp.o.provides.build
.PHONY : src/enclave2/CMakeFiles/enclave2.dir/enclave2.cpp.o.provides

src/enclave2/CMakeFiles/enclave2.dir/enclave2.cpp.o.provides.build: src/enclave2/CMakeFiles/enclave2.dir/enclave2.cpp.o


src/enclave2/CMakeFiles/enclave2.dir/enclave2_t.c.o: src/enclave2/CMakeFiles/enclave2.dir/flags.make
src/enclave2/CMakeFiles/enclave2.dir/enclave2_t.c.o: src/enclave2/enclave2_t.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/shiv/Research/temp-del/ProgrammingEnclaves/ExampleEnclaveOTPServerSecureMessaging/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object src/enclave2/CMakeFiles/enclave2.dir/enclave2_t.c.o"
	cd /home/shiv/Research/temp-del/ProgrammingEnclaves/ExampleEnclaveOTPServerSecureMessaging/src/enclave2 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/enclave2.dir/enclave2_t.c.o   -c /home/shiv/Research/temp-del/ProgrammingEnclaves/ExampleEnclaveOTPServerSecureMessaging/src/enclave2/enclave2_t.c

src/enclave2/CMakeFiles/enclave2.dir/enclave2_t.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/enclave2.dir/enclave2_t.c.i"
	cd /home/shiv/Research/temp-del/ProgrammingEnclaves/ExampleEnclaveOTPServerSecureMessaging/src/enclave2 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/shiv/Research/temp-del/ProgrammingEnclaves/ExampleEnclaveOTPServerSecureMessaging/src/enclave2/enclave2_t.c > CMakeFiles/enclave2.dir/enclave2_t.c.i

src/enclave2/CMakeFiles/enclave2.dir/enclave2_t.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/enclave2.dir/enclave2_t.c.s"
	cd /home/shiv/Research/temp-del/ProgrammingEnclaves/ExampleEnclaveOTPServerSecureMessaging/src/enclave2 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/shiv/Research/temp-del/ProgrammingEnclaves/ExampleEnclaveOTPServerSecureMessaging/src/enclave2/enclave2_t.c -o CMakeFiles/enclave2.dir/enclave2_t.c.s

src/enclave2/CMakeFiles/enclave2.dir/enclave2_t.c.o.requires:

.PHONY : src/enclave2/CMakeFiles/enclave2.dir/enclave2_t.c.o.requires

src/enclave2/CMakeFiles/enclave2.dir/enclave2_t.c.o.provides: src/enclave2/CMakeFiles/enclave2.dir/enclave2_t.c.o.requires
	$(MAKE) -f src/enclave2/CMakeFiles/enclave2.dir/build.make src/enclave2/CMakeFiles/enclave2.dir/enclave2_t.c.o.provides.build
.PHONY : src/enclave2/CMakeFiles/enclave2.dir/enclave2_t.c.o.provides

src/enclave2/CMakeFiles/enclave2.dir/enclave2_t.c.o.provides.build: src/enclave2/CMakeFiles/enclave2.dir/enclave2_t.c.o


# Object files for target enclave2
enclave2_OBJECTS = \
"CMakeFiles/enclave2.dir/enclave2.cpp.o" \
"CMakeFiles/enclave2.dir/enclave2_t.c.o"

# External object files for target enclave2
enclave2_EXTERNAL_OBJECTS =

enclave2.so: src/enclave2/CMakeFiles/enclave2.dir/enclave2.cpp.o
enclave2.so: src/enclave2/CMakeFiles/enclave2.dir/enclave2_t.c.o
enclave2.so: src/enclave2/CMakeFiles/enclave2.dir/build.make
enclave2.so: src/enclave2/CMakeFiles/enclave2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/shiv/Research/temp-del/ProgrammingEnclaves/ExampleEnclaveOTPServerSecureMessaging/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX shared library ../../enclave2.so"
	cd /home/shiv/Research/temp-del/ProgrammingEnclaves/ExampleEnclaveOTPServerSecureMessaging/src/enclave2 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/enclave2.dir/link.txt --verbose=$(VERBOSE)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Signing the enclave => /home/shiv/Research/temp-del/ProgrammingEnclaves/ExampleEnclaveOTPServerSecureMessaging/enclave2.signed.so"
	cd /home/shiv/Research/temp-del/ProgrammingEnclaves/ExampleEnclaveOTPServerSecureMessaging/src/enclave2 && /home/shiv/Research/Intel-SGX-Installation/linux-sgx/linux/installer/bin/sgxsdk/bin/x64/sgx_sign sign -key enclave2_private.pem -config enclave2.config.xml -enclave /home/shiv/Research/temp-del/ProgrammingEnclaves/ExampleEnclaveOTPServerSecureMessaging/enclave2.so -out /home/shiv/Research/temp-del/ProgrammingEnclaves/ExampleEnclaveOTPServerSecureMessaging/enclave2.signed.so

# Rule to build all files generated by this target.
src/enclave2/CMakeFiles/enclave2.dir/build: enclave2.so

.PHONY : src/enclave2/CMakeFiles/enclave2.dir/build

src/enclave2/CMakeFiles/enclave2.dir/requires: src/enclave2/CMakeFiles/enclave2.dir/enclave2.cpp.o.requires
src/enclave2/CMakeFiles/enclave2.dir/requires: src/enclave2/CMakeFiles/enclave2.dir/enclave2_t.c.o.requires

.PHONY : src/enclave2/CMakeFiles/enclave2.dir/requires

src/enclave2/CMakeFiles/enclave2.dir/clean:
	cd /home/shiv/Research/temp-del/ProgrammingEnclaves/ExampleEnclaveOTPServerSecureMessaging/src/enclave2 && $(CMAKE_COMMAND) -P CMakeFiles/enclave2.dir/cmake_clean.cmake
.PHONY : src/enclave2/CMakeFiles/enclave2.dir/clean

src/enclave2/CMakeFiles/enclave2.dir/depend: src/enclave2/enclave2_t.c
	cd /home/shiv/Research/temp-del/ProgrammingEnclaves/ExampleEnclaveOTPServerSecureMessaging && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/shiv/Research/temp-del/ProgrammingEnclaves/ExampleEnclaveOTPServerSecureMessaging /home/shiv/Research/temp-del/ProgrammingEnclaves/ExampleEnclaveOTPServerSecureMessaging/src/enclave2 /home/shiv/Research/temp-del/ProgrammingEnclaves/ExampleEnclaveOTPServerSecureMessaging /home/shiv/Research/temp-del/ProgrammingEnclaves/ExampleEnclaveOTPServerSecureMessaging/src/enclave2 /home/shiv/Research/temp-del/ProgrammingEnclaves/ExampleEnclaveOTPServerSecureMessaging/src/enclave2/CMakeFiles/enclave2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/enclave2/CMakeFiles/enclave2.dir/depend

