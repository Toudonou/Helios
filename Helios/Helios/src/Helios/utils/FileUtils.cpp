//
// Created by Toudonou on 30/07/2024.
//

#include "Helios/utils/FileUtils.h"
#include "Helios/core/log.h"

namespace helios {
    std::string FileUtils::ReadFile(const std::string &filepath) {
        std::ifstream file(filepath);
        std::string line;
        std::string result;

        if (!file.is_open()) {
           HELIOS_ERROR("Error during file opening : %s", filepath.c_str());
            return "";
        }

        while (getline(file, line)) result.append(line).append("\n");

        return result;
    }
} // helios
