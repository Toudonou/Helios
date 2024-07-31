//
// Created by Toudonou on 30/07/2024.
//

#ifndef RENDERER2D_H
#define RENDERER2D_H

#include "Helios/2D/shape/Rectangle2D.h"
#include "Helios/core/defines.h"
#include "Helios/core/Window.h"
#include "Helios/maths/maths.h"
#include "Helios/shader/Shader.h"

namespace helios {
    struct HELIOS_API Vertex {
        Vector3 position;
        Vector2 uv;
        Color color;
        real_t texID;
    };

    class HELIOS_API Renderer2D {
    public:
        // Initialize the renderer : batch rendering
        static void Init(GLuint maxRenderable, Window &window);

        // Shutdown the renderer
        static void Shutdown();

        // Begin the drawing process
        static void Begin();

        // End the drawing process
        static void End();

        // Submit a vertex to the renderer
        static void Submit(const Rectangle2D &rectangle);

        // Flush the renderer
        static void Flush();

    private:
        static bool s_init;

        static GLuint s_VAO, s_VBO, s_IBO;

        static GLuint s_maxRenderable;

        static std::vector<Vertex> s_vertices;

        static Window *s_window;

        static std::shared_ptr<Shader> s_shader;

        Renderer2D() = default;

        ~Renderer2D() = default;
    };
} // helios

#endif // RENDERER2D_H
