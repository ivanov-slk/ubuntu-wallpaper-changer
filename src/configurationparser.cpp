#pragma once
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <regex>
#include <sstream>
#include <string>

#include "configurationparserinterface.h"
#include "exceptions.h"

/**
 * Parses a configuration file from a given file path.
 * Expects key-value pairs separated by "="; each on separate line.
 *
 * TODO: this whole thing contains too much duplicated code and if-else stuff.
 * Consider refactoring to something more reasonable.
 */
class ConfigurationParser : public ConfigurationParserInterface {
 private:
  const std::string config_file_path;
  const std::string config_in;
  FolderConfiguration config_parsed;

  /**
   * @brief Parses a line of the form key=value, where value is string.
   *
   * @param std::string rhs - the right hand side of the "="
   * @returns std::string
   * @throw ConfigurationParsingException
   */
  std::string parse_policy(std::string rhs) {
    if ((rhs == "weighted") || (rhs == "uniform")) {
      return rhs;
    }
    throw ConfigurationParsingException("Invalid policy choice.");
  }

  /**
   * @brief Parses a line of the form key=value, where value is path.
   * Checks if the path exist.
   *
   * @param std::string rhs - the right hand side of the "="
   * @returns std::string
   * @throw ConfigurationParsingException
   */
  std::string parse_root_path(std::string rhs) {
    bool valid = std::filesystem::exists(rhs);
    if (!valid) {
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
   * @throw ConfigurationParsingException
   */
  int parse_int(std::string rhs) {
    int parsed = std::stoi(rhs);
    // Make sure that the seconds to change is reasonable (i.e. the parsing
    // makes sense), but "reasonable" remains undefined...
    if ((parsed <= 0) || (parsed > 6000)) {
      std::string msg = "Integer out of bounds: " + parsed;
      throw ConfigurationParsingException(msg);
    }
    return parsed;
  }
  /**
   * @brief Parses the directory exclusion list.
   *
   * @param std::string_view rhs
   * @returns std::vector<std::string>
   */
  std::vector<std::string> parse_string_list(std::string rhs) {
    replace(rhs.begin(), rhs.end(), ',', ' ');
    std::istringstream ss(rhs);
    std::vector<std::string> dir_exclusions{
        std::istream_iterator<std::string>{ss},
        std::istream_iterator<std::string>{}};
    return dir_exclusions;
  }

  /**
   * @brief Parses string:integer key-value pairs.
   *
   * @param std::string_view rhs
   * @returns std::vector<std::pair<std::string, int>> A vector of pairs,
   * where the first element is a directory name and the second element is
   * some directory property (seconds or priority up to this point). The
   * vector is sorted by the second elements in the pairs.
   *
   * Expects the key-value pairs (e.g. the folder:priority pairs) be
   * separated by comma.
   */
  std::vector<std::pair<std::string, int>> parse_string_int_pairs(
      std::string rhs) {
    std::vector<std::pair<std::string, int>> vec_pairs;
    // replace(rhs.begin(), rhs.end(), ',', ' ');
    std::istringstream ss(rhs);
    std::string token_comma;
    while (getline(ss, token_comma, ',')) {
      std::string pair_first;
      std::string pair_second;
      int pair_second_parsed;
      // replace(token_comma.begin(), token_comma.end(), ':', ' ');
      std::istringstream token_comma_ss(token_comma);
      std::vector<std::string> token_list_colon;
      std::string token_colon;
      while (getline(token_comma_ss, token_colon, ':')) {
        token_colon =
            std::regex_replace(token_colon, std::regex("^ +| +$|( ) +"), "$1");
        token_list_colon.push_back(token_colon);
      }
      // token_ss >> pair_first >> pair_second;
      // pair_second_parsed = parse_int(token_list_colon.at(1));
      std::pair<std::string, int> vec_element{
          token_list_colon.at(0), parse_int(token_list_colon.at(1))};
      vec_pairs.push_back(vec_element);
    }
    std::sort(vec_pairs.begin(), vec_pairs.end(), [](auto &left, auto &right) {
      return left.second < right.second;
    });
    return vec_pairs;
  }

  /**
   * @brief Parses string:string key-value pairs.
   *
   * @param std::string_view rhs
   * @returns std::vector<std::pair<std::string, int>> A vector of pairs,
   * where the first element is a directory name and the second element is
   * some directory property (seconds or priority up to this point). The
   * vector is sorted by the second elements in the pairs.
   *
   * Expects the key-value pairs (e.g. the folder:priority pairs) be
   * separated by comma.
   */
  std::map<std::string, std::string> parse_pic_options(std::string rhs) {
    std::vector<std::string> allowed_values{"none",   "wallpaper", "centered",
                                            "scaled", "stretched", "zoom",
                                            "spanned"};
    std::map<std::string, std::string> map_out;
    // replace(rhs.begin(), rhs.end(), ',', ' ');
    std::istringstream ss(rhs);
    std::vector<std::string> token_list_comma;
    std::string token_comma;
    while (getline(ss, token_comma, ',')) {
      token_comma =
          std::regex_replace(token_comma, std::regex("^ +| +$|( ) +"), "$1");
      std::string dir;
      std::string pic_option;
      // replace(token.begin(), token.end(), ':', ' ');
      std::vector<std::string> token_list_colon;
      std::string token_colon;
      std::istringstream token_comma_ss(token_comma);
      while (getline(token_comma_ss, token_colon, ':')) {
        token_colon =
            std::regex_replace(token_colon, std::regex("^ +| +$|( ) +"), "$1");
        token_list_colon.push_back(token_colon);
      }
      // token_ss >> dir >> pic_option;
      dir = token_list_colon.at(0);
      pic_option = token_list_colon.at(1);
      if (std::find(allowed_values.begin(), allowed_values.end(), pic_option) !=
          allowed_values.end()) {
        map_out[dir] = pic_option;
      } else {
        throw ConfigurationParsingException{"Invalid picture-options value."};
      }
    }
    return map_out;
  }

  /**
   * @brief Parses a line given its key's name.
   *
   * @param std::string key - the left-hand side of the "=";
   * @param std::string value - the right hand side of the "=".
   */
  void parse_line(std::string key, std::string value) {
    if (key == "path") {
      config_parsed.path = parse_root_path(value);
    } else if (key == "policy") {
      config_parsed.policy = parse_policy(value);
    } else if (key == "seconds_before_change") {
      config_parsed.seconds_before_change = parse_int(value);
    } else if (key == "directory_exclusions") {
      config_parsed.directory_exclusions = parse_string_list(value);
    } else if (key == "file_allowed_extensions") {
      config_parsed.file_allowed_extensions = parse_string_list(value);
    } else if (key == "directory_priorities") {
      config_parsed.directory_priorities = parse_string_int_pairs(value);
    } else if (key == "directory_seconds") {
      config_parsed.directory_seconds = parse_string_int_pairs(value);
    } else if (key == "directory_pic_options") {
      config_parsed.directory_pic_options = parse_pic_options(value);
    } else {
      throw ConfigurationParsingException{"Wrong setting key."};
    }
  };

  /**
   * @brief Parses the configuration file.
   *
   * The general strategy for parsing is to have a different parsing method
   * for each of the expected configuration parameters (pretty inefficient,
   * eh?). The configuration file is read line by line and the left-hand side of
   * the "equals" sign is checked if is expected. If it is, the appropriate
   * method is called and its return value is put into the
   * `FolderConfiguration`. If not, the line is skipped. Any validations are
   * done within the method.
   */
  void parse_config_file() {
    if (!std::filesystem::exists(config_file_path)) {
      throw FileIOException("The file was not found.");
    };

    std::ifstream config_file(config_file_path);
    std::string key;
    std::string value;
    std::string line;
    while (config_file.good()) {
      getline(config_file, line);
      // line.erase(std::remove_if(line.begin(), line.end(), ::isspace),
      //  line.end());
      if (line[0] == '#' || line.empty()) continue;

      // replace(line.begin(), line.end(), '=', ' ');
      std::istringstream ss(line);
      std::vector<std::string> split_line;
      std::string line_token;
      while (std::getline(ss, line_token, '=')) {
        // line_token.erase(
        //     std::remove_if(line_token.begin(), line_token.end(), ::isspace),
        //     line_token.end());
        line_token =
            std::regex_replace(line_token, std::regex("^ +| +$|( ) +"), "$1");
        split_line.push_back(line_token);
      };
      // ss >> key >> value;
      parse_line(split_line.at(0), split_line.at(1));
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
  FolderConfiguration create_configuration() override {
    parse_config_file();
    return config_parsed;
  }
};
