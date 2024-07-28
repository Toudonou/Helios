//
// Created by Toudonou on 28/07/2024.
//

#ifndef MATRIX4_H
#define MATRIX4_H

#include "Helios/core/defines.h"
#include "Helios/maths/Vector4.h"

namespace helios {
    struct Matrix4 {
        real elements[4 * 4]{}; // Will be arrange like opengl matrix : column major

        // Matrix4 with all elements set to 0
        Matrix4();

        // Constructor with diagonal value
        explicit Matrix4(real diagonal);

        // Constructor with array of 16 elements arranged in column major
        explicit Matrix4(real elements[4 * 4]);

        // Constructor with 4 Vector4
        Matrix4(const Vector4 &column0, const Vector4 &column1, const Vector4 &column2, const Vector4 &column3);

        // Copy constructor
        Matrix4(const Matrix4 &other);

        // Assignment constructor
        Matrix4 &operator=(const Matrix4 &other);

        // Identity Matrix4
        static Matrix4 Identity();

        // Orthographic Matrix4
        static Matrix4 Orthographic(real left, real right, real bottom, real top, real near, real far);

        // Perspective Matrix4
        static Matrix4 Perspective(real fov, real aspectRatio, real near, real far);

        // Transpose Matrix4
        Matrix4 Transpose();

        real &operator()(int i, int j);

        const real &operator()(int i, int j) const;

        bool operator==(const Matrix4 &other) const;

        // Addition and Sum
        Matrix4 operator+(const Matrix4 &other) const;

        void operator+=(const Matrix4 &other);

        Matrix4 operator-(const Matrix4 &other) const;

        void operator-=(const Matrix4 &other);

        // Matrix product
        Matrix4 operator*(const Matrix4 &other) const;

        // Matrix product
        void operator*=(const Matrix4 &other);

        // Scalar product
        Matrix4 operator*(real scalar) const;

        // Scalar product
        void operator*=(real scalar);

        // Matrix times Vector4
        Vector4 operator*(const Vector4 &vector) const;
    };

    // Scalar product 1 * Matrix4
    Matrix4 operator*(real scalar, const Matrix4 &other);
} // helios

#endif // MATRIX4_H
