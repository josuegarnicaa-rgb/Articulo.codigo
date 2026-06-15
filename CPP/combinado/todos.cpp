/*
    Prueba combinada de Quick Sort en C++.
    Ejecuta enteros, decimales, cadenas, caracteres y booleanos
    en una sola ejecucion y mide un solo tiempo total.
*/

#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <iomanip>

#include "../include/QuickSort.hpp"
#include "../include/Utilidades.hpp"

using namespace std;
using namespace chrono;

template <typename T>
vector<T> ordenarDatos(const vector<T>& datos) {
    QuickSort<T> quickSort;
    return quickSort.ordenar(datos);
}

int main() {
    vector<int> enteros = {8, 3, 1, 7, 0, 10, 2, -5, 1000000, -1000000};
    vector<double> decimales = {2.5, 1.1, 8.7, 3.3, 0.5, -4.2, 1000000.5, -999999.9};
    vector<string> cadenas = {"rust", "cpp", "haskell", "python", "java", "Rust", "Cpp"};
    vector<char> caracteres = {'z', 'a', 'm', 'b', 'x', 'c', 'A', 'Z', '1', '@'};
    vector<bool> booleanos = {true, false, true, false, true, false};

    cout << "=============================================" << endl;
    cout << "PRUEBA COMBINADA DE QUICK SORT EN C++" << endl;
    cout << "=============================================" << endl;

    auto inicioTotal = high_resolution_clock::now();

    vector<int> enterosOrdenados = ordenarDatos(enteros);
    vector<double> decimalesOrdenados = ordenarDatos(decimales);
    vector<string> cadenasOrdenadas = ordenarDatos(cadenas);
    vector<char> caracteresOrdenados = ordenarDatos(caracteres);
    vector<bool> booleanosOrdenados = ordenarDatos(booleanos);

    auto finTotal = high_resolution_clock::now();

    double tiempoTotalMs = duration<double, milli>(finTotal - inicioTotal).count();

    cout << "\nEnteros originales: ";
    imprimirVectorLimitado(enteros);
    cout << "\nEnteros ordenados: ";
    imprimirVectorLimitado(enterosOrdenados);

    cout << "\n\nDecimales originales: ";
    imprimirVectorLimitado(decimales);
    cout << "\nDecimales ordenados: ";
    imprimirVectorLimitado(decimalesOrdenados);

    cout << "\n\nCadenas originales: ";
    imprimirVectorLimitado(cadenas);
    cout << "\nCadenas ordenadas: ";
    imprimirVectorLimitado(cadenasOrdenadas);

    cout << "\n\nCaracteres originales: ";
    imprimirVectorLimitado(caracteres);
    cout << "\nCaracteres ordenados: ";
    imprimirVectorLimitado(caracteresOrdenados);

    cout << "\n\nBooleanos originales: ";
    imprimirVectorLimitado(booleanos);
    cout << "\nBooleanos ordenados: ";
    imprimirVectorLimitado(booleanosOrdenados);

    cout << "\n\n=============================================" << endl;
    cout << fixed << setprecision(3);
    cout << "Tiempo total combinado: " << tiempoTotalMs << " ms" << endl;
    cout << "=============================================" << endl;

    return 0;
}

/*
g++ -std=c++17 -O2 CPP\combinado\todos.cpp -o CPP\combinado\todos.exe
.\CPP\combinado\todos.exe
*/