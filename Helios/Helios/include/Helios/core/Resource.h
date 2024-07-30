//
// Created by Toudonou on 30/07/2024.
//

#ifndef RESOURCE_H
#define RESOURCE_H

#include "Helios/core/defines.h"

namespace helios {
    // Base class for all ressources
    class HELIOS_API Resource {
    public:
        Resource() = default;

        virtual ~Resource() = default;

        // Load ressource from a file
        virtual void LoadFromFile(const std::string &path) = 0;

        // Get the path of the ressource
        [[nodiscard]] virtual const std::string &GetPath() const = 0;
    };
}

#endif // RESOURCE_H
