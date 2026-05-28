#include "../include/almacenamiento.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>

namespace Almacenamiento {
    bool guardarRegistro(const Registro& reg){
        std::ofstream file("data/registros.bin", std::ios::binary | std::ios::app);

        if(!file.is_open()){
            std::cerr << "Error.No se pudo abrir registros.bin" << std::endl;
            return false;
        }

        file.write(reinterpret_cast<const char*>(&reg), sizeof(Registro));
        file.close();

        std::cout << "Regustro guardado en registros.bin" << std::endl;
        return true;

    }

    void listarRegistros(){
        std::ifstream file("data/registros.bin", std::ios::binary);

        if(!file.is_open()){
            std::cout << "No hay registros guardados" << std::endl;
            return;
        }

        Registro reg;
        int count = 0;


        std::cout << "REGISTROS GUARDADOS";

        while(file.read(reinterpret_cast<char*>(&reg), sizeof(Registro))){
            count++;
            std::cout << "Registro #" << count << std::endl;
            std::cout << "Usuario: " << reg.usuario  << std::endl;
            std::cout << "Comando: " << reg.comandoOriginal  << std::endl;
            std::cout << "Hex: " << reg.comandoHex  << std::endl;
            std::cout << "Hash: " << reg.hash  << std::endl;


            time_t tiempo = reg.timestamp;
            std::cout << "Fecha: " << ctime(&tiempo);
            std::cout << "---------------------\n";
        }
        file.close();

        if (count == 0){
            std::cout << "No hay registros guardados" << std::endl;

        }
        else {
            std::cout << "Total: " << count << "registro (s)/n";
        }
        

    }

    int contarRegistros(){
        std::ifstream file("data/registros.bin", std::ios::binary);
        if(!file.is_open()) return 0;

        file.seekg(0, std::ios::end);
        int size = file.tellg();
        file.close();

        return size / sizeof(Registro);
    }

}