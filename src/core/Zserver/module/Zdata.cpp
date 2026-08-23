#include "Zdata.h"

Zdata::Zdata(){}
Zdata::Zdata(const std::string& jsonString){
    parse(jsonString);
}
Zdata::~Zdata(){}

void Zdata::parse(const std::string& jsonString) {
    try {
        JsonData = nlohmann::json::parse(jsonString);
    } catch (nlohmann::json::parse_error& e) {
        std::cerr << "JSONパースエラー: " << e.what() << std::endl;
    }

    if (JsonData.contains("main_command") && JsonData.contains("optional_value")) {
        mainCommand   = JsonData["main_command"].get<std::string>();
        optValues     = JsonData["optional_value"].get<std::vector<int>>();
        optStrings    = JsonData["optional_string"].get<std::vector<std::string>>();
    } else {
        std::cerr << "必要なキーが見つかりません。" << std::endl;
    }
}
