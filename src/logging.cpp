#include "logger/logging.hpp"

void Logger::log(LogType type, const std::string& message) {
    if (logFile.is_open()) {
        // Format: "YYYY-MM-DD HH:MM:SS[LOG_TYPE]: message".
        logFile << currentTime() << "[" << stringLogType(type) << "]" 
                << ": " << message << std::endl;
        
        // Immediate write to disk for crash safety.
        logFile.flush();
    }
}

std::string Logger::currentTime() {
    time_t now = time(0); // Current time.
    tm* tstruct = localtime(&now);
    char buf[80];

    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", tstruct);
    return std::string(buf); 
}

std::string Logger::stringLogType(LogType type) {
    switch (type) {
        case INFO:
            return "INFO";
        case ERROR:
            return "ERROR";
        case WARNING:
            return "WARNING";
        default:
            return "UNKNOWN";
    }
}
