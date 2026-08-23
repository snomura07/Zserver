#include "Logger.h"
#include <string>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <datetime.hpp>

Logger::Logger(){}
Logger::~Logger(){
    ofs.close();
}

void Logger::init(std::string name)
{
    masterConf.read();
    std::string fileName = name + ".log";
    std::string filePath = masterConf.logPath + fileName;
    ofs.open(filePath, std::ios::app);

    writeInfoLog(name+" start");
}

void Logger::writeInfoLog(std::string msg){
    writeLog("info", msg);
}

void Logger::writeErrorLog(std::string msg){
    writeLog("error", msg);
}

void Logger::writeLog(std::string level, std::string msg){
    ofs << DateTime::getFormattedDateTime();
    ofs << " [" << level << "] : " << msg << std::endl;
}
