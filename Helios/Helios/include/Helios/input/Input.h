//
// Created by Toudonou on 26/07/2024.
//

#ifndef INPUT_H
#define INPUT_H

#include "Helios/core/defines.h"
#include "Helios/core/Window.h"

namespace helios {
    class HELIOS_API Input {
        // TODO : Add my key enum class
    public:
        // Initialize the input system
        static void Init(Window &window);

        // Update the input system
        static void Update();

        // Shutdown the input system
        static void Shutdown();

        // Return true if the key is just pressed
        [[nodiscard]] static bool IsKeyPressed(const unsigned int keycode) {
            return s_frameKeys[keycode] && !s_lastFrameKeys[keycode];
        }

        // Return true if the key is just released
        [[nodiscard]] static bool IsKeyReleased(const unsigned int keycode) {
            return !s_frameKeys[keycode] && s_lastFrameKeys[keycode];
        }

        // Return true if the key is held down
        [[nodiscard]] static bool IsKeyDown(const unsigned int keycode) { return s_frameKeys[keycode]; }

        // Return true if the mouse button is just pressed
        [[nodiscard]] static bool IsMouseButtonPressed(const unsigned int button) {
            return s_frameMouseButtonKeys[button] && !s_lastFrameMouseButtonKeys[button];
        }

        // Return true if the mouse button is released
        [[nodiscard]] static bool IsMouseButtonReleased(const unsigned int button) {
            return !s_frameMouseButtonKeys[button] && s_lastFrameMouseButtonKeys[button];
        }

        // Return true if the mouse button is held down
        [[nodiscard]] static bool IsMouseButtonDown(const unsigned int button) {
            return s_frameMouseButtonKeys[button];
        }

        // Return the mouse x-position
        [[nodiscard]] static real_t GetMouseX() { return s_mouseX; }

        // Return the mouse y-position
        [[nodiscard]] static real_t GetMouseY() { return s_mouseY; }

    private:
        static bool s_init;

        static Window *s_window;

        static bool s_frameKeys[HELIOS_MAX_KEYS];

        static bool s_lastFrameKeys[HELIOS_MAX_KEYS];

        static bool s_frameMouseButtonKeys[HELIOS_MAX_MOUSE_BUTTONS];

        static bool s_lastFrameMouseButtonKeys[HELIOS_MAX_MOUSE_BUTTONS];

        static real_t s_mouseX, s_mouseY;

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
