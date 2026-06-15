#include <iostream>
#include <string>
#include <vector>
#include "../include/Benchmark.hpp"
#include "../include/Modelos.hpp"

using namespace std;

// Estimacion especifica para registros con strings.
double memoriaEstimadaEstudiantesMB(const vector<Estudiante>& datos) {
    const double MB = 1024.0 * 1024.0;
    size_t total = 0;

    for (const Estudiante& e : datos) {
        total += sizeof(Estudiante);
        total += e.nombre.capacity() + 1;
        total += e.fecha.capacity() + 1;
    }

    return (total * 2.0) / MB;
}

template <typename Compare>
void ejecutarCasoEstudiante(const string& caso, const vector<Estudiante>& datos, int repeticiones, Compare comp, bool mostrarEjemplo = false) {
    ResultadoBenchmark r = medirQuickSort(datos, repeticiones, comp);
    r.memoriaMB = memoriaEstimadaEstudiantesMB(datos);
    imprimirFila(caso, datos.size(), r);

    if (mostrarEjemplo) {
        QuickSort<Estudiante> quickSort;
        vector<Estudiante> ordenados = quickSort.ordenar(datos, comp);

        cout << "   Original: ";
        imprimirVectorLimitado(datos, 3);
        cout << endl;

        cout << "   Ordenado: ";
        imprimirVectorLimitado(ordenados, 3);
        cout << endl;
    }
}

int main() {
    const int REP = 10;

    imprimirEncabezadoTabla("8.10 REGISTROS COMBINADOS - struct Estudiante - C++");

    vector<Estudiante> ejemplo = {
        {"Carlos", 85, 80.5, 'B', true, "2026-06-10"},
        {"Ana", 95, 91.2, 'A', true, "2026-05-20"},
        {"Pedro", 60, 65.8, 'C', false, "2026-04-15"}
    };

    auto porNombre = [](const Estudiante& a, const Estudiante& b) { return a.nombre < b.nombre; };
    auto porNota = [](const Estudiante& a, const Estudiante& b) { return a.nota < b.nota; };
    auto porPromedio = [](const Estudiante& a, const Estudiante& b) { return a.promedio < b.promedio; };
    auto porParalelo = [](const Estudiante& a, const Estudiante& b) { return a.paralelo < b.paralelo; };
    auto porAprobado = [](const Estudiante& a, const Estudiante& b) { return a.aprobado < b.aprobado; };
    auto porFecha = [](const Estudiante& a, const Estudiante& b) { return a.fecha < b.fecha; };

    ejecutarCasoEstudiante("Ejemplo por nombre", ejemplo, REP, porNombre, true);

    vector<Estudiante> datos1000 = generarEstudiantes(1000);
    vector<Estudiante> datos10000 = generarEstudiantes(10000);
    vector<Estudiante> datos100000 = generarEstudiantes(100000);

    ejecutarCasoEstudiante("Minimo por nombre", datos1000, REP, porNombre);
    ejecutarCasoEstudiante("Promedio por nombre", datos10000, REP, porNombre);
    ejecutarCasoEstudiante("Maximo por nombre", datos100000, REP, porNombre);

    ejecutarCasoEstudiante("Maximo por nota", datos100000, REP, porNota);
    ejecutarCasoEstudiante("Maximo por promedio", datos100000, REP, porPromedio);
    ejecutarCasoEstudiante("Maximo por paralelo", datos100000, REP, porParalelo);
    ejecutarCasoEstudiante("Maximo por aprobado", datos100000, REP, porAprobado);
    ejecutarCasoEstudiante("Maximo por fecha", datos100000, REP, porFecha);

    imprimirNotaFinal("El registro combinado usa struct y permite ordenar por diferentes campos. Este caso aumenta la longitud del codigo y la memoria por usar strings y varios atributos.");

    return 0;
}

/*
g++ -std=c++17 -O2 CPP\combinado\todos.cpp -o CPP\combinado\todos.exe
.\CPP\combinado\todos.exe
*/