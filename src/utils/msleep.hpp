#ifndef INCLUDE_MSLEEP
#define INCLUDE_MSLEEP

#include <chrono>
#include <thread>

inline void msleep(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}


#endif
