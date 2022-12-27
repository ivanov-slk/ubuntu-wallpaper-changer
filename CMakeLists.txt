cmake_minimum_required(VERSION 3.25)
project(UbuntuWallpaperChanger, VERSION 1.1.0)

configure_file(ubuntu_wallpaper_changer_config.h.in ubuntu_wallpaper_changer.h)
 
set(CMAKE_CXX_STANDARD 20)

# Include application entrypoint
add_executable(ubuntu_wallpaper_changer main.cpp)

# Include subdirectories
add_subdirectory(src)
list(APPEND EXTRA_LIBS src)
list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/src")

# Configure GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
FetchContent_MakeAvailable(googletest)

# Configure the tests suite and executables
add_subdirectory(test)

target_link_libraries(ubuntu_wallpaper_changer PUBLIC ${EXTRA_LIBS})

target_include_directories(ubuntu_wallpaper_changer PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           "${EXTRA_INCLUDES}")