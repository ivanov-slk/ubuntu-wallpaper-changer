/**
 * The structure represents a folder path with some
 * pertinent properties.
 */
struct FolderConfiguration
{
    std::filesystem::path path;
    int seconds_before_change;
    std::vector<std::string> directory_exclusions;
    std::vector<std::pair<std::string, int>> directory_priorities;
    std::vector<std::pair<std::string, int>> directory_seconds;
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
