//
// Created by Toudonou on 19/07/2024.
//

#include "Helios/core/defines.h"
#include "Helios/core/log.h"
#include "Helios/core/Engine.h"
#include "Helios/input/Input.h"
#include "Helios/asset/AssetsManager.h"
#include "Helios/2D/Renderer2D.h"
#include "Helios/2D/node/Sprite2D.h"


namespace helios {
    Window *Engine::s_window = nullptr;
    bool Engine::s_init = false;

    void Engine::Init(const ApplicationSpecifications &specifications) {
        Logger::Init("logs.txt");

        if (s_init) {
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
        s_window = Window::GetInstance();
        HELIOS_ASSERT_MSG(s_window, "Failed to get the window instance");
        s_window->Init(specifications);

        // Initialize GLAD
        HELIOS_ASSERT_MSG(gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)),
                          "Failed to initialize GLAD");

        // Initialize the input system
        Input::Init(*s_window);
        // Initialize the asset manager
        AssetsManager::Init();
        // Initialize the renderer
        Renderer2D::Init(10000, *s_window);

        s_init = true;
        HELIOS_INFO("Engine initialized successfully");
        printf("\n");
    }

    void Engine::Run() {
        if (!s_init) {
            HELIOS_WARN("Trying to run the engine without initializing it");
            return;
        }

        auto sprite = Sprite2D();

        sprite.SetPosition(Vector2(300, 250));
        sprite.SetTexture("./playerGrey_walk1.png");

        // TODO : Scene management;

        while (!s_window->IsClosed()) {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glClearColor(0.21, 0.21, 0.21, 1);

            Renderer2D::DrawQuad(0, 0, 100, 100, Color::RED);

            if (Input::IsKeyPressed(GLFW_KEY_ESCAPE)) {
                s_window->Close();
            }

            sprite.SetVisible(!Input::IsKeyDown(GLFW_KEY_SPACE));

            if (Input::IsKeyPressed(GLFW_KEY_RIGHT)) {
                sprite.FlipX(false);
            } else if (Input::IsKeyPressed(GLFW_KEY_LEFT)) {
                sprite.FlipX(true);
            }

            if (Input::IsKeyPressed(GLFW_KEY_UP)) {
                sprite.FlipY(false);
            } else if (Input::IsKeyPressed(GLFW_KEY_DOWN)) {
                sprite.FlipY(true);
            }

            sprite.Update(0.0f);
            Renderer2D::Flush();

            Input::Update();
            s_window->Update();
        }
    }

    void Engine::Shutdown() {
        if (!s_init) {
            HELIOS_WARN("Trying to shutdown the engine without initializing it");
            return;
        }

        printf("\n");
        Renderer2D::Shutdown();
        AssetsManager::Shutdown();
        Input::Shutdown();
        s_window->Shutdown();
        s_window = nullptr;

        s_init = false;
        glfwTerminate();
        HELIOS_INFO("Engine shutdown successfully");

        // Shutting down the logger in last
        Logger::Shutdown();
    }

    Engine::~Engine() = default;
} // helios
