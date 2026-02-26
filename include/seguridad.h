#ifndef SEGURIDAD_H
#define SEGURIDAD_H
#include <string>

namespace Seguridad {
    std::string convertirAHex(const std::string& comando);
    std::string generarHash(const std::string& data);
}

#endif