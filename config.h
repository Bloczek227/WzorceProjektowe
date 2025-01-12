#ifndef WP_PROJ_CONFIG_H
#define WP_PROJ_CONFIG_H

class Config
{
    static Config* instance;
protected:
    Config()=default;
public:
    int ticksPerSecond=10;
    static Config* Instance();
};
Config* Config::instance = nullptr;
Config* Config::Instance()
{
    if (! instance)
    {
        instance = new Config();
    }
    return instance;
}


#endif //WP_PROJ_CONFIG_H
