//
// Created by Toudonou on 30/07/2024.
//

#ifndef ASSET_H
#define ASSET_H

#include "Helios/core/defines.h"

namespace helios {
    // Base class for all ressources
    class HELIOS_API Asset {
    public:
        Asset() = default;

        virtual ~Asset() = default;

        // Load ressource from a file
        virtual void LoadFromFile(const std::string &path) = 0;

        // Get the path of the ressource
        [[nodiscard]] virtual const std::string &GetPath() const = 0;
    };
}

#endif // ASSET_H
