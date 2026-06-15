#include <iostream>
#include <string>
#include <vector>
#include "../include/Benchmark.hpp"
#include "../include/Generadores.hpp"

using namespace std;

int main() {
    const int REP = 10;

    imprimirEncabezadoTabla("8.6 FECHAS - REGISTROS CRONOLOGICOS - C++ string YYYY-MM-DD");

    ejecutarCaso<string>("Ejemplo base", {"2026-06-10", "2026-01-05", "2026-03-20"}, REP, true);
    ejecutarCaso<string>("Minimo fechas", generarFechas(1000), REP);
    ejecutarCaso<string>("Promedio fechas", generarFechas(10000), REP);
    ejecutarCaso<string>("Maximo fechas", generarFechas(100000), REP);

    imprimirNotaFinal("Las fechas se representan como string con formato YYYY-MM-DD. En este formato, el orden lexicografico coincide con el orden cronologico.");

    return 0;
}


/*
g++ -std=c++17 -O2 CPP\fechas\fechas.cpp -o CPP\fechas\fechas.exe
.\CPP\fechas\fechas.exe
*/