/**
 * The structure represents a folder path with some
 * pertinent properties.
 */
struct FolderConfiguration
{
    std::filesystem::path path;
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
