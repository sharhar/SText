cmake_minimum_required(VERSION 2.8.11)

file(GLOB_RECURSE STEXT_HEADERS "${CMAKE_SOURCE_DIR}/include/*.h")

if(APPLE)
	add_library(SText ${STEXT_HEADERS} 
			SText_Cocoa.m
			SText_Utils.c
			SText_GL.c)
	set(STEXT_LIBRARIES SText PARENT_SCOPE)
elseif(MSVC)
	add_library(SText ${STEXT_HEADERS} 
			SText_Win32.c
			SText_Utils.c
			SText_GL.c)
	set(STEXT_LIBRARIES SText PARENT_SCOPE)
else()
#	add_library(SWin ${SWIN_HEADERS}
#			GLX/SWin_GLX.c
#			X11/SWin_X11_VK.c
#			X11/SWin_X11_Window.c
#			X11/SWin_X11_Utils.c
#			POSIX/SWin_POSIX_Thread.c
#			SWin_Utils.c)
#
#	set(SWIN_LIBRARIES SWin -lX11 -ldl -lpthread PARENT_SCOPE)
endif()

target_include_directories (SText PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../include)
