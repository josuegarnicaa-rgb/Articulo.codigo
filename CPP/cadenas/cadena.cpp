#include <iostream>
#include <string>
#include <vector>
#include "../include/Benchmark.hpp"
#include "../include/Generadores.hpp"

using namespace std;

int main() {
    const int REP = 10;

    imprimirEncabezadoTabla("8.4 CADENAS - NOMBRES ALFABETICAMENTE - C++ string");

    ejecutarCaso<string>("Ejemplo base", {"Carlos", "Ana", "Pedro", "Luis"}, REP, true);
    ejecutarCaso<string>("Minimo nombres", generarNombres(1000), REP);
    ejecutarCaso<string>("Promedio nombres", generarNombres(10000), REP);
    ejecutarCaso<string>("Maximo nombres", generarNombres(100000), REP);
    ejecutarCaso<string>("Nombres largos 10000", generarNombresLargos(10000), REP);
    ejecutarCaso<string>("Lexicografico", {"dato10", "dato2", "dato1", "dato20"}, REP, true);
    ejecutarCaso<string>("Mayusculas/minusculas", {"Rust", "rust", "Cpp", "cpp", "Haskell", "haskell"}, REP, true);

    imprimirNotaFinal("Las cadenas requieren comparar caracter por caracter. El orden es lexicografico: dato10 puede quedar antes que dato2, y las mayusculas pueden ordenarse antes que las minusculas.");

    return 0;
}


/*
g++ -std=c++17 -O2 CPP\cadenas\cadena.cpp -o CPP\cadenas\cadena.exe
.\CPP\cadenas\cadena.exe
*/