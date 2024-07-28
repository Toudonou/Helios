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

// thrid-party libraries
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Helios defines
#define HELIOS_EXPORT
// #define HELIOS_RELEASE
#define HELIOS_LOG_MAX_BUFFER_SIZE (64 * 1024) // Logger buffer size : 64kb
#define HELIOS_MAX_KEYS             1024
#define HELIOS_MAX_MOUSE_BUTTONS    32

typedef float real;

#ifdef _WIN32
#ifdef HELIOS_EXPORT
#define HELIOS_API __declspec(dllexport)
#else
#define HELIOS_API __declspec(dllimport)
#endif
#endif

#endif //DEFINES_H
