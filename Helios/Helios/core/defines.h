//
// Created by Toudonou on 21/07/2024.
//

#ifndef DEFINES_H
#define DEFINES_H

// std libraries
#include <iostream>
#include <cstring>
#include <cstdarg>
#include <chrono>
#include <fstream>
#include <cmath>
#include <unordered_set>

// thrid-party libraries
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Helios defines
#define HELIOS_EXPORT
// #define HELIOS_RELEASE
#define HELIOS_LOG_MAX_BUFFER_SIZE (64 * 1024) // Logger buffer size : 64kb
#define HELIOS_MAX_KEYS             1024
#define HELIOS_MAX_MOUSE_BUTTONS    32

// Helios types
typedef float real_t;

namespace helios {
    inline real_t toRadian(const real_t degree) {
        constexpr real_t pi_over_180 = M_PI / 180;
        return degree * pi_over_180;
    }

    inline real_t hsin(const real_t angle) {
        return sinf(angle);
    }

    inline real_t hcos(const real_t angle) {
        return cosf(angle);
    }
}

#ifdef _WIN32
#ifdef HELIOS_EXPORT
#define HELIOS_API __declspec(dllexport)
#else
#define HELIOS_API __declspec(dllimport)
#endif
#endif

#endif //DEFINES_H
