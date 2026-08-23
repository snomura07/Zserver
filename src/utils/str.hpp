#ifndef INCLUDED_STR
#define INCLUDED_STR

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

inline std::string str(int num)
{
    return std::to_string(num);
}

inline std::string str(double num)
{
    return std::to_string(num);
}

inline void split(std::string msg, std::string separator, std::vector<std::string> &sep_list)
{
    char separator_ =  *separator.c_str();

    std::stringstream ss{msg};
    std::string str_;
    while ( getline(ss, str_, separator_) ){
        sep_list.push_back(str_);
    }
}

template<typename... Args>
std::string strJoin(const Args&... args) {
    std::ostringstream oss;

    ((oss << args), ...);

    return oss.str();
}

#endif
