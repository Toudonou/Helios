//
// Created by Toudonou on 29/07/2024.
//

#ifndef TRANSFORM2D_H
#define TRANSFORM2D_H

#include "Helios/maths/Matrix4.h"

namespace helios {
    struct HELIOS_API Transform2D {
        // To store the position of the object
        Vector2 position;

        // To store the scale of the object
        Vector2 scale;

        // To store the rotation of the object in degrees aroud the z-axis
        real_t rotation;

        Transform2D();

        Transform2D(const Vector2 &position, const Vector2 &scale, real_t rotation);

        [[nodiscard]] Matrix4 GetTransformMatrix() const;

        static Matrix4 Translate(const Vector2 &vector);

        static Matrix4 Scale(const Vector2 &vector);

        static Matrix4 Rotate(real_t angle);
    };
} // helios

#endif // TRANSFORM2D_H
