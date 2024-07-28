//
// Created by Toudonou on 28/07/2024.
//

#include "Helios/maths/Vector2.h"

#include "Helios/core/log.h"

namespace helios {
    Vector2::Vector2() : x(0), y(0) {
    }

    Vector2::Vector2(const real _x, const real _y) : x(_x), y(_y) {
    }

    Vector2::Vector2(const real value) : x(value), y(value) {
    }

    Vector2::Vector2(const Vector2 &other) {
        this->x = other.x;
        this->y = other.y;
    }

    real Vector2::length() const {
        return std::sqrt(squareLength());
    }

    real Vector2::squareLength() const {
        return x * x + y * y;
    }

    Vector2 Vector2::normalized() const {
        if (squareLength() == 0) {
            HELIOS_WARN("Trying to normalize a null Vector2");
            return {0, 0};
        }
        return *this * (1 / length());
    }

    Vector2 Vector2::operator+(const Vector2 &other) const {
        return {x + other.x, y + other.y};
    }

    void Vector2::operator+=(const Vector2 &other) {
        x += other.x;
        y += other.y;
    }

    // Scalar product
    Vector2 Vector2::operator*(const real scalar) const {
        return {x * scalar, y * scalar};
    }

    // Scalar product
    Vector2 operator*(const real scalar, const Vector2 &other) {
        return other * scalar;
    }

    // Scalar product
    void Vector2::operator*=(const real scalar) {
        x *= scalar;
        y *= scalar;
    }

    // Dot product
    real Vector2::operator*(const Vector2 &other) const {
        return x * other.x + y * other.y;
    }

    Vector2 Vector2::operator-(const Vector2 &other) const {
        return *this + -1 * other;
    }

    void Vector2::operator-=(const Vector2 &other) {
        *this += -1 * other;
    }
} // helios
