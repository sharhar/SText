cmake_minimum_required(VERSION 2.8.11)

file(GLOB_RECURSE STEXT_HEADERS "${CMAKE_SOURCE_DIR}/include/*.h")
#file(GLOB_RECURSE STEXT_SRC *.m)

#add_library(SText ${STEXT_HEADERS} ${STEXT_SRC})

if(APPLE)
	add_library(SText ${STEXT_HEADERS} 
			SText_Cocoa.m
			SText_Glyph.c
			SText.c)
	set(STEXT_LIBRARIES SText PARENT_SCOPE)
elseif(MSVC)
#	add_library(SWin ${SWIN_HEADERS}
#			Win32/SWin_Win32_GL.c
#			Win32/SWin_Win32_Thread.c
#			Win32/SWin_Win32_VK.c
#			Win32/SWin_Win32_Window.c
#			Win32/SWin_Win32_Utils.c
#			SWin_Utils.c)
#	set(SWIN_LIBRARIES SWin PARENT_SCOPE)
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
