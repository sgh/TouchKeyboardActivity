cmake_minimum_required(VERSION 2.6)

project( TouchKeyboardActivity )

if (NOT CMAKE_BUILD_TYPE)
	message(STATUS "No build type selected, default to Release")
	set(CMAKE_BUILD_TYPE "Release")
endif()

## Basic Qt4
find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})
link_libraries(${QT_LIBRARIES})
##

add_executable( TouchKeyboardActivity touchkeyboardactivity.cpp )