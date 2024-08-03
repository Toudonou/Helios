//
// Created by Toudonou on 21/07/2024.
//

// For testing purposes

#include "Helios/core/Engine.h"
#include "Helios/core/log.h"

using namespace helios;

int main() {
    Engine::Init(ApplicationSpecifications{"Helios", 800, 600, false});
    Engine::Run();
    Engine::Shutdown();

    std::cin.get();
    return 0;
}
