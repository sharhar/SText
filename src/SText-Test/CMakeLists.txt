cmake_minimum_required(VERSION 2.8.11)

file(GLOB_RECURSE STEXT_TEST_SRC *.c)

if(APPLE)
	add_executable(
		SText-Test 
		MACOSX_BUNDLE 
		${STEXT_TEST_SRC}
		)
else()
	add_executable(SText-Test ${STEXT_TEST_SRC})
endif()

target_link_libraries (SText-Test LINK_PUBLIC SText)
target_link_libraries (SText-Test glfw ${GLFW_LIBRARIES})