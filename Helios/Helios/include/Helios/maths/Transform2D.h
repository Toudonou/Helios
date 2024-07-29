//
// Created by Toudonou on 29/07/2024.
//

#ifndef TRANSFORM2D_H
#define TRANSFORM2D_H

#include "Helios/maths/Matrix4.h"

namespace helios {
    struct Transform2D {
        // To store the position of the object
        Vector2 position;

        // To store the scale of the object
        Vector2 scale;

        // To store the rotation of the object in degrees aroud the z-axis
        real rotation;

        Transform2D();

        [[nodiscard]] Matrix4 GetTransformMatrix() const;

        static Matrix4 Translate(const Vector2 &vector);

        static Matrix4 Scale(const Vector2 &vector);

        static Matrix4 Rotate(real angle);
    };
} // helios

#endif // TRANSFORM2D_H
