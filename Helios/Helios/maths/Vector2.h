//
// Created by Toudonou on 28/07/2024.
//

#ifndef VECTOR2_H
#define VECTOR2_H

#include "Helios/core/defines.h"

namespace helios {
    struct HELIOS_API Vector2 {
        real_t x, y;

        // Constants
        static const Vector2 ZERO;
        static const Vector2 ONE;
        static const Vector2 UP;
        static const Vector2 DOWN;
        static const Vector2 RIGHT;
        static const Vector2 LEFT;

        // Vector2 with x = y = 0
        Vector2();

        // Vector2 with x = y = value
        explicit Vector2(real_t value);

        // Vector2 with x = _x and y = _y
        Vector2(real_t _x, real_t _y);

        // Copy constructor
        Vector2(const Vector2 &other);

        // Assignment constructor
        Vector2 &operator=(const Vector2 &other) = default;

        ~Vector2() = default;

        // Length of the Vector2
        [[nodiscard]] real_t Length() const;

        // Square length of the Vector2
        [[nodiscard]] real_t SquareLength() const;

        // Normalized Vector2
        [[nodiscard]] Vector2 Normalized() const;

        Vector2 operator+(const Vector2 &other) const;

        void operator+=(const Vector2 &other);

        Vector2 operator-(const Vector2 &other) const;

        void operator-=(const Vector2 &other);

        Vector2 operator*(real_t scalar) const; // Scalar product Vector2 * 1

        void operator*=(real_t scalar); // Scalar product Vector2 * 1

        real_t operator*(const Vector2 &other) const; // Dot product

        __inline bool operator==(const Vector2 &other) const { return x == other.x && y == other.y; }

        __inline bool operator!=(const Vector2 &other) const { return !(*this == other); }

        // toString method
        [[nodiscard]] __inline std::string toString() const {
            return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
        }
    };

    // Scalar product 1 * Vector2
    Vector2 operator*(real_t scalar, const Vector2 &other);
} // helios

#endif // VECTOR2_H
