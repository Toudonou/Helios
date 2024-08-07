//
// Created by Toudonou on 19/07/2024.
//

#ifndef ENGINE_H
#define ENGINE_H

#include "Helios/core/defines.h"
#include "Helios/core/Window.h"

namespace helios {
    class HELIOS_API Engine {
    public:
        static void Init(const ApplicationSpecifications &specifications);

        static void Run();

        static void Shutdown();

    private:
        static Window *s_window;

        static bool s_init;

        Engine() = default;

        ~Engine();
    };
} // helios

#endif // ENGINE_H
