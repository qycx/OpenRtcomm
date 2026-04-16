#include "mLogger.h" 
#include <iostream>
#include <fstream>
#include <filesystem>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

namespace fs = std::filesystem;

static std::string GetCurrentTimeStamp() {
    auto now = std::chrono::system_clock::now();
    std::time_t in_time_t = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

void WriteLog(const std::string& message, const std::string& fileName) {
    std::string folderPath = "D:\\log";

    try {
        if (!fs::exists(folderPath)) {
            fs::create_directories(folderPath);
        }
        fs::path fullPath = fs::path(folderPath) / fileName;

        std::ofstream logFile(fullPath, std::ios::out | std::ios::app);

        if (logFile.is_open()) {
            logFile << "[" << GetCurrentTimeStamp() << "] " << message << std::endl;
            std::cout << "Log written: " << message << std::endl;
            logFile.close();
        }
        else {
            std::cerr << "无法写入日志文件: " << fullPath << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "日志系统出错: " << e.what() << std::endl;
    }
}