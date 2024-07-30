//
// Created by Toudonou on 30/07/2024.
//

#ifndef  RESOURCEMANAGER_H
#define  RESOURCEMANAGER_H

#include "Helios/core/defines.h"
#include "Helios/core/Resource.h"

namespace helios {
    class  HELIOS_API ResourceManager {
    public:
        // Initialize the resource manager
        static void Init();

        // Shutdown the resource manager
        static void Shutdown();

        // Load a resource from a file
        template<typename T>
        static std::shared_ptr<T> GetResource(const std::string &path) {
            // Will return the first resource that has the same path
            auto iterator = std::find_if(s_resources.begin(), s_resources.end(),
                                         [&path](const std::shared_ptr<Resource> &resource) {
                                             return resource->GetPath() == path;
                                         });

            // If the resource is found
            if (iterator != s_resources.end()) {
                // Return the derivative of the ressource : the real resource
                return std::dynamic_pointer_cast<T>(*iterator);
            }

            // If the resource is not found
            auto resource = std::make_shared<Resource>();
            resource->LoadFromFile(path);
            s_resources.push_back(resource);
            return resource;
        }

    private:
        // To check if the resource manager is initialized : maybe not necessary
        static bool s_init;

        // To store all the ressources
        static std::vector<std::shared_ptr<Resource> > s_resources;
    };
} // helios

#endif // RESOURCEMANAGER_H
