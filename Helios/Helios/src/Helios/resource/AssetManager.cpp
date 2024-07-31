//
// Created by Toudonou on 30/07/2024.
//

#include "Helios/core/log.h"
#include "Helios/asset/AssetManager.h"

namespace helios {
    bool AssetManager::s_init = false;
    std::vector<std::shared_ptr<Asset> > AssetManager::s_assets;

    void AssetManager::Init() {
        if (s_init) {
            HELIOS_WARN("Trying to initialize Asset manager twice");
            return;
        }
        s_assets.clear();
        s_init = true;
        HELIOS_INFO("Asset manager initialized successfully");
    }

    void AssetManager::Shutdown() {
        if (!s_init) {
            HELIOS_WARN("Trying to shutdown a non initialized Asset manager");
            return;
        }
        s_init = false;
        s_assets.clear();
        HELIOS_INFO("Asset manager shutdown successfully");
    }
} // helios
