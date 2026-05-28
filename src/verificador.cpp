#include "../include/verificador.h"
#include "../include/seguridad.h"
#include "../include/auditoria.h"
#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <cstring>
#include <string.h>

namespace Verificador{
    static std::thread hiloVerificador;
    static std::atomic<bool> ejecutando(false);

    struct RegistroVerificar{
        char usuario[50];
        char comandoOriginal[200];
        char comandoHex[400];
        char hash[100];
        long timestamp;
    };

    void verificarIntegridad(){
        std::ifstream file("data/registros.bin", std::ios::binary);

        if (!file.is_open()){
            return;
        }

        RegistroVerificar reg;
        int registroNum = 0;


        while (file.read(reinterpret_cast<char*>(&reg), sizeof(RegistroVerificar))){
            registroNum++;

            std::string hexActual(reg.comandoHex);
            std::string hashRecalculado = Seguridad::generarHash(hexActual);
            std::string hashGuardado(reg.hash);


            if(hashRecalculado != hashGuardado){
                std::string alerta = "ALERTA: Registro " + std::to_string(registroNum) 
                                    + " ha sido alterado. Usuario " + std::string(reg.usuario) 
                                    + " Comando:  " + std::string(reg.comandoOriginal);

                std::cout << "\n*** " << alerta << "\n*** " << std::endl;
                Auditoria::registrarEvento(alerta);
            }
        }

        file.close();
    }

    void funcionThread(){
        while (ejecutando){
            std::this_thread::sleep_for(std::chrono::seconds(15));
            if(ejecutando){
                verificarIntegridad;
            }
        }
    }


    void iniciarThread(){
        if (!ejecutando){
            ejecutando = true;
            hiloVerificador = std::thread(funcionThread);
            Auditoria::registrarEvento("Thread verificador iniciado");
            std::cout << "Thread verificador iniciado(cada 15 segundos)" << std::endl;
        }
    }

    void detenerThread(){
        ejecutando = false;
        if (hiloVerificador.joinable()){
            hiloVerificador.join();
        }
         Auditoria::registrarEvento("Thread detenido");
        
    }

    bool isEjecutando(){
        return ejecutando;
    }
}