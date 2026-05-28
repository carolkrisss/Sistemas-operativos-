#include "../include/permisos.h"
#include <map>
#include <string> 


namespace Permisos{

    static std::map<std::string, Rol> rolesUsuario;

    void cargarPermisos(){
        rolesUsuario["admin"] = ROL_ADMIN;
        rolesUsuario["profesor"] = ROL_PROFESOR;
        rolesUsuario["alumno"] = ROL_ALUMNO;
    }

    Rol obtenerRol(const std::string& usuario){
        if(rolesUsuario.find(usuario) != rolesUsuario.end()){
            return rolesUsuario[usuario];
        }
        return ROL_ALUMNO;
    }
    std::string obtenerNombreRol(const std::string& usuario){
        Rol r = obtenerRol(usuario);

        if (r == ROL_ADMIN){
            return "Administrador";
        }
        if (r == ROL_ALUMNO){
            return "Alumno";
        }
        if (r == ROL_PROFESOR){
            return "Profesor";
        }

        return "Desconocido";

    }

    bool tienePermiso(const std::string& usuario, int opcion){
        Rol r = obtenerRol(usuario);

        if (opcion == 1){
            return (r == ROL_ADMIN || r == ROL_PROFESOR);
        }
        if (opcion == 2){
            return (r == ROL_ADMIN || r == ROL_ALUMNO || r == ROL_PROFESOR);
        }
        if (opcion == 3){
            return (r == ROL_ADMIN || r == ROL_PROFESOR);
        }
        if (opcion == 4){
            return (r == ROL_ADMIN);
        }
        return true;


        
    }


}
