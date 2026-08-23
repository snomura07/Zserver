#include "MasterConfig.h"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

MasterConfig::MasterConfig():
    jsonPath("/opt/raptor/config/MasterConfig.json"),
    localhost(""),
    raptorIp(""),
    subPort(0),
    pubPort(0),
    configPath("/opt/raptor/config/"),
    imagePath("/opt/raptor/image/"),
    cameraPath("/opt/raptor/image/camera/"),
    logPath("/opt/raptor/log/"),
    binPath("/opt/raptor/bin/"),
    apiHost(""),
    apiPort(0),
    chatTopic(""),
    zserverTopic(""),
    zserverPort(0),
    processMonitorTopic(""),
    shutdownTopic(""),
    raptorLoggerApiEndpoint(""),
    raptorLoggerApiSetLogPath(""),
    mapFmt()
{}

MasterConfig::~MasterConfig(){}


void MasterConfig::read(){
    std::ifstream jsonFile(jsonPath);

    if (jsonFile.is_open()) {
        jsonFile >> jsonData;
        localhost                 = jsonData["localhost"];
        raptorIp                  = jsonData["raptorIp"];
        subPort                   = jsonData["subPort"];
        pubPort                   = jsonData["pubPort"];
        configPath                = jsonData["path"]["config"];
        imagePath                 = jsonData["path"]["image"];
        cameraPath                = jsonData["path"]["camera"];
        logPath                   = jsonData["path"]["log"];
        binPath                   = jsonData["path"]["bin"];
        apiHost                   = jsonData["api"]["host"];
        apiPort                   = jsonData["api"]["port"];
        chatTopic                 = jsonData["chat"]["topic"];
        zserverTopic              = jsonData["zserver"]["topic"];
        zserverPort               = jsonData["zserver"]["port"];
        processMonitorTopic       = jsonData["processMonitor"]["topic"];
        shutdownTopic             = jsonData["shutdown"]["topic"];
        raptorLoggerApiEndpoint   = jsonData["raptorLoggerApi"]["endpoint"];
        raptorLoggerApiSetLogPath = jsonData["raptorLoggerApi"]["path"]["setLog"];

        mapFmt["localhost"]                 = localhost;
        mapFmt["raptorIp"]                  = raptorIp;
        mapFmt["subPort"]                   = subPort;
        mapFmt["pubPort"]                   = pubPort;
        mapFmt["configPath"]                = configPath;
        mapFmt["imagePath"]                 = imagePath;
        mapFmt["cameraPath"]                = cameraPath;
        mapFmt["logPath"]                   = logPath;
        mapFmt["binPath"]                   = binPath;
        mapFmt["apiHost"]                   = apiHost;
        mapFmt["apiPort"]                   = apiPort;
        mapFmt["chatTopic"]                 = chatTopic;
        mapFmt["zserverTopic"]              = zserverTopic;
        mapFmt["zserverPort"]               = zserverPort;
        mapFmt["processMonitorTopic"]       = processMonitorTopic;
        mapFmt["shutdownTopic"]             = shutdownTopic;
        mapFmt["raptorLoggerApiEndpoint"]   = raptorLoggerApiEndpoint;
        mapFmt["raptorLoggerApiSetLogPath"] = raptorLoggerApiSetLogPath;
    }
    else{
        std::cerr << "file open error" << std::endl;
    }
}

std::string MasterConfig::getStringFromMap(std::string key)
{
    auto it = mapFmt.find(key);
    if (it != mapFmt.end()) {
        if (std::holds_alternative<std::string>(it->second)) {
            return std::get<std::string>(it->second);
        } else {
            throw std::runtime_error("Key does not hold a string value");
        }
    } else {
        throw std::runtime_error("Key not found in map");
    }
}

int MasterConfig::getIntFromMap(std::string key)
{
    auto it = mapFmt.find(key);
    if (it != mapFmt.end()) {
        if (std::holds_alternative<int>(it->second)) {
            return std::get<int>(it->second);
        } else {
            throw std::runtime_error("Key does not hold an int value");
        }
    } else {
        throw std::runtime_error("Key not found in map");
    }
}
