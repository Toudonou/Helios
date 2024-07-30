//
// Created by Toudonou on 28/07/2024.
//

#ifndef VECTOR3_H
#define VECTOR3_H

#include "Helios/core/defines.h"
#include "Helios/maths/Vector2.h"

namespace helios {
    struct HELIOS_API Vector3 {
        real_t x, y, z;

        // Vector3 with x = y = z = 0
        Vector3();

        // Vector3 with x = y = z = value
        explicit Vector3(real_t value);

        // Vector3 with x = _x, y = _y, z = _z
        Vector3(real_t _x, real_t _y, real_t _z);

        // Vector3 with x = other.x, y = other.y, z = _z
        Vector3(const Vector2 &other, real_t _z);

        // Copy constructor
        Vector3(const Vector3 &other);

        // Assignment constructor
        Vector3 &operator=(const Vector3 &other) = default;

        ~Vector3() = default;

        // Length of the Vector3
        [[nodiscard]] real_t length() const;

        // Square length of the Vector3
        [[nodiscard]] real_t squareLength() const;

        // Normalized Vector3
        [[nodiscard]] Vector3 normalized() const;

        Vector3 operator+(const Vector3 &other) const;

        void operator+=(const Vector3 &other);

        Vector3 operator-(const Vector3 &other) const;

        void operator-=(const Vector3 &other);

        Vector3 operator*(real_t scalar) const; // Scalar product

        void operator*=(real_t scalar); // Scalar product

        real_t operator*(const Vector3 &other) const; // Dot product

        Vector3 operator^(const Vector3 &other) const; // Cross product

        void operator^=(const Vector3 &other); // Cross product

        __inline bool operator==(const Vector3 &other) const { return x == other.x && y == other.y && z == other.z; }

        __inline bool operator!=(const Vector3 &other) const { return !(*this == other); }

        // toString method
        [[nodiscard]] __inline std::string toString() const {
            return "(" + std::to_string(x) + ", " + std::to_string(y) + std::to_string(z) + ")";
        }
    };

    // Scalar product 1 * Vector3
    Vector3 operator*(real_t scalar, const Vector3 &other);
} // helios

#endif // VECTOR3_H
