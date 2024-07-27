//
// Created by Toudonou on 19/07/2024.
//

#include "Helios/core/defines.h"
#include "Helios/core/Engine.h"

#include "Helios/core/log.h"

namespace helios {
    Window *Engine::m_window = nullptr;
    bool Engine::m_init = false;

    void Engine::Init(const ApplicationSpecifications &specifications) {
        Logger::Init("logs.txt");

        if (m_init) {
            HELIOS_WARN("Trying to initialize the engine twice");
            return;
        }

        // Init GLFW library
        HELIOS_ASSERT_MSG(glfwInit(), "Failed to initialize GLFW");

        // Setting up the major and minor GLFW version
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        // Telling GLFW that we want to used the core profile
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // Setting up the window
        m_window = Window::GetInstance();
        m_window->Init(specifications);

        // Initialize GLAD
        HELIOS_ASSERT_MSG(gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)), "Failed to initialize GLAD");

        m_init = true;
        HELIOS_INFO("Engine initialized successfully");
    }

    void Engine::Run() {
        if (!m_init) {
            HELIOS_WARN("Trying to run the engine without initializing it");
            return;
        }

        while (!m_window->IsClosed()) {
            glDisable(GL_DEPTH_TEST);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glClearColor(0.21, 0.21, 0.21, 1);

            m_window->Update();
        }
    }

    void Engine::ShutDown() {
        if (!m_init) {
            HELIOS_WARN("Trying to shutdown the engine without initializing it");
            return;
        }
        m_window->ShutDown();

        m_init = false;
        glfwTerminate();
        HELIOS_INFO("Engine shutdown successfully");

        // Shutting down the logger in last
        Logger::ShutDown();
    }

    Engine::~Engine() = default;
} // helios
