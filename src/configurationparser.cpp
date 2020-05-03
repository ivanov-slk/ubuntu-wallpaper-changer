#include <string>
#include "configurationparserinterface.h"

using namespace std;

/**
 * Parses a configuration file from a given file path.
 * Expects key-value pairs separated by "="; each on separate line.
*/
class ConfigurationParser : public ConfigurationParserInterface
{
private:
    string config_path;

public:
    ConfigurationParser() = default;
    ConfigurationParser(string filename) : config_path(filename){};
    void read_config_file() override{};
    FolderConfiguration create_configuration() override{};
};