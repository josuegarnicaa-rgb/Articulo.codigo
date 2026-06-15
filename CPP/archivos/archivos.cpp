#include <iostream>
#include <vector>
#include "../include/Benchmark.hpp"
#include "../include/Generadores.hpp"

using namespace std;

int main() {
    const int REP = 10;

    imprimirEncabezadoTabla("8.7 ARCHIVOS - TAMANIOS EN BYTES - C++ long long");

    ejecutarCaso<long long>("Ejemplo base", {500, 20, 150, 1000}, REP, true);
    ejecutarCaso<long long>("Minimo tamanios", generarTamaniosArchivo(1000), REP);
    ejecutarCaso<long long>("Promedio tamanios", generarTamaniosArchivo(10000), REP);
    ejecutarCaso<long long>("Maximo tamanios", generarTamaniosArchivo(100000), REP);

    imprimirNotaFinal("Los tamanios de archivo usan long long para soportar numeros grandes. Este caso compara enteros grandes frente a enteros simples.");

    return 0;
}


/*
g++ -std=c++17 -O2 CPP\archivos\archivos.cpp -o CPP\archivos\archivos.exe
.\CPP\archivos\archivos.exe
*/