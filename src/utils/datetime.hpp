#ifndef INCLUDE_DATETIME
#define INCLUDE_DATETIME

#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <filesystem>

class DateTime {
public:
    // フォーマット: "2024/08/12 09:55:22"
    static std::string getFormattedDateTime(const std::string& format = "%Y/%m/%d %H:%M:%S") {
        std::time_t t = std::time(nullptr);
        std::tm tm;
        localtime_r(&t, &tm);
        std::ostringstream oss;
        oss << std::put_time(&tm, format.c_str());
        return oss.str();
    }

    // フォーマット: "20240812095532"
    static std::string getCompactDateTime() {
        return getFormattedDateTime("%Y%m%d%H%M%S");
    }

    // 現在時刻のUNIXタイムスタンプを文字列で取得
    static std::string getUnixTimestamp() {
        std::time_t t = std::time(nullptr);
        return std::to_string(t);
    }

    // std::filesystem::file_time_type から UNIX タイムスタンプを取得
    static std::string fileTimeToUnixTimestamp(const std::filesystem::file_time_type& ftime) {
        auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
            ftime - std::filesystem::file_time_type::clock::now()
            + std::chrono::system_clock::now());
        std::time_t cftime = std::chrono::system_clock::to_time_t(sctp);
        return std::to_string(cftime);
    }
};

#endif
