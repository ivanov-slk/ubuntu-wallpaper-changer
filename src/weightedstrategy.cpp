#pragma once
#include <random>
#include <numeric>
#include "strategyinterface.h"
#include "filepicker.cpp"
#include "directory.cpp"

/**
 * The uniform strategy gets all files in the root
 * directory and its subdirectories and picks a file at random.
 */
class WeightedStrategy : public StrategyInterface
{
private:
    std::vector<std::pair<std::filesystem::path, int>> directory_priorities;

public:
    WeightedStrategy(const std::vector<std::pair<std::filesystem::path, int>> &directory_priorities)
        : directory_priorities(directory_priorities) {}
    WeightedStrategy(const std::vector<std::pair<std::string, int>> &directory_priorities_input)
    {
        // this convertion may be too explicit
        std::vector<std::pair<std::filesystem::path, int>> converted_priorities;
        for (auto &dir_pair : directory_priorities)
        {
            converted_priorities.push_back({std::filesystem::path{dir_pair.first}, dir_pair.second});
        }
        directory_priorities = converted_priorities;
    }

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
     * @brief Normalizes the priorities, so that they represent a cumulative distribution function.
     * 
     * @param const std::vector<std::pair<std::string, int>> subdirs_with_priorities - a vector of
     * directory-priority pairs;
     * 
     * @return std::vector<std::pair<std::string, float>> - a vector of directory-priority pairs,
     * with the priorities summing to 1.
     * 
     * The basic steps are the following:
     * 1. Divide each priority by the sum of all priorities
     * (results in a probability mass function, i.e. gives the probability that each pair will be chosen);
     * 2. Take the cumulative sum for each priority -
     * 3. I.e. if the initial priorities are 50, 20, 30:
     * - step 1 results in 0.5, 0.2, 0.3;
     * - the values are sorted - 0.2, 0.3, 0.5;
     * - step 2 results in 0.2, 0.5, 1.0
     * 4. This means that the probability of getting the directory with initial priority 50 is still 50%,
     * and the probability of getting the directory with initial priority 30 is still 30%.
     */
    std::vector<std::pair<std::filesystem::path, float>>
    normalize_priorities(const std::vector<std::pair<std::filesystem::path, int>> subdirs_with_priorities)
    {
        std::vector<std::pair<std::filesystem::path, float>> normalized_priorities;

        // get the sum of the priorities
        int priority_sum = 0;
        for (auto &element : subdirs_with_priorities)
        {
            priority_sum += element.second;
        }

        // get the share of each priority in the total sum (i.e. make them sum to one; i.e. make this a probability mass function)
        for (auto &element : subdirs_with_priorities)
        {
            normalized_priorities.push_back({element.first, (float)element.second / (float)priority_sum});
        }

        // take the PMF from above and convert it to cumulative distribution function; works in-place
        std::partial_sum(normalized_priorities.begin(),
                         normalized_priorities.end(),
                         normalized_priorities.begin(),
                         [](const std::pair<std::filesystem::path, float> &x,
                            const std::pair<std::filesystem::path, float> &y) {
                             return std::pair<std::filesystem::path, float>{y.first, x.second + y.second};
                         });
        return normalized_priorities;
    }

    /**
     * @brief Picks a path from vector of filesystem::path at random, given the weights.
     * 
     * @param std::vector<std::pair<std::filesystem::path, float>> normalized_priorities - As per normalize_priorities() output;
     * 
     * @return std::filesystem::path
     * 
     * Expects that the input vector is sorted by priority, smallest first. This should be provided by
     * default by normalize_priorities() (although, formally, the method is public and could be used anywhere);
     * no explicit enforcement here.
     * 
     * An idea to make it more general is to add 1. sorting of the input vector at the beginning and 2. taking
     * a random uniform number only in the range (from min to max) of the pair's second element.
     */
    std::filesystem::path pick_directory(std::vector<std::pair<std::filesystem::path, float>> normalized_priorities,
                                         bool testing)
    {
        // set random generator for the uniform distribution, or fix at 0.5 for testing purposes
        double threshold = 0.5;
        if (!testing)
        {
            std::random_device rd;
            std::mt19937_64 gen(rd());
            std::uniform_real_distribution<> dis(0.0, 1.0);
            threshold = dis(gen);
        }
        // extract the first directory that has priority less than or equal to `threshold`
        std::vector<std::pair<std::filesystem::path, float>> picked_paths;
        std::pair<std::string, float> check_equal_priority_pair;
        for (auto &dir_pair : normalized_priorities)
        {
            if (threshold <= dir_pair.second && picked_paths.empty())
            {
                return dir_pair.first;
            }
        }
        return std::filesystem::path{};
    }

    std::vector<std::filesystem::path>
    execute(Directory root_dir) override
    {
        std::vector<std::filesystem::path> subdirs = root_dir.get_subdirs();
        if (subdirs.empty())
        {
            return root_dir.get_files();
        }

        if (root_dir.get_files().size() > 0)
        {
            subdirs.push_back(root_dir.get_root_path());
        }
        std::vector<std::pair<std::filesystem::path, int>> subdirs_with_priorities =
            create_subdirs_with_priorities(subdirs);

        std::vector<std::pair<std::filesystem::path, float>> normalized_priorities = normalize_priorities(subdirs_with_priorities);

        // loop over the subfolders and get the first folder with priority less than the random number
        std::filesystem::path picked_subdir = pick_directory(normalized_priorities, false);
        // We have picked root_dir, so just return the files in it.
        // Otherwise, we would be just repeating the whole process over directories we have already checked.
        // And potentially just repeat selecting the root path and checking over and over again its subfolders.
        if (picked_subdir == root_dir.get_root_path())
        {
            return root_dir.get_files();
        }
        return execute(Directory{picked_subdir,
                                 root_dir.get_exclusions(),
                                 root_dir.get_allowed_extensions()});
    }
};