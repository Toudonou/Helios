//
// Created by Toudonou on 26/07/2024.
//

#include "Helios/core/Window.h"
#include "Helios/core/log.h"

namespace helios {
    Window *Window::s_instance = nullptr;

    // Callbacks functions
    void frame_buffer_size_callback(GLFWwindow *window, const int width, const int height) {
        if (Window::s_instance) {
            Window::s_instance->m_specifications.width = width;
            Window::s_instance->m_specifications.height = height;
        }
        glViewport(0, 0, width, height);
    }

    Window *Window::GetInstance() {
        if (s_instance == nullptr) {
            s_instance = new Window();
        }
        return s_instance;
    }

    void Window::Init(const ApplicationSpecifications &specifications) {
        if (m_init) {
            HELIOS_WARN("Trying to initialize the window twice");
            return;
        }

        m_specifications = specifications;

        // Setting up window resizable capability
        glfwWindowHint(GLFW_RESIZABLE, m_specifications.resizable);

        // Creating the window
        m_window = glfwCreateWindow(m_specifications.width, m_specifications.height, m_specifications.title.c_str(),
                                    nullptr, nullptr);
        HELIOS_ASSERT_MSG(m_window != nullptr, "Failed to create GLFW window");

        // Setting up the window as the current context
        glfwMakeContextCurrent(m_window);

        // // Setting up the viewport
        // glViewport(0, 0, m_specifications.width, m_specifications.height);

        // Setting up the frame buffer callback function
        glfwSetFramebufferSizeCallback(m_window, frame_buffer_size_callback);

        m_init = true;
        HELIOS_INFO("Window initialized successfully");
    }

    void Window::Update() const {
        if (!m_init) {
            HELIOS_WARN("Trying to update a non initialized window");
            return;
        }

        glfwPollEvents();
        // Swapping the buffers
        glfwSwapBuffers(m_window);
    }

    void Window::ShutDown() {
        if (!m_init) {
            HELIOS_WARN("Trying to shutdown a non initialized window");
            return;
        }

        glfwDestroyWindow(m_window);
        m_init = false;
        HELIOS_INFO("Window shutdown successfully");
    }
} // helios
