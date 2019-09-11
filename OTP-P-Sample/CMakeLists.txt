cmake_minimum_required (VERSION 3.1)
project (P)
set(projectName OTPServer)
find_package (Threads)
include_directories(~/Research/P/Bld/Drops/Prt/include)
add_executable(otp_server
	OTPServer.c
	OTPServer.h
	MainFunction.c)

target_link_libraries(otp_server ${CMAKE_SOURCE_DIR}/../../../Bld/Drops/Prt/lib/libPrt_static.a ${CMAKE_SOURCE_DIR}/../../../Ext/libhandler/out/gcc-amd64-linux-gnu/debug/libhandler.a ${CMAKE_THREAD_LIBS_INIT})

