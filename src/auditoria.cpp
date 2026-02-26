#include "../include/auditoria.h"
#include <fstream>
#include <ctime>
#include <iomanip>

namespace Auditoria {
    void registrarEvento(const std::string& mensaje){

        std::ofstream logFile("data/audit.log", std::ios::app);

         if (!logFile.is_open()){
            return;            
         }
         std::time_t now = std::time(nullptr);

         logFile << std::put_time(std::localtime(&now), "%Y-%m-%d %H:%M:%S")
                 << " - " << mensaje << std::endl;
        logFile.close();
    }

   
}