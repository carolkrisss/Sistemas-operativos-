#include <iostream> 
#include <string> 
#include <limits>
#include "../include/seguridad.h"
#include "../include/auditoria.h"

using namespace std;

void mostrarMenu(){
    cout << "1.Procesar comando   ";
    cout << "2.Registrar evento manual   ";
    cout << "3.Salir   \n";
    cout << "Selecciona una opcion:  ";
}
int main() {
    int opcion;
    string comando; 
    
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

                    Auditoria::registrarEvento("Comando procesado: " + comando);
                }
                break;

            case 2: 
                cout << "Ingrese mensaje para auditoria: ";
                getline(cin, comando);

                Auditoria::registrarEvento("Evento manual: " + comando);
                cout << "Evento registrado";
                break;
                

            case 3:
                cout << "Saliendo del sistema...";
                return 0;

            default:
                cout << "Opcion invalida";
        }
    }

    
}
