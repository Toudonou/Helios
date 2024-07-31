//
// Created by Toudonou on 30/07/2024.
//

#ifndef SHADER_H
#define SHADER_H

#include "Helios/core/defines.h"
#include "Helios/maths/maths.h"

namespace helios {
    class HELIOS_API Shader {
    public:
        Shader(std::string vertPath, std::string fragPath);

        ~Shader();

        void SetUniform1i(const std::string &name, int value) const;

        void SetUniform1iv(const std::string &name, const int *value, int count) const;

        void SetUniform1f(const std::string &name, float value) const;

        void SetUniform2f(const std::string &name, const Vector2 &vector) const;

        void SetUniform3f(const std::string &name, const Vector3 &vector) const;

        void SetUniform4f(const std::string &name, const Vector4 &vector) const;

        void SetUniformMat4(const std::string &name, const Matrix4 &matrix) const;

        void Enable() const;

        void Disable() const;

    private:
        GLuint m_ShaderID;
        std::string m_VertPath, m_FragPath;

        [[nodiscard]] GLuint load() const;

        [[nodiscard]] GLint getUniformLocation(const std::string &name) const;
    };
} // helios

#endif //SHADER_H
