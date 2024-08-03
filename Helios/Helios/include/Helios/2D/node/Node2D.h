//
// Created by Toudonou on 31/07/2024.
//

#ifndef NODE2D_H
#define NODE2D_H

#include "Helios/core/defines.h"
#include "Helios/2D/Transform2D.h"

namespace helios {
    // Base class for all 2D nodes
    class HELIOS_API Node2D {
    public:
        // TODO : Enum class state

        Node2D() = default;

        virtual ~Node2D() = default;

        // Function launched when the node is added to the a scene
        virtual void Start() = 0;

        // Update the node
        virtual void Update(float deltaTime) = 0;

        // Destroy the node
        virtual void Destroy() = 0;

        // Function launched when the node is reset
        virtual void Reset() = 0;

        // Function launched when the node is enabled
        virtual void Enable() = 0;

        // Function launched when the node is disabled
        virtual void Disable() = 0;

        [[nodiscard]] GLuint GetNodeID() const { return nodeID; }

        Transform2D &GetTransform() { return transform; }
        void SetTransform(const Transform2D &transform) { this->transform = transform; }

        [[nodiscard]] Vector2 GetPosition() const { return transform.position; }
        void SetPosition(const Vector2 &position) { transform.position = position; }

        [[nodiscard]] Vector2 GetScale() const { return transform.scale; }
        void SetScale(const Vector2 &scale) { transform.scale = scale; }

        [[nodiscard]] real_t GetRotation() const { return transform.rotation; }
        void SetRotation(const real_t rotation) { transform.rotation = rotation; }

        [[nodiscard]] real_t GetZIndex() const { return zIndex; }
        void SetZIndex(const real_t zIndex) { this->zIndex = zIndex; }

    protected:
        GLuint nodeID{};

        Transform2D transform{};

        real_t zIndex{};
    };
} // helios

#endif // NODE2D_H
