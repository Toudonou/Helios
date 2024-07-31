//
// Created by Toudonou on 30/07/2024.
//

#include "Helios/core/log.h"
#include "Helios/shader/Shader.h"
#include "Helios/utils/FileUtils.h"

namespace helios {
    Shader::Shader(std::string vertPath, std::string fragPath)
        : m_VertPath(std::move(vertPath)), m_FragPath(std::move(fragPath)) {
        m_ShaderID = load();
    }

    Shader::~Shader() {
        m_ShaderID = -1;
        glDeleteProgram(m_ShaderID);
    }

    void Shader::SetUniform1i(const std::string &name, const int value) const {
        glUniform1i(getUniformLocation(name), value);
    }

    void Shader::SetUniform1iv(const std::string &name, const int *value, const int count) const {
        glUniform1iv(getUniformLocation(name), count, value);
    }

    void Shader::SetUniform1f(const std::string &name, const float value) const {
        glUniform1f(getUniformLocation(name), value);
    }

    void Shader::SetUniform2f(const std::string &name, const Vector2 &vector) const {
        glUniform2f(getUniformLocation(name), static_cast<GLfloat>(vector.x), static_cast<GLfloat>(vector.y));
    }

    void Shader::SetUniform3f(const std::string &name, const Vector3 &vector) const {
        glUniform3f(getUniformLocation(name), static_cast<GLfloat>(vector.x), static_cast<GLfloat>(vector.y),
                    static_cast<GLfloat>(vector.z));
    }

    void Shader::SetUniform4f(const std::string &name, const Vector4 &vector) const {
        glUniform4f(getUniformLocation(name), static_cast<GLfloat>(vector.x), static_cast<GLfloat>(vector.y),
                    static_cast<GLfloat>(vector.z), static_cast<GLfloat>(vector.w));
    }

    void Shader::SetUniformMat4(const std::string &name, const Matrix4 &matrix) const {
        glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, matrix.elements);
    }

    void Shader::Enable() const {
        glUseProgram(m_ShaderID);
    }

    void Shader::Disable() const {
        glUseProgram(0);
    }

    GLuint Shader::load() const {
        const GLuint program = glCreateProgram();
        const GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
        const GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
        GLint result;
        GLchar errorLog[1024];

        const std::string vertSourceStr = FileUtils::ReadFile(m_VertPath);
        const std::string fragSourceStr = FileUtils::ReadFile(m_FragPath);

        if (vertSourceStr.empty()) {
            HELIOS_ERROR("Vertex shader source is empty.");
            return 0;
        }

        if (fragSourceStr.empty()) {
            HELIOS_ERROR("Fragment shader source is empty.");
            return 0;
        }

        const char *vertSource = vertSourceStr.c_str();
        const char *fragSource = fragSourceStr.c_str();

        // Vertex Shader
        glShaderSource(vertex, 1, &vertSource, nullptr);
        glCompileShader(vertex);
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE) {
            glGetShaderInfoLog(vertex, sizeof(errorLog), nullptr, errorLog);
            HELIOS_ERROR("Error during vertex shader compilation: %s", errorLog);
            glDeleteShader(vertex);
            return 0;
        }

        // Fragment Shader
        glShaderSource(fragment, 1, &fragSource, nullptr);
        glCompileShader(fragment);
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE) {
            glGetShaderInfoLog(fragment, sizeof(errorLog), nullptr, errorLog);
            HELIOS_ERROR("Error during fragment shader compilation: %s", errorLog);
            glDeleteShader(fragment);
            return 0;
        }

        // Link Shaders
        glAttachShader(program, vertex);
        glAttachShader(program, fragment);
        glLinkProgram(program);
        glGetProgramiv(program, GL_LINK_STATUS, &result);
        if (result == GL_FALSE) {
            glGetProgramInfoLog(program, sizeof(errorLog), nullptr, errorLog);
            HELIOS_ERROR("Error during shader program linking: %s", errorLog);
            glDeleteProgram(program);
            return 0;
        }

        // Validate Program
        glValidateProgram(program);
        glGetProgramiv(program, GL_VALIDATE_STATUS, &result);
        if (result == GL_FALSE) {
            glGetProgramInfoLog(program, sizeof(errorLog), nullptr, errorLog);
            HELIOS_ERROR("Error during shader program validation: %s", errorLog);
            glDeleteProgram(program);
            return 0;
        }

        glDeleteShader(vertex);
        glDeleteShader(fragment);

        return program;
    }

    GLint Shader::getUniformLocation(const std::string &name) const {
        return glGetUniformLocation(m_ShaderID, name.c_str());
    }
} // helios
