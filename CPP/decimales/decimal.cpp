#include <iostream>
#include <vector>
#include "../include/Benchmark.hpp"
#include "../include/Generadores.hpp"

using namespace std;

int main() {
    const int REP = 10;

    imprimirEncabezadoTabla("8.2 DECIMALES - PRECIOS DE PRODUCTOS - C++ double");

    ejecutarCaso<double>("Ejemplo base", {120.50, 50.99, 300.75, 80.20, 20.10}, REP, true);
    ejecutarCaso<double>("Minimo aleatorio", generarPrecios(1000), REP);
    ejecutarCaso<double>("Promedio aleatorio", generarPrecios(10000), REP);
    ejecutarCaso<double>("Maximo aleatorio", generarPrecios(100000), REP);
    ejecutarCaso<double>("Repetidos 100000", generarDecimalesRepetidos(100000), REP);
    ejecutarCaso<double>("Valores extremos", {1000000.50, -999999.90, 0.01, 99999.99, 20.20}, REP, true);

    imprimirNotaFinal("Los decimales consumen mas memoria que int. El ordenamiento es correcto, pero la comparacion puede mostrar mas costo que los enteros.");

    return 0;
}

/*
g++ -std=c++17 -O2 CPP\decimales\decimal.cpp -o CPP\decimales\decimal.exe
.\CPP\decimales\decimal.exe
*/