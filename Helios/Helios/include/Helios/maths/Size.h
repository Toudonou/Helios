//
// Created by Toudonou on 30/07/2024.
//

#ifndef SIZE_H
#define SIZE_H

#include "Helios/core/defines.h"

namespace helios {
    struct HELIOS_API Size {
        // Width
        GLuint w;
        // Height
        GLuint h;

        Size(const GLuint w, const GLuint h) : w(w), h(h) {
        }
    };
}

#endif // SIZE_H
