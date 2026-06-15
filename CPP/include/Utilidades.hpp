#ifndef UTILIDADES_HPP
#define UTILIDADES_HPP

#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <type_traits>
#include <string>

#include "QuickSort.hpp"

using namespace std;
using namespace chrono;

template <typename T>
void imprimirElemento(const T& valor) {
    if constexpr (std::is_same<T, bool>::value) {
        cout << (valor ? "true" : "false");
    } else {
        cout << valor;
    }
}

template <typename T>
void imprimirVectorLimitado(const vector<T>& datos, int limite = 25) {
    int cantidad = datos.size();

    cout << "[";

    for (int i = 0; i < cantidad && i < limite; i++) {
        imprimirElemento(datos[i]);

        if (i < cantidad - 1 && i < limite - 1) {
            cout << " ";
        }
    }

    if (cantidad > limite) {
        cout << " ...";
    }

    cout << "]";
}

template <typename T>
bool estaOrdenado(const vector<T>& datos) {
    for (size_t i = 1; i < datos.size(); i++) {
        if (datos[i] < datos[i - 1]) {
            return false;
        }
    }

    return true;
}

template <typename T>
void ejecutarPrueba(const string& nombrePrueba, const vector<T>& datos, bool mostrarDatos = true) {
    QuickSort<T> quickSort;

    auto inicio = high_resolution_clock::now();
    vector<T> ordenados = quickSort.ordenar(datos);
    auto fin = high_resolution_clock::now();

    double tiempoMs = duration<double, milli>(fin - inicio).count();

    cout << "\n---------------------------------------------" << endl;
    cout << "Prueba: " << nombrePrueba << endl;
    cout << "Cantidad de datos: " << datos.size() << endl;

    if (mostrarDatos) {
        cout << "Original: ";
        imprimirVectorLimitado(datos);
        cout << endl;

        cout << "Ordenado: ";
        imprimirVectorLimitado(ordenados);
        cout << endl;
    } else {
        cout << "Original: ";
        imprimirVectorLimitado(datos);
        cout << endl;

        cout << "Ordenado: ";
        imprimirVectorLimitado(ordenados);
        cout << endl;
    }

    cout << "Correcto: " << (estaOrdenado(ordenados) ? "SI" : "NO") << endl;

    cout << fixed << setprecision(3);
    cout << "Tiempo: " << tiempoMs << " ms" << endl;
}

#endif