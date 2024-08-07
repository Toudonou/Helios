#include "Helios/core/Engine.h"
#include "Helios/core/log.h"


using namespace helios;

int main() {
    Engine::Init(ApplicationSpecifications{"Helios", 800, 600, false});
    Engine::Run();
    Engine::Shutdown();

    system("pause");
    return 0;
}