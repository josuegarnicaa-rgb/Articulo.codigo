#include <iostream>
#include <vector>
#include "../include/Benchmark.hpp"
#include "../include/Generadores.hpp"

using namespace std;

int main() {
    const int REP = 10;

    imprimirEncabezadoTabla("8.8 RELEVANCIA - RESULTADOS DE BUSQUEDA - C++ double");

    ejecutarCaso<double>("Ejemplo ascendente", {0.45, 0.90, 0.30, 0.75}, REP, true);
    ejecutarCaso<double>("Minimo relevancia", generarRelevancia(1000), REP);
    ejecutarCaso<double>("Promedio relevancia", generarRelevancia(10000), REP);
    ejecutarCaso<double>("Maximo relevancia", generarRelevancia(100000), REP);

    auto mayorAMenor = [](double a, double b) { return a > b; };
    ejecutarCaso<double>("Descendente ejemplo", {0.45, 0.90, 0.30, 0.75}, REP, mayorAMenor, true);

    imprimirNotaFinal("Los puntajes de relevancia se comparan como decimales entre 0 y 1. Tambien se prueba orden descendente usando comparador.");

    return 0;
}


/*
g++ -std=c++17 -O2 CPP\relevancia\relevancia.cpp -o CPP\relevancia\relevancia.exe
.\CPP\relevancia\relevancia.exe
*/