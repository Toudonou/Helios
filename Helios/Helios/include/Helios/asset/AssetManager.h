//
// Created by Toudonou on 30/07/2024.
//

#ifndef  ASSETMANAGER_H
#define  ASSETMANAGER_H

#include "Helios/core/defines.h"
#include "Helios/asset/Asset.h"

namespace helios {
    class HELIOS_API AssetManager {
    public:
        // Initialize the resource manager
        static void Init();

        // Shutdown the resource manager
        static void Shutdown();

        // Load a resource from a file
        template<typename T>
        static std::shared_ptr<T> GetAsset(const std::string &path) {
            // Will return the first resource that has the same path
            auto iterator = std::find_if(s_assets.begin(), s_assets.end(),
                                         [&path](const std::shared_ptr<Asset> &resource) {
                                             return resource->GetPath() == path;
                                         });

            // If the resource is found
            if (iterator != s_assets.end()) {
                // Return the derivative of the ressource : the real resource
                return std::dynamic_pointer_cast<T>(*iterator);
            }

            // If the resource is not found
            auto resource = std::make_shared<Asset>();
            resource->LoadFromFile(path);
            s_assets.push_back(resource);
            return resource;
        }

    private:
        // To check if the resource manager is initialized : maybe not necessary
        static bool s_init;

        // To store all the ressources
        static std::vector<std::shared_ptr<Asset> > s_assets;

        AssetManager() = default;

        ~AssetManager() = default;
    };
} // helios

#endif // ASSETMANAGER_H
