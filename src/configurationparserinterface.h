/**
 * The structure represents a folder path with some
 * pertinent properties.
 */
struct FolderConfiguration
{
    std::filesystem::path path;
    std::string policy;
    int seconds_before_change;
    std::vector<std::string> directory_exclusions;
    std::vector<std::string> file_allowed_extensions;
    std::vector<std::pair<std::string, int>> directory_priorities;
    std::vector<std::pair<std::string, int>> directory_seconds;
    std::map<std::string, std::string> directory_pic_options;
};

/**
 * Parses a configuration file.
*/
class ConfigurationParserInterface
{
public:
    virtual ~ConfigurationParserInterface() = default;

    /**
     * Returns an object representing the parsed configuration.
     * @return FolderConfiguration
     */
    virtual FolderConfiguration create_configuration() = 0;
};
