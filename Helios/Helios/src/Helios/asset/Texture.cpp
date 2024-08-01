//
// Created by Toudonou on 31/07/2024.
//

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h> // Used only here

#include "Helios/asset/Texture.h"
#include "Helios/core/log.h"

namespace helios {
    Texture::Texture(const GLuint textureIndex) {
        m_textureValue = 0;
        m_textureIndex = textureIndex;
    }

    void Texture::LoadFromFile(const std::string &filePath) {
        GLuint tex;
        glGenTextures(1, &tex);
        glBindTexture(GL_TEXTURE_2D, tex);

        stbi_set_flip_vertically_on_load(true);
        int temp_width, temp_height, channels;
        unsigned char *image = stbi_load(filePath.c_str(), &temp_width, &temp_height, &channels, 0);
        // TODO :  Make sure the image is not null

        m_size.w = static_cast<GLfloat>(temp_width);
        m_size.h = static_cast<GLfloat>(temp_height);

        GLenum format = 0;
        if (channels == 1)
            format = GL_RED;
        else if (channels == 3)
            format = GL_RGB;
        else if (channels == 4)
            format = GL_RGBA;

        glTexImage2D(GL_TEXTURE_2D, 0, static_cast<GLint>(format), temp_width, temp_height, 0, format, GL_UNSIGNED_BYTE,
                     image);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glGenerateMipmap(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, 0);
        stbi_image_free(image);

        m_textureValue = static_cast<GLint>(tex);
        m_path = filePath;
    }
} // helios
