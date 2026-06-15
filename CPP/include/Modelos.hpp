#ifndef MODELOS_HPP
#define MODELOS_HPP

#include <string>
#include <vector>

using namespace std;

struct Estudiante {
    string nombre;
    int nota;
    double promedio;
    char paralelo;
    bool aprobado;
    string fecha;
};

inline ostream& operator<<(ostream& os, const Estudiante& e) {
    os << "{" << e.nombre
       << ", nota=" << e.nota
       << ", prom=" << e.promedio
       << ", par=" << e.paralelo
       << ", ap=" << (e.aprobado ? "true" : "false")
       << ", fecha=" << e.fecha << "}";
    return os;
}

inline vector<Estudiante> generarEstudiantes(int n) {
    vector<Estudiante> datos;
    datos.reserve(n);

    vector<string> nombres = {"Carlos", "Ana", "Pedro", "Luis", "Maria", "Jose", "Lucia", "Rosa", "Miguel", "Sofia"};
    char paralelos[] = {'A', 'B', 'C', 'D'};

    for (int i = n; i >= 1; i--) {
        Estudiante e;
        e.nombre = nombres[i % nombres.size()] + "_" + to_string(i);
        e.nota = (i * 37) % 101;
        e.promedio = 30.0 + ((i * 7919) % 7000) / 100.0;
        e.paralelo = paralelos[i % 4];
        e.aprobado = e.nota >= 51;

        int anio = 2020 + (i % 7);
        int mes = 1 + (i % 12);
        int dia = 1 + (i % 28);
        e.fecha = to_string(anio) + "-" + (mes < 10 ? "0" : "") + to_string(mes) + "-" + (dia < 10 ? "0" : "") + to_string(dia);

        datos.push_back(e);
    }

    return datos;
}

#endif
