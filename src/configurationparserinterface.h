class ConfigurationParserInterface
{
public:
    virtual ~ConfigurationParserInterface() = default;
    virtual void read_config_file();
    virtual void create_configuration();
};