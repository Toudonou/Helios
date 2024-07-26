//
// Created by Toudonou on 26/07/2024.
//

#ifndef WINDOW_H
#define WINDOW_H

#include "Helios/core/defines.h"

namespace helios {
    // To store the application specifications
    struct HELIOS_API ApplicationSpecifications {
        std::string title;
        int width;
        int height;
        bool resizable;
    };

    class HELIOS_API Window {
    public:
        // Singleton
        static Window *GetInstance();

        // Initialize the window
        void Init(const ApplicationSpecifications &specifications);

        // Call each frame
        void Update() const;

        // To uninitialize the window
        void ShutDown();

        // To check if the window is closed
        [[nodiscard]] bool IsClosed() const { return glfwWindowShouldClose(m_window); }

        // To close the window
        void Closed() const { glfwSetWindowShouldClose(m_window, true); }

        // To get the window
        [[nodiscard]] GLFWwindow *GetWindow() const { return m_window; }

    private:
        // To store the instance of the window
        static Window *s_instance;

        // To store the window
        GLFWwindow *m_window = nullptr;

        // To store the application specifications
        ApplicationSpecifications m_specifications;

        // To store the initialization state
        bool m_init = false;

        Window() = default;

        ~Window() = default;

        // Friends functions
        // Callbacks prototyes
        // Call when the window is resized
        friend void frame_buffer_size_callback(GLFWwindow *window, int width, int height);
    };
} // helios

#endif // WINDOW_H
