#pragma once
#include <filesystem>
#include <vector>

/**
 * Represents a directory on the filesystem, with 
 * appropriate getters for files and subdirectories.
 */
class Directory
{
private:
    std::filesystem::path path;

public:
    Directory(std::filesystem::path path) : path(path){};

    std::filesystem::path get_root_path() { return path; }

    /**
     * Get all files in the directory.
     */
    std::vector<std::filesystem::path> get_files()
    {
        std::vector<std::filesystem::path> dir_files;
        for (auto &p : std::filesystem::directory_iterator(path))
        {
            if (std::filesystem::is_regular_file(p.path()))
            {
                dir_files.push_back(p.path());
            }
        };
        return dir_files;
    };

    /**
     * Get all subdirectories in the directory.
     */
    std::vector<std::filesystem::path> get_subdirs()
    {
        std::vector<std::filesystem::path> dir_subdirs;
        for (auto &p : std::filesystem::directory_iterator(path))
        {
            if (std::filesystem::is_directory(p.path()))
            {
                dir_subdirs.push_back(p.path());
            }
        }
        return dir_subdirs;
    };
};