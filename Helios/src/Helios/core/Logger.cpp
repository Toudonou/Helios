//
// Created by Toudonou on 21/07/2024.
//

#include "Helios/core/Logger.h"

namespace helios {
    void Logger::Init() {
        // TODO: Implement logger initialization (Add file logging)
    }

    void Logger::Log(const LogLevel level, const std::string &message, ...) {
        char outMessage[HELIOS_LOG_MAX_BUFFER_SIZE];
        std::ostringstream finalMessage;

        // Getting the current time
        const auto now = std::chrono::system_clock::now();
        // Convert to time_t to get calendar time
        const std::time_t now_time = std::chrono::system_clock::to_time_t(now);
        // Convert to tm structure for local time
        const std::tm now_tm = *std::localtime(&now_time);

        // Getting the message in the right format
        __builtin_va_list args;
        va_start(args, message);
        vsnprintf(outMessage, HELIOS_LOG_MAX_BUFFER_SIZE, message.c_str(), args);
        va_end(args);

        finalMessage << LogLevelColor(level) << "[" << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S") << "] "
                << LogLevelToString(level) << " " << outMessage;

        std::cout << finalMessage.str();
    }

    std::string Logger::LogLevelToString(const LogLevel level) {
        switch (level) {
            case LogLevel::DEBUG:
                return "DEBUG   ";
            case LogLevel::INFO:
                return "INFO    ";
            case LogLevel::WARNING:
                return "WARNING ";
            case LogLevel::ERROR:
                return "ERROR   ";
            case LogLevel::CRITICAL:
                return "CRITICAL";
            default:
                return "UNKNOWN ";
        }
    }

    std::string Logger::LogLevelColor(const LogLevel level) {
        switch (level) {
            case LogLevel::DEBUG:
                return "\033[0;34m"; // Blue
            case LogLevel::INFO:
                return "\033[0;32m"; // Green
            case LogLevel::WARNING:
                return "\033[0;33m"; // Yellow
            case LogLevel::ERROR:
                return "\033[0;31m"; // Red
            case LogLevel::CRITICAL:
                return "\033[0;31m"; // Red
            default:
                return "\033[0m"; // Reset
        }
    }
} // helios
