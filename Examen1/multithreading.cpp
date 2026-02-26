#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>
using namespace std;

mutex mtx;

void Archivo(ofstream &archivo, string texto) {
    lock_guard<mutex> lock(mtx);
    archivo << texto << endl;
}

int main () {
    ofstream archivo("salida.txt");

    if(!archivo.is_open()){
        cout << "error" << endl;
        return 1;
    }
    thread t1(Archivo, ref(archivo), "Mensaje del thread 1");
    thread t2(Archivo, ref(archivo), "Mensaje del thread 2");
    thread t3(Archivo, ref(archivo), "Mensaje del thread 3");
    thread t4(Archivo, ref(archivo), "Mensaje del thread 4");
    thread t5(Archivo, ref(archivo), "Mensaje del thread 5");

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();

    archivo.close();

    cout << "Archivo escrito correctamente" << endl;
    return 0;
    
}