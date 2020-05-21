#pragma once
#include "strategyinterface.h"
#include "directory.cpp"

/**
 * The uniform strategy gets all files in the root
 * directory and its subdirectories and picks a file at random.
 */
class UniformStrategy : public StrategyInterface
{
private:
    std::vector<std::filesystem::path> cached_files;
    std::vector<std::filesystem::path> traverse_get_files(Directory root_dir)
    {
        std::vector<std::filesystem::path> all_files = root_dir.get_files();
        std::vector<std::filesystem::path> all_subdirs = root_dir.get_subdirs();
        for (auto &sub_dir : all_subdirs)
        {
            std::vector<std::filesystem::path> subdir_files =
                traverse_get_files(Directory{sub_dir,
                                             root_dir.get_exclusions(),
                                             root_dir.get_allowed_extensions()});

            all_files.reserve(all_files.size() + subdir_files.size());
            all_files.insert(all_files.end(), subdir_files.begin(), subdir_files.end());
        }
        return all_files;
    }

public:
    std::vector<std::filesystem::path> execute(Directory root_dir) override
    {
        if (!cached_files.empty())
        {
            return cached_files;
        }
        return traverse_get_files(root_dir);
    }
};