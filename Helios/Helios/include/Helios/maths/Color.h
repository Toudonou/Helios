//
// Created by Toudonou on 30/07/2024.
//

#ifndef COLOR_H
#define COLOR_H

#include "Helios/core/defines.h"

namespace helios {
    struct HELIOS_API Color {
        GLuint r;
        GLuint g;
        GLuint b;
        GLuint a;

        Color(const GLuint r, const GLuint g, const GLuint b, const GLuint a) : r(r), g(g), b(b), a(a) {
        }
    };
}

#endif // COLOR_H
