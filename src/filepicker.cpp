#include <algorithm>
#include <random>
#include <vector>
#include <filesystem>

class FilePicker
{
private:
    const std::vector<std::filesystem::path> path_vector;

public:
    FilePicker(const std::vector<std::filesystem::path> &path_vector) : path_vector(path_vector){};
    std::filesystem::path pick_random_path()
    {
        std::vector<std::filesystem::path> out_path;
        std::sample(
            path_vector.begin(),
            path_vector.end(),
            std::back_inserter(out_path),
            1,
            std::mt19937{std::random_device{}()});
        return out_path[0];
    }
};