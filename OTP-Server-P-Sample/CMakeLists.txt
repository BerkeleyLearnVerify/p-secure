cmake_minimum_required (VERSION 3.1)
project (P)
set(projectName PingPong)
find_package (Threads)
include_directories(~/Research/P/Bld/Drops/Prt/include)
add_executable(ping_pong
	PingPong.c
	PingPong.h
	MainFunction.c
	~/Research/P/Bld/Drops/Prt/include/ext_compat.h
	~/Research/P/Bld/Drops/Prt/include/libhandler.h
	~/Research/P/Bld/Drops/Prt/include/libhandler-internal.h
	~/Research/P/Bld/Drops/Prt/include/Prt.h
	~/Research/P/Bld/Drops/Prt/include/PrtConfig.h
	~/Research/P/Bld/Drops/Prt/include/PrtExecution.h
	~/Research/P/Bld/Drops/Prt/include/PrtLinuxUserConfig.h
	~/Research/P/Bld/Drops/Prt/include/PrtProgram.h
	~/Research/P/Bld/Drops/Prt/include/PrtTypes.h
	~/Research/P/Bld/Drops/Prt/include/PrtValues.h
	~/Research/P/Bld/Drops/Prt/include/sal.h)

target_link_libraries(ping_pong ${CMAKE_SOURCE_DIR}/../../../Bld/Drops/Prt/lib/libPrt_static.a ${CMAKE_SOURCE_DIR}/../../../Ext/libhandler/out/gcc-amd64-linux-gnu/debug/libhandler.a ${CMAKE_THREAD_LIBS_INIT})

