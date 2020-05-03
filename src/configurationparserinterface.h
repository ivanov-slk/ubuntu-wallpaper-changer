/**
 * Parses a configuration file.
*/
class ConfigurationParserInterface
{
public:
    virtual ~ConfigurationParserInterface() = default;

    /**
     * Parses the configuration file.
     * @param string config_path - the path to the configuration file.
     */
    virtual void read_config_file(string config_path);

    /**
     * Returns an object representing the parsed configuration.
     * @return FolderConfiguration
     */
    virtual FolderConfiguration create_configuration();
};

/**
 * The structure represents a folder path with some
 * pertinent properties.
 */
struct FolderConfiguration
{
    string path;
};