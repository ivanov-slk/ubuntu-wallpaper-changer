/**
 * Parses a configuration file.
*/
class ConfigurationParserInterface
{
public:
    virtual ~ConfigurationParserInterface() = default;

    /**
     * Parses the configuration file.
     */
    virtual void read_config_file();

    /**
     * Returns an object representing the parsed configuration
     */
    virtual void create_configuration();
};