//
// Created by Toudonou on 26/07/2024.
//

#ifndef INPUT_H
#define INPUT_H

#include "Helios/core/defines.h"
#include "Helios/core/Window.h"

namespace helios {
    class Input {
    public:
        // Initialize the input system
        static void Init(const Window &window);

        // Update the input system
        static void Update();

        // Shutdown the input system
        static void ShutDown();

        // Return true if the key is just pressed
        [[nodiscard]] static bool IsKeyPressed(const unsigned int keycode) {
            return m_frameKeys[keycode] && !m_lastFrameKeys[keycode];
        }

        // Return true if the key is just released
        [[nodiscard]] static bool IsKeyReleased(const unsigned int keycode) {
            return !m_frameKeys[keycode] && m_lastFrameKeys[keycode];
        }

        // Return true if the key is held down
        [[nodiscard]] static bool IsKeyDown(const unsigned int keycode) { return m_frameKeys[keycode]; }

        // Return true if the mouse button is just pressed
        [[nodiscard]] static bool IsMouseButtonPressed(const unsigned int button) {
            return m_frameMouseButtonKeys[button] && !m_lastFrameMouseButtonKeys[button];
        }

        // Return true if the mouse button is released
        [[nodiscard]] static bool IsMouseButtonReleased(const unsigned int button) {
            return !m_frameMouseButtonKeys[button] && m_lastFrameMouseButtonKeys[button];
        }

        // Return true if the mouse button is held down
        [[nodiscard]] static bool IsMouseButtonDown(const unsigned int button) {
            return m_frameMouseButtonKeys[button];
        }

    private:
        static bool m_init;

        static bool m_frameKeys[HELIOS_MAX_KEYS];

        static bool m_lastFrameKeys[HELIOS_MAX_KEYS];

        static bool m_frameMouseButtonKeys[HELIOS_MAX_MOUSE_BUTTONS];

        static bool m_lastFrameMouseButtonKeys[HELIOS_MAX_MOUSE_BUTTONS];

        static real m_mouseX, m_mouseY;

        Input() = default;

        ~Input() = default;

        // Friends functions
        // Callbacks prototyes
        friend void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

        friend void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);

        friend void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);
    };
} // helios

#endif // INPUT_H
