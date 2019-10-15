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


# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_SOURCE_DIR = /home/shiv/Research/temp-del/ProgrammingEnclaves

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/shiv/Research/temp-del/ProgrammingEnclaves

# Include any dependencies generated for this target.
include Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/depend.make

# Include the progress variables for this target.
include Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/progress.make

# Include the compile flags for this target's objects.
include Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/flags.make

Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/enclave_t.c: Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/enclave.edl
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/shiv/Research/temp-del/ProgrammingEnclaves/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating enclave_t.c"
	cd /home/shiv/Research/temp-del/ProgrammingEnclaves/Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave && /home/shiv/Research/Intel-SGX-Installation/linux-sgx/linux/installer/bin/sgxsdk/bin/x64/sgx_edger8r --trusted enclave.edl --search-path /home/shiv/Research/Intel-SGX-Installation/linux-sgx/linux/installer/bin/sgxsdk/include --search-path /home/shiv/Research/temp-del/ProgrammingEnclaves/Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave

Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/enclave.cpp.o: Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/flags.make
Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/enclave.cpp.o: Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/enclave.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/shiv/Research/temp-del/ProgrammingEnclaves/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/enclave.cpp.o"
	cd /home/shiv/Research/temp-del/ProgrammingEnclaves/Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/enclave.dir/enclave.cpp.o -c /home/shiv/Research/temp-del/ProgrammingEnclaves/Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/enclave.cpp

Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/enclave.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/enclave.dir/enclave.cpp.i"
	cd /home/shiv/Research/temp-del/ProgrammingEnclaves/Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/shiv/Research/temp-del/ProgrammingEnclaves/Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/enclave.cpp > CMakeFiles/enclave.dir/enclave.cpp.i

Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/enclave.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/enclave.dir/enclave.cpp.s"
	cd /home/shiv/Research/temp-del/ProgrammingEnclaves/Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/shiv/Research/temp-del/ProgrammingEnclaves/Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/enclave.cpp -o CMakeFiles/enclave.dir/enclave.cpp.s

Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/enclave.cpp.o.requires:

.PHONY : Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/enclave.cpp.o.requires

Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/enclave.cpp.o.provides: Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/enclave.cpp.o.requires
	$(MAKE) -f Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/build.make Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/enclave.cpp.o.provides.build
.PHONY : Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/enclave.cpp.o.provides

Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/enclave.cpp.o.provides.build: Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/enclave.cpp.o


Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/pong_enclave_internal_attestation.cpp.o: Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/flags.make
Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/pong_enclave_internal_attestation.cpp.o: Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/pong_enclave_internal_attestation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/shiv/Research/temp-del/ProgrammingEnclaves/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/pong_enclave_internal_attestation.cpp.o"
	cd /home/shiv/Research/temp-del/ProgrammingEnclaves/Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/enclave.dir/pong_enclave_internal_attestation.cpp.o -c /home/shiv/Research/temp-del/ProgrammingEnclaves/Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/pong_enclave_internal_attestation.cpp

Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/pong_enclave_internal_attestation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/enclave.dir/pong_enclave_internal_attestation.cpp.i"
	cd /home/shiv/Research/temp-del/ProgrammingEnclaves/Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/shiv/Research/temp-del/ProgrammingEnclaves/Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/pong_enclave_internal_attestation.cpp > CMakeFiles/enclave.dir/pong_enclave_internal_attestation.cpp.i

Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/pong_enclave_internal_attestation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/enclave.dir/pong_enclave_internal_attestation.cpp.s"
	cd /home/shiv/Research/temp-del/ProgrammingEnclaves/Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/shiv/Research/temp-del/ProgrammingEnclaves/Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/pong_enclave_internal_attestation.cpp -o CMakeFiles/enclave.dir/pong_enclave_internal_attestation.cpp.s

Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/pong_enclave_internal_attestation.cpp.o.requires:

.PHONY : Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/pong_enclave_internal_attestation.cpp.o.requires

Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/pong_enclave_internal_attestation.cpp.o.provides: Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/pong_enclave_internal_attestation.cpp.o.requires
	$(MAKE) -f Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/build.make Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/pong_enclave_internal_attestation.cpp.o.provides.build
.PHONY : Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/pong_enclave_internal_attestation.cpp.o.provides

Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/pong_enclave_internal_attestation.cpp.o.provides.build: Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/pong_enclave_internal_attestation.cpp.o


Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/enclave_t.c.o: Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/flags.make
Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/enclave_t.c.o: Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/enclave_t.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/shiv/Research/temp-del/ProgrammingEnclaves/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/enclave_t.c.o"
	cd /home/shiv/Research/temp-del/ProgrammingEnclaves/Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/enclave.dir/enclave_t.c.o   -c /home/shiv/Research/temp-del/ProgrammingEnclaves/Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/enclave_t.c

Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/enclave_t.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/enclave.dir/enclave_t.c.i"
	cd /home/shiv/Research/temp-del/ProgrammingEnclaves/Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/shiv/Research/temp-del/ProgrammingEnclaves/Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/enclave_t.c > CMakeFiles/enclave.dir/enclave_t.c.i

Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/enclave_t.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/enclave.dir/enclave_t.c.s"
	cd /home/shiv/Research/temp-del/ProgrammingEnclaves/Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/shiv/Research/temp-del/ProgrammingEnclaves/Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/enclave_t.c -o CMakeFiles/enclave.dir/enclave_t.c.s

Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/enclave_t.c.o.requires:

.PHONY : Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/enclave_t.c.o.requires

Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/enclave_t.c.o.provides: Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/enclave_t.c.o.requires
	$(MAKE) -f Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/build.make Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/enclave_t.c.o.provides.build
.PHONY : Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/enclave_t.c.o.provides

Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/enclave_t.c.o.provides.build: Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/enclave_t.c.o


Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/__/__/PGenerated/PingPongEnclave.c.o: Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/flags.make
Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/__/__/PGenerated/PingPongEnclave.c.o: Samples/PingEnclavePongOutsideRemoteAttestation/PGenerated/PingPongEnclave.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/shiv/Research/temp-del/ProgrammingEnclaves/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/__/__/PGenerated/PingPongEnclave.c.o"
	cd /home/shiv/Research/temp-del/ProgrammingEnclaves/Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/enclave.dir/__/__/PGenerated/PingPongEnclave.c.o   -c /home/shiv/Research/temp-del/ProgrammingEnclaves/Samples/PingEnclavePongOutsideRemoteAttestation/PGenerated/PingPongEnclave.c

Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/__/__/PGenerated/PingPongEnclave.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/enclave.dir/__/__/PGenerated/PingPongEnclave.c.i"
	cd /home/shiv/Research/temp-del/ProgrammingEnclaves/Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/shiv/Research/temp-del/ProgrammingEnclaves/Samples/PingEnclavePongOutsideRemoteAttestation/PGenerated/PingPongEnclave.c > CMakeFiles/enclave.dir/__/__/PGenerated/PingPongEnclave.c.i

Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/__/__/PGenerated/PingPongEnclave.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/enclave.dir/__/__/PGenerated/PingPongEnclave.c.s"
	cd /home/shiv/Research/temp-del/ProgrammingEnclaves/Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/shiv/Research/temp-del/ProgrammingEnclaves/Samples/PingEnclavePongOutsideRemoteAttestation/PGenerated/PingPongEnclave.c -o CMakeFiles/enclave.dir/__/__/PGenerated/PingPongEnclave.c.s

Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/__/__/PGenerated/PingPongEnclave.c.o.requires:

.PHONY : Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/__/__/PGenerated/PingPongEnclave.c.o.requires

Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/__/__/PGenerated/PingPongEnclave.c.o.provides: Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/__/__/PGenerated/PingPongEnclave.c.o.requires
	$(MAKE) -f Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/build.make Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/__/__/PGenerated/PingPongEnclave.c.o.provides.build
.PHONY : Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/__/__/PGenerated/PingPongEnclave.c.o.provides

Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/__/__/PGenerated/PingPongEnclave.c.o.provides.build: Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/__/__/PGenerated/PingPongEnclave.c.o


# Object files for target enclave
enclave_OBJECTS = \
"CMakeFiles/enclave.dir/enclave.cpp.o" \
"CMakeFiles/enclave.dir/pong_enclave_internal_attestation.cpp.o" \
"CMakeFiles/enclave.dir/enclave_t.c.o" \
"CMakeFiles/enclave.dir/__/__/PGenerated/PingPongEnclave.c.o"

# External object files for target enclave
enclave_EXTERNAL_OBJECTS =

Samples/PingEnclavePongOutsideRemoteAttestation/enclave.so: Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/enclave.cpp.o
Samples/PingEnclavePongOutsideRemoteAttestation/enclave.so: Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/pong_enclave_internal_attestation.cpp.o
Samples/PingEnclavePongOutsideRemoteAttestation/enclave.so: Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/enclave_t.c.o
Samples/PingEnclavePongOutsideRemoteAttestation/enclave.so: Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/__/__/PGenerated/PingPongEnclave.c.o
Samples/PingEnclavePongOutsideRemoteAttestation/enclave.so: Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/build.make
Samples/PingEnclavePongOutsideRemoteAttestation/enclave.so: Submodule/P/Bld/Drops/Prt/lib/libPrt_trusted_static.a
Samples/PingEnclavePongOutsideRemoteAttestation/enclave.so: Submodule/P/Bld/Drops/Prt/lib/libPrt_trusted_static.a
Samples/PingEnclavePongOutsideRemoteAttestation/enclave.so: Submodule/P/Ext/libhandler/out/gcc-amd64-linux-gnu/debug/libhandler.a
Samples/PingEnclavePongOutsideRemoteAttestation/enclave.so: Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/shiv/Research/temp-del/ProgrammingEnclaves/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX shared library ../../enclave.so"
	cd /home/shiv/Research/temp-del/ProgrammingEnclaves/Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/enclave.dir/link.txt --verbose=$(VERBOSE)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Signing the enclave => /home/shiv/Research/temp-del/ProgrammingEnclaves/Samples/PingEnclavePongOutsideRemoteAttestation/enclave.signed.so"
	cd /home/shiv/Research/temp-del/ProgrammingEnclaves/Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave && /home/shiv/Research/Intel-SGX-Installation/linux-sgx/linux/installer/bin/sgxsdk/bin/x64/sgx_sign sign -key enclave_private.pem -config enclave.config.xml -enclave /home/shiv/Research/temp-del/ProgrammingEnclaves/Samples/PingEnclavePongOutsideRemoteAttestation/enclave.so -out /home/shiv/Research/temp-del/ProgrammingEnclaves/Samples/PingEnclavePongOutsideRemoteAttestation/enclave.signed.so

# Rule to build all files generated by this target.
Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/build: Samples/PingEnclavePongOutsideRemoteAttestation/enclave.so

.PHONY : Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/build

Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/requires: Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/enclave.cpp.o.requires
Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/requires: Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/pong_enclave_internal_attestation.cpp.o.requires
Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/requires: Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/enclave_t.c.o.requires
Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/requires: Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/__/__/PGenerated/PingPongEnclave.c.o.requires

.PHONY : Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/requires

Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/clean:
	cd /home/shiv/Research/temp-del/ProgrammingEnclaves/Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave && $(CMAKE_COMMAND) -P CMakeFiles/enclave.dir/cmake_clean.cmake
.PHONY : Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/clean

Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/depend: Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/enclave_t.c
	cd /home/shiv/Research/temp-del/ProgrammingEnclaves && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/shiv/Research/temp-del/ProgrammingEnclaves /home/shiv/Research/temp-del/ProgrammingEnclaves/Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave /home/shiv/Research/temp-del/ProgrammingEnclaves /home/shiv/Research/temp-del/ProgrammingEnclaves/Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave /home/shiv/Research/temp-del/ProgrammingEnclaves/Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Samples/PingEnclavePongOutsideRemoteAttestation/Src/enclave/CMakeFiles/enclave.dir/depend

