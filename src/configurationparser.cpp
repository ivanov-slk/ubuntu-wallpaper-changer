#pragma once
#include <algorithm>
#include <string>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <map>

#include "exceptions.h"
#include "configurationparserinterface.h"

#include <iostream>
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
    const std::string config_file_path;
    const std::string config_in;
    std::map<std::string, std::string> params;

    /**
     * Validates the configuration inputs.
     * @param std::string key - the parameter's name
     * @param std::string value - the parameter's value
     * 
     * @returns bool - true if the parameter key-value pair is valid.
     * @throw ConfigurationParsingException - if wrong input is detected.
     */
    void validate_inputs(std::string key, std::string value)
    {
        // Parse the path parameter
        if (key == "path")
        {
            bool valid = std::filesystem::exists(value);
            if (!valid)
            {
                std::string msg = "Path does not exist: " + key + " " + value;
                throw ConfigurationParsingException(msg);
            }
        }

        // Parse the seconds to change parameter
        if (key == "seconds_before_change")
        {
            int check = std::stoi(value);
            // Make sure that the seconds to change is reasonable (i.e. the parsing makes sense),
            // but "reasonable" remains undefined...
            if ((check <= 0) || (check > 6000))
            {
                std::string msg = "Invalid value: " + key + " " + value;
                throw ConfigurationParsingException(msg);
            }
        }
    }

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
            std::string key;
            std::string value;
            std::string line;
            while (config_file.good())
            {
                getline(config_file, line);
                replace(line.begin(), line.end(), '=', ' ');
                std::istringstream ss(line);
                ss >> key >> value;
                validate_inputs(key, value);
                params[key] = value;
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
        folder_config.path = std::filesystem::path(params["path"]);
        folder_config.seconds_before_change = std::stoi(params["seconds_before_change"]); // this kind of doubles validate_inputs();
        return folder_config;
    };

public:
    ConfigurationParser() = default;
    ConfigurationParser(std::string filename) : config_file_path(filename){};

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
