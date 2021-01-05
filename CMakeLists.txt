cmake_minimum_required(VERSION 3.1)
project(UbuntuWallpaperChanger, VERSION 0.0.1)

configure_file(ubuntu_wallpaper_changer_config.h.in ubuntu_wallpaper_changer.h)
 
set(CMAKE_CXX_STANDARD 17)

# Include application entrypoint
add_executable(ubuntu_wallpaper_changer main.cpp)

# Include subdirectories
add_subdirectory(src)
list(APPEND EXTRA_LIBS src)
list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/src")

add_subdirectory(test)

target_link_libraries(ubuntu_wallpaper_changer PUBLIC ${EXTRA_LIBS})

target_include_directories(ubuntu_wallpaper_changer PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           "${EXTRA_INCLUDES}")