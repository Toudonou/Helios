//
// Created by Toudonou on 29/07/2024.
//

#include "Helios/2D/Transform2D.h"

namespace helios {
    Transform2D::Transform2D() {
        position = Vector2::ZERO;
        scale = Vector2::ONE;
        rotation = 0;
    }

    Transform2D::Transform2D(const Vector2 &position, const Vector2 &scale, const real_t rotation) : position(position),
                                                                                                     scale(scale),
                                                                                                     rotation(rotation) {
    }

    Matrix4 Transform2D::GetTransformMatrix() const {
        return Scale(scale) * Rotate(rotation) * Translate(position);
    }

    Matrix4 Transform2D::Translate(const Vector2 &vector) {
        auto result = Matrix4::Identity();

        result(0, 3) = vector.x;
        result(1, 3) = vector.y;

        return result;
    }

    Matrix4 Transform2D::Scale(const Vector2 &vector) {
        auto result = Matrix4::Identity();

        result(0, 0) = vector.x;
        result(1, 1) = vector.y;

        return result;
    }

    Matrix4 Transform2D::Rotate(const real_t angle) {
        auto result = Matrix4::Identity();

        const real_t r = toRadian(angle);
        const real_t s = sinf(r);
        const real_t c = cosf(r);

        result(0, 0) = c;
        result(0, 1) = -s;

        result(1, 0) = s;
        result(1, 1) = c;

        return result;
    }
} // helios
