//
// Created by Toudonou on 21/07/2024.
//

#ifndef LOGGER_H
#define LOGGER_H

#include "Helios/core/defines.h"

namespace helios {
    // Enum to represent log levels
    enum class LogLevel {
        DEBUG,
        INFO,
        WARNING,
        ERROR,
        CRITICAL
    };

    // Logger class
    class HELIOS_API Logger {
    public:
        // Initializes the logger
        static void Init(const std::string &logFile);

        // Logs a message with a given log level
        static void Log(LogLevel level, const std::string &message, ...);

        // Shutdown the logger
        static void Shutdown();

    private:
        // To store temporary log messages
        static std::ostringstream tempBuffer;

        // Logger file
        static std::ofstream s_loggingFile;

        // Converts a log level to a string
        static std::string LogLevelToString(LogLevel level);

        // Activates the color for a log level
        static std::string LogLevelColor(LogLevel level);

        Logger() = default;

        ~Logger() = default;
    };
} // helios

#endif //LOGGER_H
