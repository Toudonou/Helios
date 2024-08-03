//
// Created by Toudonou on 31/07/2024.
//

#ifndef SPRITE2D_H
#define SPRITE2D_H

#include "Helios/2D/node/Node2D.h"
#include "Helios/asset/Texture.h"
#include "Helios/maths/Color.h"
#include "Helios/2D/Renderer2D.h"

namespace helios {
    class HELIOS_API Sprite2D : public Node2D {
    public:
        Sprite2D();

        ~Sprite2D() override = default;

        void Start() override;

        void Update(float deltaTime) override;

        void Destroy() override;

        void Reset() override;

        void Enable() override;

        void Disable() override;

        void SetTexture(const std::string &filePath);

        void SetColor(const Color &color) { this->color = color; }

        [[nodiscard]] const Color &GetColor() const { return color; }

        void SetVisible(const bool isVisible) { m_isVisible = isVisible; }

        void FlipX(const bool flipX) { m_flipX = flipX; }

        void FlipY(const bool flipY) { m_flipY = flipY; }

        void SetCentered(const bool isCentered) { m_isCentered = isCentered; }

        // void SetOffset(const Vector2 &offset) { m_offset = offset; }

    protected:
        Texture *m_texture;

        Color color;

        bool m_isVisible;

        bool m_flipX;

        bool m_flipY;

        bool m_isCentered;

    private:
        void ApplyScale();

        void ApplyRotation();

        std::vector<Vertex> s_vertices;

        Size m_size;
    };
} // helios

#endif // SPRITE2D_H
