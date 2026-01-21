#pragma once

#include <iostream>
#include <ctime>
#include <fstream>
#include <string>

enum LogType {
    INFO,
    ERROR,
    WARNING
};

class Logger {
public:
    Logger(const std::string& filename) {
        logFile.open(filename, std::ios::app);
        if (!logFile.is_open()) {
            std::cerr << "Error: can't open log file." << std::endl;
        }
    }

    ~Logger() {
        logFile.close();
    }

    void log(LogType type, const std::string& message);
    std::string currentTime();
    std::string stringLogType(LogType type);

private:
    std::ofstream logFile;

};
