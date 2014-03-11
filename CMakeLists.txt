cmake_minimum_required(VERSION 2.8.8)

project( TouchKeyboardActivity )

if (NOT CMAKE_BUILD_TYPE)
	message(STATUS "No build type selected, default to Release")
	set(CMAKE_BUILD_TYPE "Release")
endif()

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Widgets)


add_executable( TouchKeyboardActivity touchkeyboardactivity.cpp )

# Use the Widgets module from Qt 5.
qt5_use_modules(TouchKeyboardActivity Widgets)
