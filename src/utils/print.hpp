#ifndef INCLUDED_PRINT
#define INCLUDED_PRINT

#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <datetime.hpp>

template<typename... Args>
void print(const Args&... args) {
    std::ostringstream oss;
    oss << "[" << DateTime::getFormattedDateTime() << "]";

    ((oss << " " << args), ...);

    std::cout << oss.str() << std::endl;
}

template<typename... Args>
void printe(const Args&... args) {
    std::ostringstream oss;
    oss << DateTime::getFormattedDateTime();

    ((oss << " " << args), ...);

    std::cerr << oss.str() << std::endl;
}

template<typename... Args>
void gprint(const Args&... args) {
    std::ostringstream oss;

    ((oss << " \033[92m" << args << "\033[0m"), ...);

    std::cout << oss.str() << std::endl;
}

#endif
