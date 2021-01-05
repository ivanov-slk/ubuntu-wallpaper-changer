#pragma once
#include <algorithm>
#include <random>
#include <vector>
#include <filesystem>

/**
 * Picks random path from a vector of std::filesystem::path-s.
 * Returns empty (default) std::filesystem::path if the input 
 * vector is empty.
 */
class FilePicker
{
private:
    const std::vector<std::filesystem::path> path_vector;

public:
    FilePicker(const std::vector<std::filesystem::path> &path_vector) : path_vector(path_vector){};
    std::filesystem::path pick_random_path()
    {
        std::vector<std::filesystem::path> out_paths;
        if (path_vector.empty())
        {
            std::filesystem::path empty;
            return empty;
        }
        std::sample(
            path_vector.begin(),
            path_vector.end(),
            std::back_inserter(out_paths),
            1,
            std::mt19937{std::random_device{}()});
        return out_paths[0];
    }
};