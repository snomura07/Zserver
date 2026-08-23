#ifndef INCLUDED_ROUTER
#define INCLUDED_ROUTER
#include <string>
#include <vector>

class Router
{
public:
    Router();
    ~Router();
    void setRequestPath(std::string path);
    bool get(std::string routePath);

    template<typename T>
    bool get(std::string routePath, std::vector<T> params, bool paramRequired);

private:
    std::string requestPath;
};

#endif
