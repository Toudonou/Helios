//
// Created by Toudonou on 30/07/2024.
//

#ifndef COLOR_H
#define COLOR_H

#include "Helios/core/defines.h"

namespace helios {
    struct HELIOS_API Color {
        GLfloat r;
        GLfloat g;
        GLfloat b;
        GLfloat a;

        Color() : r(1), g(1), b(1), a(1) {
        }

        Color(const GLfloat r, const GLfloat g, const GLfloat b, const GLfloat a) : r(r), g(g), b(b), a(a) {
            this->r = std::clamp(r, 0.0f, 1.0f);
            this->g = std::clamp(g, 0.0f, 1.0f);
            this->b = std::clamp(b, 0.0f, 1.0f);
            this->a = std::clamp(a, 0.0f, 1.0f);
        }

        // Constants for common colors
        static const Color TRANSPARENT;
        static const Color WHITE;
        static const Color BLACK;
        static const Color RED;
        static const Color GREEN;
        static const Color BLUE;
        static const Color YELLOW;
        static const Color MAGENTA;
        static const Color CYAN;
        static const Color ORANGE;
        static const Color PURPLE;
        static const Color PINK;
        static const Color BROWN;
        static const Color GREY;
        static const Color LIGHT_GREY;
        static const Color DARK_GREY;
    };
}

#endif // COLOR_H
