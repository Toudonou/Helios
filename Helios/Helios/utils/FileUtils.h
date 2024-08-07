//
// Created by Toudonou on 30/07/2024.
//

#ifndef FILEUTILS_H
#define FILEUTILS_H

#include "Helios/core/defines.h"

namespace helios {
    class HELIOS_API FileUtils {
    public:
        static std::string ReadFile(const std::string &filepath);
    };
} // helios

#endif // FILEUTILS_H
