cmake_minimum_required(VERSION 3.1)
project(UbuntuWallpaperChanger VERSION 0.0.1)

configure_file(UbuntuWallpaperChangerConfig.h.in UbuntuWallpaperChanger.h)
 
set(CMAKE_CXX_STANDARD 17)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Include application entrypoint
add_executable(UbuntuWallpaperChanger main.cpp)

target_include_directories(UbuntuWallpaperChanger PUBLIC
                           "${PROJECT_BINARY_DIR}")