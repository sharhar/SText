cmake_minimum_required(VERSION 2.8.11)

set(EXT_EXTRACT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/ext")

project(SText)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

option(STEXT_BUILD_TEST "Build the SText-Test project" ON)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src/SText")

if(STEXT_BUILD_TEST)
set(GLFW_SOURCE_NAME "glfw-3.2")
set(GLFW_URL "http://downloads.sourceforge.net/project/glfw/glfw/3.2/${GLFW_SOURCE_NAME}.tar.gz?r=https%3A%2F%2Fsourceforge.net%2Fprojects%2Fglfw%2Ffiles%2Fglfw%2F3.2%2F&ts=1470492725&use_mirror=heanet")
set(GLFW_DOWNLOAD_PATH "${CMAKE_SOURCE_DIR}/${GLFW_SOURCE_NAME}.tar.gz")
set(GLFW_SOURCE_DIR "${EXT_EXTRACT_DIR}/${GLFW_SOURCE_NAME}")

if(NOT MSVC)
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
message(STATUS "Found CXX11 support in ${CMAKE_CXX_COMPILER}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
message(STATUS "Found CXX0X support in ${CMAKE_CXX_COMPILER}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
message(FATAL_ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

endif()

if(NOT EXISTS ${EXT_EXTRACT_DIR})
execute_process(
COMMAND ${CMAKE_COMMAND} -E make_directory "ext"
WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
endif()

if(NOT EXISTS ${GLFW_SOURCE_DIR})
message(STATUS "GLFW source not found. Fixing..")
#First we check if the .tar.gz is downloaded. There may be chance it is already downloaded and not extracted
if (NOT EXISTS "${GLFW_DOWNLOAD_PATH}")
message(STATUS "Downloading GLFW source...")
file(DOWNLOAD "${GLFW_URL}" "${GLFW_DOWNLOAD_PATH}")
else()
message(STATUS "GLFW source found in tar.gz")
endif()

message(STATUS "Extracting GLFW source...")

#Next we extract the .tar.gz. This works on Windows as well
execute_process(
COMMAND ${CMAKE_COMMAND} -E tar xvf ${GLFW_DOWNLOAD_PATH}
WORKING_DIRECTORY "${EXT_EXTRACT_DIR}"
)

#If the extraction fails, go to here.
if(NOT EXISTS "${GLFW_SOURCE_DIR}")
message(FATAL_ERROR "Failed to extract GLFW source! Please retry or file a bug report.")
else()
message(STATUS "GLFW extracted.")
endif()

#Remove the extracted tar. We dont need the original anymore
file(REMOVE ${GLFW_DOWNLOAD_PATH})
message(STATUS "Deleted temporary tar")
message(STATUS "Done adding ${GLFW_SOURCE_NAME}")
else()
message(STATUS "GLFW found.")
endif()

include_directories(
"${GLFW_SOURCE_DIR}/include"
"${CMAKE_CURRENT_SOURCE_DIR}/include"
)

option(GLFW_BUILD_EXAMPLES "Build the GLFW example programs" OFF)
option(GLFW_BUILD_TESTS "Build the GLFW test programs" OFF)
option(GLFW_BUILD_DOCS "Build the GLFW documentation" OFF)

add_subdirectory("${GLFW_SOURCE_DIR}")

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src/SText-Test")
endif()
