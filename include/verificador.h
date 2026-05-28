#ifndef VERIFICADOR_H
#define VERIFICADOR_H
#include <thread>
#include <atomic>

namespace Verificador {
    void iniciarThread();
    void detenerThread();
    void verificarIntegridad();
    bool isEjecutando();

}

#endif