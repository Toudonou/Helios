//
// Created by Toudonou on 30/07/2024.
//

#include "Helios/core/log.h"
#include "Helios/asset/AssetsManager.h"

namespace helios {
    bool AssetsManager::s_init = false;
    std::vector<Texture *> AssetsManager::s_textures;

    void AssetsManager::Init() {
        if (s_init) {
            HELIOS_WARN("Trying to initialize Asset manager twice");
            return;
        }
        s_textures.clear();
        s_init = true;
        HELIOS_INFO("Asset manager initialized successfully");
    }

    void AssetsManager::Shutdown() {
        if (!s_init) {
            HELIOS_WARN("Trying to shutdown a non initialized Asset manager");
            return;
        }
        s_init = false;
        s_textures.clear();
        HELIOS_INFO("Asset manager shutdown successfully");
    }

    Texture *AssetsManager::GetTexture(const std::string &filePath) {
        Texture *texture = nullptr;
        for (const auto &tex: s_textures) {
            if (tex->GetPath() == filePath) {
                texture = tex;
                break;
            }
        }

        if (texture != nullptr) {
            HELIOS_DEBUG("Texture already loaded : %s", filePath.c_str());
            return texture;
        }

        // If the texture is not found
        texture = new Texture(s_textures.size());
        texture->LoadFromFile(filePath);
        s_textures.push_back(texture);
        HELIOS_DEBUG("Texture loaded from file : %s", filePath.c_str());

        return texture;
    }
} // helios
