#pragma once
#include <random>
#include "strategyinterface.h"
#include "directory.cpp"

/**
 * The uniform strategy gets all files in the root
 * directory and its subdirectories and picks a file at random.
 */
class WeightedStrategy : public StrategyInterface
{
private:
    std::vector<std::pair<std::string, int>> directory_priorities;

public:
    WeightedStrategy(const std::vector<std::pair<std::string, int>> &directory_priorities)
        : directory_priorities(directory_priorities) {}

    /**
     * @brief Creates a directory-priority mapping, where the priority for each valid subdirectory
     * (given some root_path) is taken from the configuration file (if specified there) or
     * defaulted to 1.
     * 
     * @param std::vector<std::filesystem::path> subdirs - a vector of subdirectories;
     * @param const std::vector<std::pair<std::string, int> - a vector of directory-priority pairs, as
     * per the configuration parser output.
     * 
     * @return std::vector<std::pair<std::string, int>> - a vector of valid subdirectory-priority pairs
     */
    std::vector<std::pair<std::filesystem::path, int>>
    create_subdirs_with_priorities(std::vector<std::filesystem::path> subdirs)
    {
        std::vector<std::pair<std::filesystem::path, int>> subdirs_with_priorities;
        for (std::filesystem::path &subdir : subdirs)
        {
            auto found = std::find_if(directory_priorities.begin(),
                                      directory_priorities.end(),
                                      [&subdir](const std::pair<std::string, int> &dir_pair) { return subdir.filename() == dir_pair.first; });
            if (found != directory_priorities.end())
            {
                int indx = std::distance(directory_priorities.begin(), found);

                std::pair<std::filesystem::path, int> new_pair{
                    subdir,
                    directory_priorities[indx].second};
                subdirs_with_priorities.push_back(new_pair);
            }
            else
            {
                subdirs_with_priorities.push_back({subdir, 1});
            }
        }
        std::sort(subdirs_with_priorities.begin(),
                  subdirs_with_priorities.end(),
                  [](auto &left, auto &right) { return left.second < right.second; });
        return subdirs_with_priorities;
    }

    /**
     * @brief Normalizes the priorities, so that they sum to 1 (i.e. converts them to
     * a probability distribution).
     * 
     * @param const std::vector<std::pair<std::string, int>> subdirs_with_priorities - a vector of
     * directory-priority pairs;
     * 
     * @return std::vector<std::pair<std::string, float>> - a vector of directory-priority pairs,
     * with the priorities summing to 1.
     */
    std::vector<std::pair<std::string, float>>
    normalize_priorities(const std::vector<std::pair<std::string, int>> subdirs_with_priorities)
    {
        std::vector<std::pair<std::string, float>> normalized_priorities;
        int priority_sum = 0;
        for (auto &element : subdirs_with_priorities)
        {
            priority_sum += element.second;
        }
        for (auto &element : subdirs_with_priorities)
        {
            normalized_priorities.push_back({element.first, (float)element.second / (float)priority_sum});
        }
        return normalized_priorities;
    }

    std::vector<std::filesystem::path> execute(Directory root_dir) override
    {
        // draw random number
        std::random_device rd;
        std::mt19937_64 gen(rd());
        std::uniform_real_distribution<> dis(0.0, 1.0);
        double threshold = dis(gen);

        // get subfolders (vector of filesystem::path) + add root_dir.get_root_path() if there are valid files in it
        std::vector<std::filesystem::path> subdirs = root_dir.get_subdirs();
        if (root_dir.get_files().size() > 0)
        {
            subdirs.push_back(root_dir.get_root_path());
        }

        // normalize priorities (before normalization add unmentioned directories + current root path)
        std::vector<std::pair<std::filesystem::path, int>> subdirs_with_priorities =
            create_subdirs_with_priorities(subdirs);

        // loop over the subfolders and get the first folder with priority less than the random number

        // recursively call the method until no subdirectories exist, or current root dir is selected
    }
};