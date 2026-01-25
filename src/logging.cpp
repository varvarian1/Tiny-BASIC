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

void Logger::lexerLog(std::vector<Token>& tokens) {
    for (const auto& token : tokens) {
        logFile << "Token: ";
        switch (token.type) {
            case Token::Type::Number:
                logFile << "Number      ";
                break;
            case Token::Type::String:
                logFile << "String      ";
                break;
            case Token::Type::LeftParenthesis:
                logFile << "LeftParenthesis";
                break;
            case Token::Type::RightParenthesis:
                logFile << "RightParenthesis";
                break;
            case Token::Type::Semicolon:
                logFile << "Semicolon    ";
                break;
            case Token::Type::Comma:
                logFile << "Comma        ";
                break;
            case Token::Type::Plus:
                logFile << "Plus        ";
                break;
            case Token::Type::Minus:
                logFile << "Minus       ";
                break;
            case Token::Type::Mult:
                logFile << "Mult        ";
                break;
            case Token::Type::Div:
                logFile << "Div         ";
                break;
            case Token::Type::Equal:
                logFile << "Equal       ";
                break;
            case Token::Type::Less:
                logFile << "Less        ";
                break;
            case Token::Type::Greater:
                logFile << "Greater     ";
                break;
            case Token::Type::Operator:
                logFile << "Operator    ";
                break;
            case Token::Type::Identifier:
                logFile << "Identifier  ";
                break;
            case Token::Type::Keyword:
                logFile << "Keyword     ";
                break;
            case Token::Type::Unknown:
                logFile << "Unknown     ";
                break;
        }
        logFile << "\t\t -> '" << token.text << "'";
        logFile << std::endl;
    }
}
