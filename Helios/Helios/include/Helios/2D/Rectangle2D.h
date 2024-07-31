//
// Created by Toudonou on 31/07/2024.
//

#ifndef RECTANGLE2D_H
#define RECTANGLE2D_H

#include "Helios/2D/Transform2D.h"
#include "Helios/core/defines.h"
#include "Helios/maths/Color.h"
#include "Helios/maths/Size.h"

namespace helios {
    struct HELIOS_API Rectangle2D {
        Transform2D transform;
        Size size{};
        Color color;
        real_t zIndex;

        Rectangle2D(const real_t x, const real_t y, const real_t width, const real_t height, const Color &color, const real_t zIndex = 0.0f) {
            transform.position.x = x;
            transform.position.y = y;
            size = Size(width, height);
            this->color = color;
            this->zIndex = zIndex;
        }
    };
} // helios

#endif //RECTANGLE2D_H
