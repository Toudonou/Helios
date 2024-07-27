//
// Created by Toudonou on 21/07/2024.
//

#ifndef LOG_H
#define LOG_H

#include "Helios/core/defines.h"
#include "Helios/core/Logger.h"

#ifndef HELIOS_RELEASE


// Define logging macros with different severity levels
// Log an informational message about normal operation
#define HELIOS_INFO(message, ...)         Logger::Log(LogLevel::INFO, message + std::string(" [") + get_filename_from_path(__FILE__) + std::string(":") + __FUNCTION__ + std::string(":") + std::to_string(__LINE__) + std::string("]\n"), ##__VA_ARGS__); std::cout << "\033[0m";

// Log detailed diagnostic information for development and debugging
#define HELIOS_DEBUG(message, ...)        Logger::Log(LogLevel::DEBUG, message + std::string(" [") + get_filename_from_path(__FILE__) + std::string(":") + __FUNCTION__ + std::string(":") + std::to_string(__LINE__) + std::string("]\n"), ##__VA_ARGS__); std::cout << "\033[0m";

// Log warnings about potential issues or unusual situations
#define HELIOS_WARN(message, ...)         Logger::Log(LogLevel::WARNING, message + std::string(" [") + get_filename_from_path(__FILE__) + std::string(":") + __FUNCTION__ + std::string(":") + std::to_string(__LINE__) + std::string("]\n"), ##__VA_ARGS__); std::cout << "\033[0m";

// Log serious errors affecting functionality that need fixing
#define HELIOS_ERROR(message, ...)        Logger::Log(LogLevel::ERROR, message + std::string(" [") + get_filename_from_path(__FILE__) + std::string(":") + __FUNCTION__ + std::string(":") + std::to_string(__LINE__) + std::string("]\n"), ##__VA_ARGS__); std::cout << "\033[0m";

// Log critical issues requiring immediate attention to avoid application failure
#define HELIOS_CRITICAL(message, ...)     Logger::Log(LogLevel::CRITICAL, message, ##__VA_ARGS__);  std::cout << "\033[0m" << std::endl;

// Define assertion macros
namespace helios {
    inline std::string get_filename_from_path(const std::string &fullPath) {
        // Find the last occurrence of the path separator
#if defined(_WIN32)
        std::string::size_type pos = fullPath.find_last_of("\\/");
#else
        std::string::size_type pos = fullPath.find_last_of("/");
#endif

        // If a path separator was found, return the substring after the last separator
        if (pos != std::string::npos) {
            return fullPath.substr(pos + 1);
        }

        // If no separator was found, return the full path (should not happen)
        return fullPath;
    }

    // Report an assertion failure
    inline void report_assertion_failure(const char *expression, const std::string &message, const char *file,
                                         const int line,
                                         const char *function) {
        if (message.empty()) {
            HELIOS_CRITICAL("Assertion Failure: %s, [%s:%s:%d]", expression, get_filename_from_path(file).c_str(),
                            function,
                            line);
        } else {
            HELIOS_CRITICAL("Assertion Failure: %s, message : %s, [%s:%s:%d]", expression, message.c_str(),
                            get_filename_from_path(file).c_str(), function, line);
        }
    }
}

#if _WIN32
#define HELIOS_BREAK __debugbreak();
#elif __APPLE__
#define HELIOS_BREAK __builtin_debugtrap();
#else
#define  HELIOS_BREAK __builtin_trap();
#endif

#define HELIOS_ASSERT(expr) if(expr) {} else { report_assertion_failure(#expr, "", __FILE__, __LINE__, __FUNCTION__); HELIOS_BREAK}
#define HELIOS_ASSERT_MSG(expr, message) if(expr) {} else { report_assertion_failure(#expr, message, __FILE__, __LINE__, __FUNCTION__); HELIOS_BREAK}

#else
#define HELIOS_INFO(message, ...)
#define HELIOS_DEBUG(message, ...)
#define HELIOS_WARN(message, ...)
#define HELIOS_ERROR(message, ...)
#define HELIOS_CRITICAL(message, ...)
#define HELIOS_ASSERT(expr)
#define HELIOS_ASSERT_MSG(expr, message)
#endif
#endif //LOG_H
