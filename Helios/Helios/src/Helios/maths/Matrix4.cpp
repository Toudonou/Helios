//
// Created by Toudonou on 28/07/2024.
//

#include "Helios/maths/Matrix4.h"
#include "Helios/core/log.h"

namespace helios {
    Matrix4::Matrix4() {
        memset(elements, 0, 4 * 4 * sizeof(real_t));
    }

    Matrix4::Matrix4(const real_t diagonal) {
        memset(elements, 0, 4 * 4 * sizeof(real_t));
        elements[0 + 4 * 0] = diagonal;
        elements[1 + 4 * 1] = diagonal;
        elements[2 + 4 * 2] = diagonal;
        elements[3 + 4 * 3] = diagonal;
    }

    Matrix4::Matrix4(real_t elements[16]) {
        memset(elements, 0, 4 * 4 * sizeof(real_t));
        for (int i = 0; i < 16; i++) {
            this->elements[i] = elements[i];
        }
    }

    Matrix4::Matrix4(const Vector4 &column0, const Vector4 &column1, const Vector4 &column2, const Vector4 &column3) {
        (*this)(0, 0) = column0.x;
        (*this)(1, 0) = column0.y;
        (*this)(2, 0) = column0.z;
        (*this)(3, 0) = column0.w;

        (*this)(0, 1) = column1.x;
        (*this)(1, 1) = column1.y;
        (*this)(2, 1) = column1.z;
        (*this)(3, 1) = column1.w;

        (*this)(0, 2) = column2.x;
        (*this)(1, 2) = column2.y;
        (*this)(2, 2) = column2.z;
        (*this)(3, 2) = column2.w;

        (*this)(0, 3) = column3.x;
        (*this)(1, 3) = column3.y;
        (*this)(2, 3) = column3.z;
        (*this)(3, 3) = column3.w;
    }

    Matrix4::Matrix4(const Matrix4 &other) {
        memcpy(elements, other.elements, 4 * 4 * sizeof(real_t));
    }

    Matrix4 &Matrix4::operator=(const Matrix4 &other) {
        memcpy(elements, other.elements, 4 * 4 * sizeof(real_t));
        return *this;
    }

    Matrix4 Matrix4::Identity() {
        return Matrix4(1);
    }

    Matrix4 Matrix4::Orthographic(const real_t left, const real_t right, const real_t bottom, const real_t top, const real_t near,
                                  const real_t far) {
        auto result = Identity();

        result(0, 0) = 2 / (right - left);
        result(1, 1) = 2 / (top - bottom);
        result(2, 2) = 2 / (near - far);

        result(0, 3) = -(right + left) / (right - left);
        result(1, 3) = -(top + bottom) / (top - bottom);
        result(2, 3) = -(far + near) / (far - near);

        return result;
    }

    Matrix4 Matrix4::Perspective(const real_t fov, const real_t aspectRatio, const real_t near, const real_t far) {
        auto result = Identity();

        const real_t q = 1.0f / tan(toRadian(0.5f * fov));
        const real_t a = q / aspectRatio;
        const real_t b = (near + far) / (near - far);
        const real_t c = 2 * near * far / (near - far);

        result(0, 0) = a;
        result(1, 1) = q;
        result(2, 2) = b;
        result(3, 3) = -1;
        result(3, 4) = c;

        return result;
    }

    Matrix4 Matrix4::Transpose() {
        auto result = Matrix4();
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                result(i, j) = (*this)(j, i);
            }
        }
        return result;
    }

    real_t &Matrix4::operator()(const int i, const int j) {
        HELIOS_ASSERT_MSG(i >= 0 && i < 4, " i is out of bounds");
        HELIOS_ASSERT_MSG(j >= 0 && j < 4, " j is out of bounds");
        return elements[i + 4 * j];
    }

    const real_t &Matrix4::operator()(const int i, const int j) const {
        HELIOS_ASSERT_MSG(i >= 0 && i < 4, " i is out of bounds");
        HELIOS_ASSERT_MSG(j >= 0 && j < 4, " j is out of bounds");
        return elements[i + 4 * j];
    }

    bool Matrix4::operator==(const Matrix4 &other) const {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if ((*this)(i, j) != other(i, j)) {
                    return false;
                }
            }
        }
        return true;
    }

    Matrix4 Matrix4::operator+(const Matrix4 &other) const {
        auto result = Matrix4();
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                result(i, j) = (*this)(i, j) + other(i, j);
            }
        }
        return result;
    }

    void Matrix4::operator+=(const Matrix4 &other) {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                (*this)(i, j) += other(i, j);
            }
        }
    }

    Matrix4 Matrix4::operator-(const Matrix4 &other) const {
        return *this + -1 * other;
    }

    void Matrix4::operator-=(const Matrix4 &other) {
        *this += -1 * other;
    }

    Matrix4 Matrix4::operator*(const Matrix4 &other) const {
        auto result = Matrix4();
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                for (int k = 0; k < 4; ++k) {
                    result(i, j) += (*this)(i, k) * other(k, j);
                }
            }
        }
        return result;
    }

    void Matrix4::operator*=(const Matrix4 &other) {
        auto result = Matrix4();
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                for (int k = 0; k < 4; ++k) {
                    result(i, j) += (*this)(i, k) * other(k, j);
                }
            }
            // Updating the current matrix object
            for (int j = 0; j < 4; j++) {
                (*this)(i, j) = result(i, j);
            }
        }
    }

    Matrix4 Matrix4::operator*(const real_t scalar) const {
        auto result = Matrix4();
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                result(i, j) = (*this)(i, j) * scalar;
            }
        }
        return result;
    }

    void Matrix4::operator*=(const real_t scalar) {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                (*this)(i, j) *= scalar;
            }
        }
    }

    Vector4 Matrix4::operator*(const Vector4 &vector) const {
        auto result = Vector4();
        for (int i = 0; i < 4; ++i) {
            result.x += (*this)(i, 0) * vector.x;
            result.y += (*this)(i, 1) * vector.y;
            result.z += (*this)(i, 2) * vector.z;
            result.w += (*this)(i, 3) * vector.w;
        }
        return result;
    }

    Matrix4 operator*(const real_t scalar, const Matrix4 &other) {
        return other * scalar;
    }
} // helios
