#ifndef USUARIOS_H
#define USUARIOS_H
#include <string>
#include <map>

namespace Usuarios{
    bool iniciarSesion(const std::string& usuario, const std::string& pasword);
    void cargarUsuarios();
    std::string getUsuarioActual();
    void cerrarSesion();

}

#endif