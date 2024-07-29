//
// Created by Toudonou on 30/07/2024.
//

#include "ResourceManager.h"

#include "log.h"

namespace helios {
    bool ResourceManager::s_init = false;
    std::vector<std::shared_ptr<Resource> > ResourceManager::s_resources;

    void ResourceManager::Init() {
        if (s_init) {
            HELIOS_WARN("Trying to initialize resource manager twice");
            return;
        }
        s_resources.clear();
        s_init = true;
        HELIOS_INFO("Resource manager initialized successfully");
    }

    void ResourceManager::Shutdown() {
        if (!s_init) {
            HELIOS_WARN("Trying to shutdown a non initialized resource manager");
            return;
        }
        s_init = false;
        s_resources.clear();
        HELIOS_INFO("Resource manager shutdown successfully");
    }
} // helios
