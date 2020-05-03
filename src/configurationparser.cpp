#include <string>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <map>
#include "exceptions.h"
#include "configurationparserinterface.h"

using namespace std;

/**
 * Parses a configuration file from a given file path.
 * Expects key-value pairs separated by "="; each on separate line.
*/
class ConfigurationParser : public ConfigurationParserInterface
{
    // AF: represents a configuration parser.
    // RI: Config path is not mutated after construction.
    // SRE: config_path private and constant, no getters or setters.
private:
    const string config_file_path;
    const string config_in;
    map<string, string> params;

    /**
     * Parses the configuration file.
     * @param string config_path - the path to the configuration file.
     */
    void read_config_file()
    {
        if (!std::filesystem::exists(config_file_path))
        {
            throw FileIOException("The file was not found.");
        };

        std::ifstream config_file(config_file_path);
        if (config_file.is_open())
        {
            string key;
            string value;
            while (config_file >> key >> value)
            {
                params[key] = value; // input them into the map
            }
            config_file.close();
        }
        else
        {
            throw FileIOException("The file could not be opened.");
        }
    };

    /**
     * Parses the read configuration into an object.
     * @return FolderConfiguration
     */
    FolderConfiguration parse_config_file()
    {
        FolderConfiguration folder_config;
        folder_config.path = params["path"];
        return folder_config;
    };

public:
    ConfigurationParser() = default;
    ConfigurationParser(string filename) : config_file_path(filename){};

    /**
     * Creates a configuration object from a filename.
     * @throw path_not_set
     */
    FolderConfiguration create_configuration() override
    {
        read_config_file();
        return parse_config_file();
    }
};
