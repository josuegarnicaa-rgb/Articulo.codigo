#include <iostream>
#include <vector>
#include "../include/Benchmark.hpp"
#include "../include/Generadores.hpp"

using namespace std;

int main() {
    const int REP = 10;

    imprimirEncabezadoTabla("8.1 ENTEROS - NOTAS DE ESTUDIANTES - C++ int");

    ejecutarCaso<int>("Ejemplo base", {65, 90, 45, 78, 100, 82}, REP, true);
    ejecutarCaso<int>("Minimo aleatorio", generarNotas(1000), REP);
    ejecutarCaso<int>("Promedio aleatorio", generarNotas(10000), REP);
    ejecutarCaso<int>("Maximo aleatorio", generarNotas(100000), REP);
    ejecutarCaso<int>("Ordenado 100000", generarNotasOrdenadas(100000), REP);
    ejecutarCaso<int>("Inverso 100000", generarNotasInversas(100000), REP);
    ejecutarCaso<int>("Repetidos 100000", generarNotasRepetidas(100000), REP);
    ejecutarCaso<int>("Peor caso centro 10000", generarPeorCasoCentroInt(10000), REP);

    imprimirNotaFinal("Los enteros son livianos en memoria. El peor caso construido muestra la debilidad del pivote central cuando las particiones quedan desbalanceadas.");

    return 0;
}

/*
g++ -std=c++17 -O2 CPP\entero\entero.cpp -o CPP\entero\entero.exe
.\CPP\entero\entero.exe
*/