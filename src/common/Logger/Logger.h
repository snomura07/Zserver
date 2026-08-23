#ifndef INCLUDED_LOGGER
#define INCLUDED_LOGGER
#include <fstream>
#include <string>
#include <MasterConfig/MasterConfig.h>

class Logger {
public:
    Logger();
    ~Logger();
    void init(std::string name);
    void writeInfoLog(std::string msg);
    void writeErrorLog(std::string msg);

private:
    void writeLog(std::string level, std::string msg);

private:
    std::ofstream ofs;
    MasterConfig masterConf;
};



#endif
