#ifndef ALMACENAMIENTO_H
#define ALMACENAMIENTO_H
#include <string>


struct Registro {
    char usuario[50];
    char comandoOriginal[200];
    char comandoHex[400];
    char hash[100];
    long timestamp;

};


namespace Almacenamiento {
    bool guardarRegistro(const Registro& reg);
    void listarRegistros();
    int contarRegistros();

}

#endif