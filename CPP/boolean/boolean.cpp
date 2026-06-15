#include <iostream>
#include <vector>
#include "../include/Benchmark.hpp"
#include "../include/Generadores.hpp"

using namespace std;

int main() {
    const int REP = 10;

    imprimirEncabezadoTabla("8.5 BOOLEANOS - VERDADERO/FALSO - C++ bool");

    ejecutarCaso<bool>("Ejemplo base", {true, false, true, false, true}, REP, true);
    ejecutarCaso<bool>("Minimo alternado", generarBooleanosAlternados(1000), REP);
    ejecutarCaso<bool>("Promedio alternado", generarBooleanosAlternados(10000), REP);
    ejecutarCaso<bool>("Maximo alternado", generarBooleanosAlternados(100000), REP);
    ejecutarCaso<bool>("Todos true 100000", generarBooleanosRepetidos(100000, true), REP);
    ejecutarCaso<bool>("Todos false 100000", generarBooleanosRepetidos(100000, false), REP);

    imprimirNotaFinal("Los booleanos solo tienen dos valores posibles. Este caso sirve para observar el efecto de muchos repetidos; false se ordena antes que true.");

    return 0;
}


/*
g++ -std=c++17 -O2 CPP\boolean\boolean.cpp -o CPP\boolean\boolean.exe
.\CPP\boolean\boolean.exe
*/