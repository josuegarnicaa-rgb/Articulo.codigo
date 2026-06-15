#include <iostream>
#include <vector>
#include "../include/Benchmark.hpp"
#include "../include/Generadores.hpp"

using namespace std;

int main() {
    const int REP = 10;

    imprimirEncabezadoTabla("8.9 TIEMPOS DE CARRERA - SEGUNDOS - C++ double");

    ejecutarCaso<double>("Ejemplo base", {12.5, 10.8, 14.2, 11.1}, REP, true);
    ejecutarCaso<double>("Minimo tiempos", generarTiemposCarrera(1000), REP);
    ejecutarCaso<double>("Promedio tiempos", generarTiemposCarrera(10000), REP);
    ejecutarCaso<double>("Maximo tiempos", generarTiemposCarrera(100000), REP);

    imprimirNotaFinal("Los tiempos de carrera son decimales. La comparacion es similar a precios, pero el contexto representa segundos.");

    return 0;
}


/*
g++ -std=c++17 -O2 CPP\tiempos\tiempos.cpp -o CPP\tiempos\tiempos.exe
.\CPP\tiempos\tiempos.exe
*/