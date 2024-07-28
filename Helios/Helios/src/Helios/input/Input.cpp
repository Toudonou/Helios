//
// Created by Toudonou on 26/07/2024.
//

#include "Helios/input/Input.h"

#include "Helios/core/log.h"

namespace helios {
    bool Input::m_init = false;
    bool Input::m_frameKeys[HELIOS_MAX_KEYS];
    bool Input::m_lastFrameKeys[HELIOS_MAX_KEYS];
    bool Input::m_frameMouseButtonKeys[HELIOS_MAX_MOUSE_BUTTONS];
    bool Input::m_lastFrameMouseButtonKeys[HELIOS_MAX_MOUSE_BUTTONS];
    real Input::m_mouseX;
    real Input::m_mouseY;

    // Callbacks functions
    void key_callback(GLFWwindow *window, const int key, int scancode, const int action, int mods) {
        Input::m_frameKeys[key] = action != GLFW_RELEASE;
    }

    void mouse_button_callback(GLFWwindow *window, const int button, const int action, int mods) {
        Input::m_frameMouseButtonKeys[button] = action != GLFW_RELEASE;
    }

    void cursor_position_callback(GLFWwindow *window, const double xpos, const double ypos) {
        Input::m_mouseX = static_cast<float>(xpos);
        Input::m_mouseY = static_cast<float>(ypos);
    }

    void Input::Init(const Window &window) {
        if (m_init) {
            HELIOS_WARN("Trying to initialize the input system twice");
            return;
        }

        // Setting up the callbacks
        glfwSetKeyCallback(window.GetWindow(), key_callback);
        glfwSetMouseButtonCallback(window.GetWindow(), mouse_button_callback);
        glfwSetCursorPosCallback(window.GetWindow(), cursor_position_callback);

        // Initialize key's arrays
        memset(m_frameKeys, false, HELIOS_MAX_KEYS);
        memset(m_lastFrameKeys, false, HELIOS_MAX_KEYS);
        memset(m_frameMouseButtonKeys, false, HELIOS_MAX_MOUSE_BUTTONS);
        memset(m_lastFrameMouseButtonKeys, false, HELIOS_MAX_MOUSE_BUTTONS);

        m_init = true;
        HELIOS_INFO("Input system initialized successfully");
    }

    void Input::Update() {
        if (!m_init) {
            HELIOS_WARN("Trying to update the input system without initializing it");
            return;
        }

        // Copy the current frame keys to the last frame keys
        memcpy(m_lastFrameKeys, m_frameKeys, HELIOS_MAX_KEYS);

        // Copy the current frame mouse button keys to the last frame mouse button keys
        memcpy(m_lastFrameMouseButtonKeys, m_frameMouseButtonKeys, HELIOS_MAX_MOUSE_BUTTONS);
    }

    void Input::ShutDown() {
        memset(m_frameKeys, false, HELIOS_MAX_KEYS);
        memset(m_lastFrameKeys, false, HELIOS_MAX_KEYS);
        memset(m_frameMouseButtonKeys, false, HELIOS_MAX_MOUSE_BUTTONS);
        memset(m_lastFrameMouseButtonKeys, false, HELIOS_MAX_MOUSE_BUTTONS);

        m_init = false;
        HELIOS_INFO("Input system shutdown successfully");
    }
} // helios
