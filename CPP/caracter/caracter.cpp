#include <iostream>
#include <vector>
#include "../include/Benchmark.hpp"
#include "../include/Generadores.hpp"

using namespace std;

int main() {
    const int REP = 10;

    imprimirEncabezadoTabla("8.3 CARACTERES - LETRAS O CODIGOS SIMPLES - C++ char");

    ejecutarCaso<char>("Ejemplo base", {'D', 'A', 'C', 'B', 'E'}, REP, true);
    ejecutarCaso<char>("Minimo variado", generarCaracteres(1000), REP);
    ejecutarCaso<char>("Promedio variado", generarCaracteres(10000), REP);
    ejecutarCaso<char>("Maximo variado", generarCaracteres(100000), REP);
    ejecutarCaso<char>("Todos iguales 100000", generarCaracteresIguales(100000), REP);
    ejecutarCaso<char>("ASCII mixto", {'a', 'A', 'z', 'Z', '9', '1', '@', '#'}, REP, true);

    imprimirNotaFinal("Los caracteres se ordenan por su codigo ASCII. Por eso simbolos, numeros, mayusculas y minusculas pueden quedar en un orden distinto al alfabetico tradicional.");

    return 0;
}


/*
g++ -std=c++17 -O2 CPP\caracter\caracter.cpp -o CPP\caracter\caracter.exe
.\CPP\caracter\caracter.exe
*/