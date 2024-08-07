//
// Created by Toudonou on 30/07/2024.
//

#ifndef SIZE_H
#define SIZE_H

#include "Helios/core/defines.h"

namespace helios {
    struct HELIOS_API Size {
        // Width
        GLfloat w;
        // Height
        GLfloat h;

        Size() : w(0), h(0) {
        }

        Size(const GLfloat width, const GLfloat height) : w(width), h(height) {
        }
    };
}

#endif // SIZE_H
