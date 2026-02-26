#include "../include/seguridad.h"
#include <sstream>
#include <iomanip>
#include <functional>

namespace Seguridad {
    std::string convertirAHex(const std::string& comando) {
        std::stringstream ss;

        for(unsigned char c : comando) {
            ss << std::hex << std::setw(2)
               << std::setfill('0') << (int)c;
        }

        return ss.str();
    }

    std::string generarHash(const std::string& data) {
        std::hash<std::string> hashFunction;
        size_t hashValue = hashFunction(data);

        std::stringstream ss;
        ss << std::hex << hashValue;

        return ss.str();
    }
}