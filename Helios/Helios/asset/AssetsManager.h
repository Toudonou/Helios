//
// Created by Toudonou on 30/07/2024.
//

#ifndef  ASSETMANAGER_H
#define  ASSETMANAGER_H

#include "Helios/core/defines.h"
#include "Helios/core/log.h"
#include "Helios/asset/Texture.h"

namespace helios {
    class HELIOS_API AssetsManager {
    public:
        // Initialize the resource manager
        static void Init();

        // Shutdown the resource manager
        static void Shutdown();

        // Load a resource from a file
        static Texture *GetTexture(const std::string &filePath);

        // Get all the textures
        [[nodiscard]] static const std::vector<Texture *> &GetTextures() { return s_textures; }

        // TODO : Add a function to release a resource

    private:
        // To check if the resource manager is initialized : maybe not necessary
        static bool s_init;

        // To store all the ressources
        // TODO : Think about using smart pointers and map instead of vector
        static std::vector<Texture *> s_textures;

        AssetsManager() = default;

        ~AssetsManager() = default;
    };
} // helios

#endif // ASSETMANAGER_H
