#ifndef PERMISOS_H
#define PERMISOS_H
#include<string>


namespace Permisos {
    enum Rol {
        ROL_ADMIN,
        ROL_ALUMNO,
        ROL_PROFESOR

    };

    void cargarPermisos();
    bool tienePermiso(const std::string& usuario, int opcion);
    Rol obtenerRol(const std::string& usuario);
    std::string obtenerNombreRol(const std::string& usuario);


}

#endif
