#pragma once
#include <algorithm>
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
    std::vector<std::string> exclusions;
    std::vector<std::string> allowed_extensions;

public:
    Directory(std::filesystem::path path) : path(path){};
    Directory(std::filesystem::path path,
              std::vector<std::string> exclusions,
              std::vector<std::string> allowed_extensions) : path(path),
                                                             exclusions(exclusions),
                                                             allowed_extensions(allowed_extensions){};

    std::filesystem::path get_root_path() { return path; }

    /**
     * Get all files in the directory. If `allowed_extensions` is set via
     * the constructor, returns only the files with matching extensions.
     */
    std::vector<std::filesystem::path> get_files()
    {
        std::vector<std::filesystem::path> dir_files;
        for (auto &p : std::filesystem::directory_iterator(path))
        {
            if (!allowed_extensions.empty())
            {
                if (std::find(allowed_extensions.begin(),
                              allowed_extensions.end(),
                              p.path().extension()) != allowed_extensions.end())
                {
                    dir_files.push_back(p.path());
                }
            }
            else
            {
                if (std::filesystem::is_regular_file(p.path()))
                {
                    dir_files.push_back(p.path());
                }
            }
        };
        return dir_files;
    };

    /**
     * Get all subdirectories in the directory. If `exclusions` is set via
     * the constructor, excludes the matches from the final result.
     */
    std::vector<std::filesystem::path> get_subdirs()
    {
        std::vector<std::filesystem::path> dir_subdirs;
        for (auto &p : std::filesystem::directory_iterator(path))
        {
            if (!exclusions.empty())
            // we have exclusions list, check it
            {

                if (std::filesystem::is_directory(p.path()) &&
                    std::find(exclusions.begin(),
                              exclusions.end(),
                              p.path().filename()) == exclusions.end()) // not in exclusions
                {
                    dir_subdirs.push_back(p.path());
                }
            }
            else
            {
                // we don't have exclusions list, return all subdirectories
                if (std::filesystem::is_directory(p.path()))
                {
                    dir_subdirs.push_back(p.path());
                }
            }
        }
        return dir_subdirs;
    };
};