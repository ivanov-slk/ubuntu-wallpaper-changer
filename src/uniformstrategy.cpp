#include "strategyinterface.h"
#include "directory.cpp"

/**
 * The uniform strategy gets all files in the root
 * directory and its subdirectories and picks a file at random.
 */
class UniformStrategy : public StrategyInterface
{
public:
    std::vector<std::filesystem::path> execute(Directory root_dir) override
    {
        std::vector<std::filesystem::path> all_files = root_dir.get_files();
        std::vector<std::filesystem::path> all_subdirs = root_dir.get_subdirs();
        for (auto &sub_dir : all_subdirs)
        {
            std::vector<std::filesystem::path> subdir_files = execute(Directory{sub_dir});
            all_files.reserve(all_files.size() + subdir_files.size());
            all_files.insert(all_files.end(), subdir_files.begin(), subdir_files.end());
        }
        return all_files;
    }
};