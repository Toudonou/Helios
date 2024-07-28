//
// Created by Toudonou on 28/07/2024.
//

#include "Helios/maths/Vector3.h"
#include "Helios/core/log.h"

namespace helios {
    Vector3::Vector3() : x(0), y(0), z(0) {
    }

    Vector3::Vector3(const real _x, const real _y, const real _z) : x(_x), y(_y), z(_z) {
    }

    Vector3::Vector3(const real value) : x(value), y(value), z(value) {
    }

    Vector3::Vector3(const Vector2 &other, const real _z) : x(other.x), y(other.y), z(_z) {
    }

    Vector3::Vector3(const Vector3 &other) {
        this->x = other.x;
        this->y = other.y;
        this->z = other.z;
    }

    real Vector3::length() const {
        return std::sqrt(squareLength());
    }

    real Vector3::squareLength() const {
        return x * x + y * y + z * z;
    }

    Vector3 Vector3::normalized() const {
        if (squareLength() == 0) {
            HELIOS_WARN("Trying to normalize a null Vector3");
            return {0, 0, 0};
        }
        return *this * (1 / length());
    }

    Vector3 Vector3::operator+(const Vector3 &other) const {
        return {x + other.x, y + other.y, z + other.z};
    }

    void Vector3::operator+=(const Vector3 &other) {
        x += other.x;
        y += other.y;
    }

    // Scalar product
    Vector3 Vector3::operator*(const real scalar) const {
        return {x * scalar, y * scalar, z * scalar};
    }

    // Scalar product 1 * Vector3
    Vector3 operator*(const real scalar, const Vector3 &other) {
        return other * scalar;
    }

    // Scalar product
    void Vector3::operator*=(const real scalar) {
        x *= scalar;
        y *= scalar;
    }

    // Dot product
    real Vector3::operator*(const Vector3 &other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    Vector3 Vector3::operator^(const Vector3 &other) const {
        auto result = Vector3();

        result.x = y * other.z - z * other.y;
        result.y = z * other.x - x * other.z;
        result.z = x * other.y - y * other.x;

        return result;
    }

    void Vector3::operator^=(const Vector3 &other) {
        auto result = Vector3();

        result.x = y * other.z - z * other.y;
        result.y = z * other.x - x * other.z;
        result.z = x * other.y - y * other.x;

        *this = result;
    }

    Vector3 Vector3::operator-(const Vector3 &other) const {
        return *this + -1 * other;
    }

    void Vector3::operator-=(const Vector3 &other) {
        *this += -1 * other;
    }
} // helios
