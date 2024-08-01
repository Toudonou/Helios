//
// Created by Toudonou on 31/07/2024.
//

#ifndef TEXTURE_H
#define TEXTURE_H

#include "Helios/asset/Asset.h"
#include "Helios/maths/Size.h"

namespace helios {
    class HELIOS_API Texture {
    public:
        // TODO : Provide a way to delete the texture

        explicit Texture(GLuint textureIndex);

        ~Texture() = default;

        void LoadFromFile(const std::string &filePath);

        [[nodiscard]] const std::string &GetPath() const { return m_path; }

        [[nodiscard]] GLint GetTextureValue() const { return m_textureValue; }

        [[nodiscard]] GLuint GetTextureIndex() const { return m_textureIndex; }

        [[nodiscard]] GLfloat GetWidth() const { return m_size.w; }

        [[nodiscard]] GLfloat GetHeight() const { return m_size.h; }

    private:
        GLint m_textureValue;

        GLuint m_textureIndex;

        Size m_size;

        std::string m_path;
    };
} // helios

#endif //TEXTURE_H
