//
// Created by Toudonou on 30/07/2024.
//

#include "Helios/core/log.h"
#include "Helios/2D/Renderer2D.h"
#include "Helios/asset/AssetsManager.h"
#include "Helios/input/Input.h"

namespace helios {
    bool Renderer2D::s_init = false;
    GLuint Renderer2D::s_VAO = 0;
    GLuint Renderer2D::s_VBO = 0;
    GLuint Renderer2D::s_IBO = 0;
    GLuint Renderer2D::s_maxRenderable = 0;
    std::vector<Vertex> Renderer2D::s_vertices;
    Window *Renderer2D::s_window = nullptr;
    std::shared_ptr<Shader> Renderer2D::s_shader;

    constexpr GLubyte NUM_SPRITE_VERTICES = 4;
    constexpr GLubyte NUM_SPRITE_INDICES = 6;

    void Renderer2D::Init(const GLuint maxRenderable, Window &window) {
        if (s_init) {
            HELIOS_WARN("Trying to initialize the renderer twice");
            return;
        }

        s_maxRenderable = maxRenderable;
        s_window = &window;
        HELIOS_ASSERT_MSG(s_window, "The window should not be null");

        s_shader = std::make_shared<Shader>("../Helios/include/Helios/shader/basic.vert",
                                            "../Helios/include/Helios/shader/basic.frag");
        // Enable the shader
        s_shader->Enable();
        s_shader->SetUniformMat4("vw_matrix",
                                 Matrix4::Orthographic(0, s_window->GetSpecifications().width, 0,
                                                       s_window->GetSpecifications().height, -10, 10));
        const GLint textures[32] = {
            0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
            29, 30, 31
        };
        s_shader->SetUniform1iv("textures", textures, 32);

        // VBO
        glGenBuffers(1, &s_VBO);
        glBindBuffer(GL_ARRAY_BUFFER, s_VBO);
        glBufferData(GL_ARRAY_BUFFER, s_maxRenderable * NUM_SPRITE_VERTICES * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

        // VAO
        glGenVertexArrays(1, &s_VAO);
        glBindVertexArray(s_VAO);

        // Layout attribution
        glEnableVertexAttribArray(0); // position
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                              reinterpret_cast<void *>(offsetof(Vertex, Vertex::position)));

        glEnableVertexAttribArray(1); // uv
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                              reinterpret_cast<void *>(offsetof(Vertex, Vertex::uv)));

        glEnableVertexAttribArray(2); // color
        glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                              reinterpret_cast<void *>(offsetof(Vertex, Vertex::color)));

        glEnableVertexAttribArray(3); // texID
        glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                              reinterpret_cast<void *>(offsetof(Vertex, Vertex::texIndex)));

        // IBO
        std::vector<GLuint> indices;
        indices.resize(s_maxRenderable * NUM_SPRITE_INDICES);

        GLuint offset = {0};
        // 0    3
        // 1    2
        for (int i = 0; i < s_maxRenderable * NUM_SPRITE_INDICES; i += NUM_SPRITE_INDICES) {
            indices[i + 0] = 0 + offset;
            indices[i + 1] = 1 + offset;
            indices[i + 2] = 2 + offset;

            indices[i + 3] = 1 + offset;
            indices[i + 4] = 2 + offset;
            indices[i + 5] = 3 + offset;

            offset += NUM_SPRITE_VERTICES;
        }
        glGenBuffers(1, &s_IBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_IBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, s_maxRenderable * NUM_SPRITE_INDICES * sizeof(GLuint), indices.data(),
                     GL_DYNAMIC_DRAW);

        // Unbind everything
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        s_init = true;
        HELIOS_INFO("Renderer initialized successfully");
    }

    void Renderer2D::Shutdown() {
        if (!s_init) {
            HELIOS_WARN("Trying to shutdown a non initialized renderer");
            return;
        }

        glDeleteVertexArrays(1, &s_VAO);
        glDeleteBuffers(1, &s_VBO);
        glDeleteBuffers(1, &s_IBO);

        s_VAO = 0;
        s_VBO = 0;
        s_IBO = 0;
        s_maxRenderable = 0;
        s_shader->Disable();
        s_shader.reset();
        s_vertices.clear();

        s_init = false;
        HELIOS_INFO("Renderer shutdown successfully");
    }

    void Renderer2D::Begin() {
        if (!s_init) {
            HELIOS_WARN("Trying to begin drawing with a non initialized renderer");
            return;
        }

        // Important for having good image rendering
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glShadeModel(GL_SMOOTH);

        // Enable the depth test to be able z coordinate as z-index
        glEnable(GL_DEPTH_TEST);

        // Bind everything
        glBindVertexArray(s_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, s_VBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_IBO);

        // s_shader->SetUniform4f("light_pos", Vector4(Vector2(Input::GetMouseX(),
        //                                                     static_cast<real_t>(s_window->GetSpecifications().height) -
        //                                                     Input
        //                                                     ::GetMouseY()), 0.0f, 0.0f));

        for (const auto texture: AssetsManager::GetTextures()) {
            glActiveTexture(GL_TEXTURE0 + texture->GetTextureIndex());
            glBindTexture(GL_TEXTURE_2D, texture->GetTextureValue());
        }
    }

    void Renderer2D::End() {
        if (!s_init) {
            HELIOS_WARN("Trying to end drawing with a non initialized renderer");
            return;
        }

        // Unbind everything
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindTexture(GL_TEXTURE_2D, 0);

        // Disable the shader
        // s_shader->Disable();

        // Clear the vertices
        s_vertices.clear();
    }

    void Renderer2D::Submit(const std::vector<Vertex> &vertices) {
        // 0    2
        // 1    3
        // 0 1 2; 1 2 3
        if (!s_init) {
            HELIOS_WARN("Trying to submit vertices to a non initialized renderer");
            return;
        }

        if (s_vertices.size() > s_maxRenderable * NUM_SPRITE_VERTICES) {
            // TODO : This case should be handeled in a better way
            HELIOS_INFO("Maximum number of renderable reached : %d, flushing before continue", s_maxRenderable);
            Flush();
        }

        for (auto vertex: vertices) {
            vertex.position.y = static_cast<real_t>(s_window->GetSpecifications().height) - vertex.position.y;
            s_vertices.push_back(vertex);
        }
    }

    void Renderer2D::Flush() {
        if (!s_init) {
            HELIOS_WARN("Trying to flush with a non initialized renderer");
            return;
        }

        Begin();

        // Erase all the vertices with the new ones
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * s_vertices.size(), s_vertices.data());

        // Draw the elements : 1 quad = 2 triangles = 4 vertices = 6 indices => all quads = number of quad * 6 / 4
        // NUM_SPRITE_INDICES = 6 / NUM_SPRITE_VERTICES = 4 => 6 / 4 = 1.5
        constexpr GLfloat indicesFactor = static_cast<GLfloat>(NUM_SPRITE_INDICES) / NUM_SPRITE_VERTICES;
        glDrawElements(GL_TRIANGLES, s_vertices.size() * indicesFactor, GL_UNSIGNED_INT, nullptr);

        End();
    }

    // Primitives rendering
    void Renderer2D::DrawQuad(const real_t x, const real_t y, const real_t width, const real_t height,
                              const Color &color) {
        if (!s_init) {
            HELIOS_WARN("Trying to draw a quad with a non initialized renderer");
            return;
        }

        s_vertices.push_back(Vertex{
            .position = Vector3(x, static_cast<real_t>(s_window->GetSpecifications().height) - y, 0),
            .uv = Vector2::ZERO,
            .color = color,
            .texIndex = -1.0f
        }); // 0

        s_vertices.push_back(Vertex{
            .position = Vector3(x, static_cast<real_t>(s_window->GetSpecifications().height) - y - height, 0),
            .uv = Vector2::ZERO,
            .color = color,
            .texIndex = -1.0f
        }); // 1

        s_vertices.push_back(Vertex{
            .position = Vector3(x + width, static_cast<real_t>(s_window->GetSpecifications().height) - y, 0),
            .uv = Vector2::ZERO,
            .color = color,
            .texIndex = -1.0f
        }); // 2

        s_vertices.push_back(Vertex{
            .position = Vector3(x + width, static_cast<real_t>(s_window->GetSpecifications().height) - y - height, 0),
            .uv = Vector2::ZERO,
            .color = color,
            .texIndex = -1.0f
        }); // 3
    }
} // helios
