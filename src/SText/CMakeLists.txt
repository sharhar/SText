cmake_minimum_required(VERSION 2.8.11)

file(GLOB_RECURSE STEXT_HEADERS "${CMAKE_SOURCE_DIR}/include/*.h")
file(GLOB_RECURSE STEXT_SRC *.m)

add_library(SText ${STEXT_HEADERS} ${STEXT_SRC})

target_include_directories (SText PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})