#ifndef BENCHMARK_HPP
#define BENCHMARK_HPP

#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <limits>
#include <numeric>
#include <string>
#include <type_traits>
#include <vector>

#include "QuickSort.hpp"

using namespace std;
using namespace chrono;

struct ResultadoBenchmark {
    double minimoMs = 0.0;
    double maximoMs = 0.0;
    double promedioMs = 0.0;
    double memoriaMB = 0.0;
    bool correcto = true;
};

template <typename T>
void imprimirElemento(const T& valor) {
    if constexpr (std::is_same<T, bool>::value) {
        cout << (valor ? "true" : "false");
    } else {
        cout << valor;
    }
}

template <typename T>
void imprimirVectorLimitado(const vector<T>& datos, int limite = 18) {
    cout << "[";

    for (size_t i = 0; i < datos.size() && i < static_cast<size_t>(limite); i++) {
        imprimirElemento(datos[i]);

        if (i + 1 < datos.size() && i + 1 < static_cast<size_t>(limite)) {
            cout << " ";
        }
    }

    if (datos.size() > static_cast<size_t>(limite)) {
        cout << " ...";
    }

    cout << "]";
}

template <typename T, typename Compare>
bool estaOrdenadoCon(const vector<T>& datos, Compare comp) {
    for (size_t i = 1; i < datos.size(); i++) {
        if (comp(datos[i], datos[i - 1])) {
            return false;
        }
    }

    return true;
}

template <typename T>
double memoriaEstimadaMB(const vector<T>& datos) {
    const double MB = 1024.0 * 1024.0;

    if constexpr (std::is_same<T, string>::value) {
        size_t total = 0;
        for (const string& s : datos) {
            total += sizeof(string) + s.capacity() + 1;
        }
        return (total * 2.0) / MB; // original + resultado ordenado
    } else {
        return (datos.size() * sizeof(T) * 2.0) / MB; // original + resultado ordenado
    }
}

template <typename T, typename Compare>
ResultadoBenchmark medirQuickSort(const vector<T>& datos, int repeticiones, Compare comp) {
    ResultadoBenchmark r;
    vector<double> tiempos;
    tiempos.reserve(repeticiones);

    QuickSort<T> quickSort;

    for (int i = 0; i < repeticiones; i++) {
        auto inicio = high_resolution_clock::now();
        vector<T> ordenados = quickSort.ordenar(datos, comp);
        auto fin = high_resolution_clock::now();

        double tiempoMs = duration<double, milli>(fin - inicio).count();
        tiempos.push_back(tiempoMs);

        if (!estaOrdenadoCon(ordenados, comp)) {
            r.correcto = false;
        }
    }

    r.minimoMs = *min_element(tiempos.begin(), tiempos.end());
    r.maximoMs = *max_element(tiempos.begin(), tiempos.end());
    r.promedioMs = accumulate(tiempos.begin(), tiempos.end(), 0.0) / tiempos.size();
    r.memoriaMB = memoriaEstimadaMB(datos);

    return r;
}

template <typename T>
ResultadoBenchmark medirQuickSort(const vector<T>& datos, int repeticiones) {
    return medirQuickSort(datos, repeticiones, std::less<T>());
}

inline void imprimirEncabezadoTabla(const string& titulo) {
    cout << "\n==============================================================" << endl;
    cout << titulo << endl;
    cout << "==============================================================" << endl;
    cout << left
         << setw(32) << "Caso"
         << right
         << setw(12) << "Cantidad"
         << setw(14) << "Min(ms)"
         << setw(14) << "Max(ms)"
         << setw(14) << "Prom(ms)"
         << setw(14) << "Mem(MB)"
         << setw(12) << "Correcto" << endl;
    cout << string(112, '-') << endl;
}

inline void imprimirFila(const string& caso, size_t cantidad, const ResultadoBenchmark& r) {
    cout << left << setw(32) << caso
         << right << setw(12) << cantidad
         << setw(14) << fixed << setprecision(3) << r.minimoMs
         << setw(14) << fixed << setprecision(3) << r.maximoMs
         << setw(14) << fixed << setprecision(3) << r.promedioMs
         << setw(14) << fixed << setprecision(3) << r.memoriaMB
         << setw(12) << (r.correcto ? "SI" : "NO") << endl;
}

template <typename T, typename Compare>
void ejecutarCaso(const string& caso, const vector<T>& datos, int repeticiones, Compare comp, bool mostrarEjemplo = false) {
    ResultadoBenchmark r = medirQuickSort(datos, repeticiones, comp);
    imprimirFila(caso, datos.size(), r);

    if (mostrarEjemplo) {
        QuickSort<T> quickSort;
        vector<T> ordenados = quickSort.ordenar(datos, comp);

        cout << "   Original: ";
        imprimirVectorLimitado(datos);
        cout << endl;

        cout << "   Ordenado: ";
        imprimirVectorLimitado(ordenados);
        cout << endl;
    }
}

template <typename T>
void ejecutarCaso(const string& caso, const vector<T>& datos, int repeticiones, bool mostrarEjemplo = false) {
    ejecutarCaso(caso, datos, repeticiones, std::less<T>(), mostrarEjemplo);
}

inline void imprimirNotaFinal(const string& observacion) {
    cout << "\nObservacion: " << observacion << endl;
    cout << "Repeticiones por caso: 10" << endl;
    cout << "Memoria: estimacion de datos original + resultado ordenado, expresada en MB." << endl;
}

#endif
