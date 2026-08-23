#include <string>
#include <nlohmann/json.hpp>
#include <MasterConfig/MasterConfig.h>

class AppConfig{
public:
    AppConfig();
    ~AppConfig();
    void read();
    void dump();

public:
    std::string modName;
    int healthCheckcPort;
    MasterConfig master;

private:
    nlohmann::json jsonData;
    std::string jsonPath;
};
