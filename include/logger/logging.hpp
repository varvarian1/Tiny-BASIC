#pragma once

#include <iostream>
#include <ctime>
#include <fstream>
#include <string>

#include "lexer/lexer.hpp"

enum LogType {
    INFO,
    ERROR,
    WARNING,
    DEBUG
};

enum Mode {
    WRITE,
    REWRITE
};

class Logger {
public:
    Logger(const std::string& filename, Mode mode) {
        if (mode == WRITE) {
            logFile.open(filename, std::ios::app);
        } 
        else if (mode == REWRITE) {
            logFile.open(filename, std::ios::out);
        }

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

    void lexerLog(std::vector<Token>& tokens);

private:
    std::ofstream logFile;

};
