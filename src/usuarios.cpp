#include "../include/usuarios.h"
#include <iostream>
#include <fstream>
#include <map>


namespace Usuarios {
    static std::map<std::string, std::string> usuariosDB;
    static std::string usuarioActual = "";

    void cargarUsuarios(){
        usuariosDB["admin"] = "1234";
        usuariosDB["alumno"] = "abcd";
        usuariosDB["profesor"] = "2024";

        std::ifstream file("data/usuarios.dat");
        if(file.is_open()){
            std::string u, p;
            while(file >> u >> p) {
                usuariosDB[u] = p;
    
            }
            file.close();
        }
    }

    bool iniciarSesion (const std::string& usuario, const std::string& pasword){
        if(usuariosDB.find(usuario) != usuariosDB.end() && usuariosDB[usuario] == pasword){
            usuarioActual = usuario;
            return true;

        }
        return false;
    }
    std::string getUsuarioActual(){
        return usuarioActual;
    }
    void cerrarSesion(){
        usuarioActual = "";
    }
}