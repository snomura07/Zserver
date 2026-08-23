#include <string>
#include "Router.h"

Router::Router(){}

Router::~Router(){}

void Router::setRequestPath(std::string path)
{
    requestPath = path;
}

bool Router::get(std::string routePath)
{
    return routePath == requestPath;
}

template<typename T>
bool Router::get(std::string routePath, std::vector<T> params, bool paramRequired)
{
    if(paramRequired && params.empty()){
        return false;
    }

    return routePath == requestPath;
}

template bool Router::get<int>(std::string, std::vector<int>, bool);
template bool Router::get<std::string>(std::string, std::vector<std::string>, bool);
