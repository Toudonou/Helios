//
// Created by Toudonou on 28/07/2024.
//

#include "Helios/maths/Vector4.h"

#include "Helios/core/log.h"

namespace helios {
    Vector4::Vector4() : x(0), y(0), z(0), w(0) {
    }

    Vector4::Vector4(const real_t value) : x(value), y(value), z(value), w(value) {
    }

    Vector4::Vector4(const real_t _x, const real_t _y, const real_t _z, const real_t _w) : x(_x), y(_y), z(_z), w(_w) {
    }

    Vector4::Vector4(const Vector2 &other, const real_t _z, const real_t _w) : x(other.x), y(other.y), z(_z), w(_w) {
    }

    Vector4::Vector4(const Vector3 &other, const real_t _w) : x(other.x), y(other.y), z(other.z), w(_w) {
    }

    Vector4::Vector4(const Vector4 &other) {
        this->x = other.x;
        this->y = other.y;
        this->z = other.z;
        this->w = other.w;
    }

    real_t Vector4::Length() const {
        return std::sqrt(SquareLength());
    }

    real_t Vector4::SquareLength() const {
        return x * x + y * y + z * z + w * w;
    }

    Vector4 Vector4::Normalized() const {
        if (SquareLength() == 0) {
            HELIOS_WARN("Trying to normalize a null Vector4");
            return {0, 0, 0, 0};
        }
        return *this * (1 / Length());
    }

    Vector4 Vector4::operator+(const Vector4 &other) const {
        return {x + other.x, y + other.y, z + other.z, w + other.w};
    }

    void Vector4::operator+=(const Vector4 &other) {
        x += other.x;
        y += other.y;
    }

    // Scalar product
    Vector4 Vector4::operator*(const real_t scalar) const {
        return {x * scalar, y * scalar, z * scalar, w * scalar};
    }

    // Scalar product 1 * Vector4
    Vector4 operator*(const real_t scalar, const Vector4 &other) {
        return other * scalar;
    }

    // Scalar product
    void Vector4::operator*=(const real_t scalar) {
        x *= scalar;
        y *= scalar;
    }

    // Dot product
    real_t Vector4::operator*(const Vector4 &other) const {
        return x * other.x + y * other.y;
    }

    Vector4 Vector4::operator-(const Vector4 &other) const {
        return *this + -1 * other;
    }

    void Vector4::operator-=(const Vector4 &other) {
        *this += -1 * other;
    }
} // helios
