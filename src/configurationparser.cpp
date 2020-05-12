#pragma once
#include <algorithm>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <map>
#include <sstream>
#include <string>

#include "exceptions.h"
#include "configurationparserinterface.h"

/**
 * Parses a configuration file from a given file path.
 * Expects key-value pairs separated by "="; each on separate line.
*/
class ConfigurationParser : public ConfigurationParserInterface
{
private:
    const std::string config_file_path;
    const std::string config_in;
    std::map<std::string, std::string> params;
    FolderConfiguration config_parsed;

    /**
     * @brief Parses a line of the form key=value, where value is string.
     * 
     * @param std::string rhs - the right hand side of the "=" 
     * @returns std::string
     */
    std::string parse_root_path(std::string rhs)
    {
        bool valid = std::filesystem::exists(rhs);
        if (!valid)
        {
            std::string msg = "Path does not exist: " + rhs;
            throw ConfigurationParsingException(msg);
        }
        return rhs;
    }

    /**
     * @brief Parses a line of the form key=value, where value is int.
     * 
     * @param std::string rhs - the right hand side of the "="
     * @returns int
     */
    int parse_int(std::string rhs)
    {
        int parsed = std::stoi(rhs);
        // Make sure that the seconds to change is reasonable (i.e. the parsing makes sense),
        // but "reasonable" remains undefined...
        if ((parsed <= 0) || (parsed > 6000))
        {
            std::string msg = "Integer out of bounds: " + parsed;
            throw ConfigurationParsingException(msg);
        }
        return parsed;
    }
    /**
     * @brief Parses the directory exclusion list.
     * 
     * @param std::string input_line
     * @returns std::vector<std::string>
     */
    std::vector<std::string> parse_dir_exclusions(std::string input_line)
    {
        // separate by comma

        // put into a vector
    }

    /**
     * @brief Parses string:integer key-value pairs.
     * 
     * @param std::string input_line
     * @returns std::map<std::string, int>
     * 
     * Expects the key-value pairs (e.g. the folder:priority pairs) be
     * separated by comma.
     */
    std::map<std::string, int> parse_string_int_pairs(std::string input_line) {}

    /**
     * Validates the configuration inputs.
     * @param std::string key - the parameter's name
     * @param std::string value - the parameter's value
     * 
     * @returns bool - true if the parameter key-value pair is valid.
     * @throw ConfigurationParsingException - if wrong input is detected.
     */

    /**
     * @brief Parses a line given its key's name.
     * 
     * @param std::string key - the left-hand side of the "=";
     * @param std::string value - the right hand side of the "=".
     */
    void parse_line(std::string key, std::string value)
    {
        if (key == "path")
        {
            config_parsed.path = parse_root_path(value);
        }
        if (key == "seconds_before_change")
        {
            config_parsed.seconds_before_change = parse_int(value);
        }
    };

    /**
     * @brief Parses the configuration file.
     * 
     * The general strategy for parsing is to have a different parsing method
     * for each of the expected configuration parameters (pretty inefficient, eh?).
     * The configuration file is read line by line and the left-hand side of the
     * "equals" sign is checked if is expected. If it is, the appropriate method is
     * called and its return value is put into the `FolderConfiguration`. If not,
     * the line is skipped. Any validations are done within the method.
     */
    void parse_config_file()
    {
        if (!std::filesystem::exists(config_file_path))
        {
            throw FileIOException("The file was not found.");
        };

        std::ifstream config_file(config_file_path);
        std::string key;
        std::string value;
        std::string line;
        while (config_file.good())
        {
            getline(config_file, line);
            line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
            if (line[0] == '#' || line.empty())
                continue;

            replace(line.begin(), line.end(), '=', ' ');
            std::istringstream ss(line);
            ss >> key >> value;
            parse_line(key, value);
        }
    };

public:
    ConfigurationParser() = default;
    ConfigurationParser(std::string filename) : config_file_path(filename){};

    /**
     * @brief Creates a configuration object from a filename.
     * 
     * @returns FolderConfiguration
     */
    FolderConfiguration create_configuration() override
    {
        parse_config_file();
        return config_parsed;
    }
};
