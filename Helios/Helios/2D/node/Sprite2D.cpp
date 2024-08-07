//
// Created by Toudonou on 31/07/2024.
//

#include "Helios/2D/node/Sprite2D.h"
#include "Helios/asset/AssetsManager.h"

namespace helios {
    Sprite2D::Sprite2D() {
        m_texture = nullptr;
        s_vertices.reserve(4);
        m_isVisible = true;
        m_flipX = false;
        m_flipY = false;
        m_isCentered = true;
    }

    void Sprite2D::Start() {
    }

    void Sprite2D::Update(float deltaTime) {
        if (!m_isVisible) return;

        s_vertices.clear();
        // 0    2
        // 1    3
        // 0 1 2; 1 2 3
        s_vertices.push_back(Vertex{
            .position = Vector3(Vector2::ZERO, zIndex),
            .uv = Vector2(m_flipX ? 1.0f : 0.0f, m_flipY ? 0.0f : 1.0f),
            .color = color,
            .texIndex = m_texture != nullptr ? static_cast<real_t>(m_texture->GetTextureIndex()) : -1.0f
        }); // 0

        s_vertices.push_back(Vertex{
            .position = Vector3(Vector2::ZERO, zIndex),
            .uv = Vector2(m_flipX ? 1.0f : 0.0f, m_flipY ? 1.0f : 0.0f),
            .color = color,
            .texIndex = m_texture != nullptr ? static_cast<real_t>(m_texture->GetTextureIndex()) : -1.0f
        }); // 1

        s_vertices.push_back(Vertex{
            .position = Vector3(Vector2::ZERO, zIndex),
            .uv = Vector2(m_flipX ? 0.0f : 1.0f, m_flipY ? 0.0f : 1.0f),
            .color = color,
            .texIndex = m_texture != nullptr ? static_cast<real_t>(m_texture->GetTextureIndex()) : -1.0f
        }); // 2

        s_vertices.push_back(Vertex{
            .position = Vector3(Vector2::ZERO, zIndex),
            .uv = Vector2(m_flipX ? 0.0f : 1.0f, m_flipY ? 1.0f : 0.0f),
            .color = color,
            .texIndex = m_texture != nullptr ? static_cast<real_t>(m_texture->GetTextureIndex()) : -1.0f
        }); // 3


        // Applying transformations
        ApplyScale();
        ApplyRotation();

        // To avoid weird effects on the texture
        for (auto &[position, uv, color, texIndex]: s_vertices) {
            position.x = std::roundf(position.x);
            position.y = std::roundf(position.y);
        }

        Renderer2D::Submit(s_vertices);
    }

    void Sprite2D::Destroy() {
    }

    void Sprite2D::Reset() {
    }

    void Sprite2D::Enable() {
    }

    void Sprite2D::Disable() {
    }

    void Sprite2D::SetTexture(const std::string &filePath) {
        m_texture = AssetsManager::GetTexture(filePath);

        m_size.w = m_texture->GetWidth();
        m_size.h = m_texture->GetHeight();

        HELIOS_DEBUG("Texture size : %f, %f", m_texture->GetWidth(), m_texture->GetHeight());
    }

    void Sprite2D::ApplyScale() {
        // 0    2
        // 1    3

        if (m_isCentered) {
            s_vertices[0].position.x = transform.position.x - m_size.w * transform.scale.x * 0.5f;
            s_vertices[0].position.y = transform.position.y - m_size.h * transform.scale.y * 0.5f;

            s_vertices[1].position.x = transform.position.x - m_size.w * transform.scale.x * 0.5f;
            s_vertices[1].position.y = transform.position.y + m_size.h * transform.scale.y * 0.5f;

            s_vertices[2].position.x = transform.position.x + m_size.w * transform.scale.x * 0.5f;
            s_vertices[2].position.y = transform.position.y - m_size.h * transform.scale.y * 0.5f;

            s_vertices[3].position.x = transform.position.x + m_size.w * transform.scale.x * 0.5f;
            s_vertices[3].position.y = transform.position.y + m_size.h * transform.scale.y * 0.5f;
        } else {
            s_vertices[0].position.x = transform.position.x;
            s_vertices[0].position.y = transform.position.y;

            s_vertices[1].position.x = transform.position.x;
            s_vertices[1].position.y = transform.position.y + m_size.h * transform.scale.y;

            s_vertices[2].position.x = transform.position.x + m_size.w * transform.scale.x;
            s_vertices[2].position.y = transform.position.y;

            s_vertices[3].position.x = transform.position.x + m_size.w * transform.scale.x;
            s_vertices[3].position.y = transform.position.y + m_size.h * transform.scale.y;
        }
    }

    void Sprite2D::ApplyRotation() {
        // To avoid unnecessary computations
        if (transform.rotation == 0.0f) return;

        const auto matrix = Transform2D::Rotate(-transform.rotation);
        for (auto &[position, uv, color, texIndex]: s_vertices) {
            const auto tempPosition = matrix * Vector4(position - Vector3(transform.position, 0.0f), 0.0f) +
                                      Vector4(transform.position, 0.0f, 0.0f);
            position = Vector3(tempPosition.x, tempPosition.y, position.z);
        }
    }
} // helios
