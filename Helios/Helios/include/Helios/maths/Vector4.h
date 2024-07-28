//
// Created by Toudonou on 28/07/2024.
//

#ifndef VECTOR4_H
#define VECTOR4_H

#include "Helios/core/defines.h"
#include "Helios/maths/Vector2.h"
#include "Helios/maths/Vector3.h"

namespace helios {
    struct Vector4 {
        real x, y, z, w;

        // Vector4 with x = y = z = w = 0
        Vector4();

        // Vector4 with x = y = z = w = value
        explicit Vector4(real value);

        // Vector4 with x = _x, y = _y, z = _z, w = _w
        Vector4(real _x, real _y, real _z, real _w);

        // Vector4 with x = other.x, y = other.y, z = _z, w = _w
        Vector4(const Vector2 &other, real _z, real _w);

        // Vector4 with x = other.x, y = other.y, z = other.z, w = _w
        Vector4(const Vector3 &other, real _w);

        // Copy constructor
        Vector4(const Vector4 &other);

        // Assignment constructor
        Vector4 &operator=(const Vector4 &other) = default;

        ~Vector4() = default;

        // Length of the Vector4
        [[nodiscard]] real length() const;

        // Square length of the Vector4
        [[nodiscard]] real squareLength() const;

        // Normalized Vector4
        [[nodiscard]] Vector4 normalized() const;

        Vector4 operator+(const Vector4 &other) const;

        void operator+=(const Vector4 &other);

        Vector4 operator-(const Vector4 &other) const;

        void operator-=(const Vector4 &other);

        Vector4 operator*(real scalar) const; // Scalar product Vector4 * 1

        void operator*=(real scalar); // Scalar product Vector4 * 1

        real operator*(const Vector4 &other) const; // Dot product

        __inline bool operator==(const Vector4 &other) const {
            return x == other.x && y == other.y && z == other.z && w == other.w;
        }

        __inline bool operator!=(const Vector4 &other) const { return !(*this == other); }

        [[nodiscard]] __inline std::string toString() const {
            return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ", " +
                   std::to_string(w) + ")";
        }
    };

    // Scalar product 1 * Vector3
    Vector4 operator*(real scalar, const Vector4 &other);
} // helios

#endif //VECTOR4_H
