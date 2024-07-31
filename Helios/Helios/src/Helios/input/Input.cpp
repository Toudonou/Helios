//
// Created by Toudonou on 26/07/2024.
//

#include "Helios/input/Input.h"

#include "Helios/core/log.h"

namespace helios {
    bool Input::s_init = false;
    Window *Input::s_window = nullptr;
    bool Input::s_frameKeys[HELIOS_MAX_KEYS];
    bool Input::s_lastFrameKeys[HELIOS_MAX_KEYS];
    bool Input::s_frameMouseButtonKeys[HELIOS_MAX_MOUSE_BUTTONS];
    bool Input::s_lastFrameMouseButtonKeys[HELIOS_MAX_MOUSE_BUTTONS];
    real_t Input::s_mouseX;
    real_t Input::s_mouseY;

    // Callbacks functions
    void key_callback(GLFWwindow *window, const int key, int scancode, const int action, int mods) {
        Input::s_frameKeys[key] = action != GLFW_RELEASE;
    }

    void mouse_button_callback(GLFWwindow *window, const int button, const int action, int mods) {
        Input::s_frameMouseButtonKeys[button] = action != GLFW_RELEASE;
    }

    void cursor_position_callback(GLFWwindow *window, const double xpos, const double ypos) {
        Input::s_mouseX = static_cast<float>(xpos);
        Input::s_mouseY = static_cast<float>(ypos);
    }

    void Input::Init(Window &window) {
        if (s_init) {
            HELIOS_WARN("Trying to initialize the input system twice");
            return;
        }

        s_window = &window;
        HELIOS_ASSERT_MSG(s_window, "The window should not be null");

        // Setting up the callbacks
        glfwSetKeyCallback(window.GetWindow(), key_callback);
        glfwSetMouseButtonCallback(window.GetWindow(), mouse_button_callback);
        glfwSetCursorPosCallback(window.GetWindow(), cursor_position_callback);

        // Initialize key's arrays
        memset(s_frameKeys, false, HELIOS_MAX_KEYS);
        memset(s_lastFrameKeys, false, HELIOS_MAX_KEYS);
        memset(s_frameMouseButtonKeys, false, HELIOS_MAX_MOUSE_BUTTONS);
        memset(s_lastFrameMouseButtonKeys, false, HELIOS_MAX_MOUSE_BUTTONS);

        s_init = true;
        HELIOS_INFO("Input system initialized successfully");
    }

    void Input::Update() {
        if (!s_init) {
            HELIOS_WARN("Trying to update the input system without initializing it");
            return;
        }

        // Copy the current frame keys to the last frame keys
        memcpy(s_lastFrameKeys, s_frameKeys, HELIOS_MAX_KEYS);

        // Copy the current frame mouse button keys to the last frame mouse button keys
        memcpy(s_lastFrameMouseButtonKeys, s_frameMouseButtonKeys, HELIOS_MAX_MOUSE_BUTTONS);
    }

    void Input::ShutDown() {
        if (!s_init) {
            HELIOS_WARN("Trying to shutdown a non initialized input system");
            return;
        }

        memset(s_frameKeys, false, HELIOS_MAX_KEYS);
        memset(s_lastFrameKeys, false, HELIOS_MAX_KEYS);
        memset(s_frameMouseButtonKeys, false, HELIOS_MAX_MOUSE_BUTTONS);
        memset(s_lastFrameMouseButtonKeys, false, HELIOS_MAX_MOUSE_BUTTONS);

        s_init = false;
        HELIOS_INFO("Input system shutdown successfully");
    }
} // helios
