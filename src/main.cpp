#include <iostream> 
#include <string> 
#include <limits>
#include <cstring>
#include <ctime>
#include "../include/seguridad.h"
#include "../include/auditoria.h"
#include "../include/usuarios.h"
#include "../include/almacenamiento.h"
#include "../include/permisos.h"
#include "../include/verificador.h"

using namespace std;

void mostrarMenu(){
    cout << "1.Procesar comando   ";
    cout << "2.Ver registros guardados  ";
    cout << "3.Registrar evento manual   ";
    cout << "4.Verificar integridad  ";
    cout << "5.Salir   \n";
    cout << "Selecciona una opcion:  ";
}
int main() {
    int opcion;
    string comando; 
    Usuarios::cargarUsuarios();
    string usuario, pasword;
    cout << "Login";

    while(true){
        cout << "Usuario: ";
        getline(cin, usuario);
        cout << "Password: ";
        getline (cin, pasword);


        if(Usuarios::iniciarSesion(usuario, pasword)){
            cout << "Sesion iniciada como: " << usuario << endl;
            Auditoria::registrarEvento("Usuario" + usuario + "inicio sesion");
            break;
        } else{
            cout << "Usuario o password incorrectos";
        }
    }

    Permisos::cargarPermisos();
    Verificador::iniciarThread();

    cout << "Rol: " << Permisos::obtenerNombreRol(usuario) << endl;
    
    while (true) {

        mostrarMenu();

        if (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada invalida";
            continue;
        }
        
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 


        switch(opcion) {

            case 1:
                if (!Permisos::tienePermiso(Usuarios::getUsuarioActual(), 1)){
                    cout << "No tienes permiso" << endl;
                    Auditoria::registrarEvento("Intento sin permiso: procesar comando por " + Usuarios::getUsuarioActual());
                    break;
                }
                cout << "Ingrese un comando: ";
                getline (cin, comando);

                if (comando.empty()){
                    cout << "No se ingreso un comando";
                    break; 
                }
                {
                    string hex = Seguridad::convertirAHex(comando);
                    string hash = Seguridad::generarHash(hex);

                    cout << "Hex: " << hex << endl;
                    cout << "Hash: " << hash << endl;


                    Registro reg;
                    strcpy(reg.usuario, Usuarios::getUsuarioActual().c_str());
                    strcpy(reg.comandoOriginal, comando.c_str());
                    strcpy(reg.comandoHex, hex.c_str());
                    strcpy(reg.hash, hash.c_str());
                    reg.timestamp = time(nullptr);
                    Almacenamiento::guardarRegistro(reg);
                    Auditoria::registrarEvento("Comando procesado: " + comando);
                    break;


                    Auditoria::registrarEvento("Comando procesado: " + comando);
                }
                break;
            case 2:
            if (!Permisos::tienePermiso(Usuarios::getUsuarioActual(), 2)){
                    cout << "No tienes permiso" << endl;
                    Auditoria::registrarEvento("Intento sin permiso: ver registros por " + Usuarios::getUsuarioActual());
                    break;
                }
            Almacenamiento::listarRegistros();
            break;

            break;

            case 3: 
            if (!Permisos::tienePermiso(Usuarios::getUsuarioActual(), 3)){
                    cout << "No tienes permiso" << endl;
                    Auditoria::registrarEvento("Intento sin permiso: registrar evento por " + Usuarios::getUsuarioActual());
                    break;
                }
                cout << "Ingrese mensaje para auditoria: ";
                getline(cin, comando);

                Auditoria::registrarEvento("Evento manual: " + comando);
                cout << "Evento registrado";
                break;
                
            case 4:
            cout << "Verificar integridad manualmente " << endl;
            Verificador::verificarIntegridad();
            cout << "Verificacion completa. Revise audit.log" << endl;
            break;

            case 5:
                Verificador::detenerThread();
                cout << "Saliendo del sistema...";
                return 0;

            default:
                cout << "Opcion invalida";
        }
    }

    
}
