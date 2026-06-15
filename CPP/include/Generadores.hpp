#ifndef GENERADORES_HPP
#define GENERADORES_HPP

#include <string>
#include <vector>

using namespace std;

class GeneradorDeterministico {
private:
    unsigned long long estado;

public:
    explicit GeneradorDeterministico(unsigned long long semilla) : estado(semilla) {}

    unsigned int siguiente() {
        estado = (estado * 1103515245ULL + 12345ULL) % 2147483648ULL;
        return static_cast<unsigned int>(estado);
    }

    int entero(int minimo, int maximo) {
        return minimo + static_cast<int>(siguiente() % (static_cast<unsigned int>(maximo - minimo + 1)));
    }

    long long enteroLargo(long long minimo, long long maximo) {
        unsigned long long a = siguiente();
        unsigned long long b = siguiente();
        unsigned long long combinado = (a << 31) ^ b;
        return minimo + static_cast<long long>(combinado % static_cast<unsigned long long>(maximo - minimo + 1));
    }

    double decimal(double minimo, double maximo) {
        double fraccion = static_cast<double>(siguiente()) / 2147483648.0;
        return minimo + fraccion * (maximo - minimo);
    }
};

inline vector<int> generarNotas(int n, unsigned long long semilla = 123456789ULL) {
    vector<int> datos;
    datos.reserve(n);
    GeneradorDeterministico g(semilla);

    for (int i = 0; i < n; i++) {
        datos.push_back(g.entero(0, 100));
    }

    return datos;
}

inline vector<int> generarNotasOrdenadas(int n) {
    vector<int> datos;
    datos.reserve(n);
    for (int i = 0; i < n; i++) datos.push_back(i % 101);
    return datos;
}

inline vector<int> generarNotasInversas(int n) {
    vector<int> datos;
    datos.reserve(n);
    for (int i = n - 1; i >= 0; i--) datos.push_back(i % 101);
    return datos;
}

inline vector<int> generarNotasRepetidas(int n) {
    vector<int> datos;
    datos.reserve(n);
    int base[] = {51, 51, 70, 70, 70, 85, 85, 100, 100, 100};
    for (int i = 0; i < n; i++) datos.push_back(base[i % 10]);
    return datos;
}

inline vector<int> generarPeorCasoCentroInt(int n) {
    vector<int> datos(n);
    vector<int> posiciones;
    posiciones.reserve(n);

    for (int i = 0; i < n; i++) posiciones.push_back(i);

    int valor = 1;
    while (!posiciones.empty()) {
        int medio = static_cast<int>(posiciones.size() / 2);
        int posicionReal = posiciones[medio];
        datos[posicionReal] = valor++;
        posiciones.erase(posiciones.begin() + medio);
    }

    return datos;
}

inline vector<double> generarPrecios(int n, unsigned long long semilla = 987654321ULL) {
    vector<double> datos;
    datos.reserve(n);
    GeneradorDeterministico g(semilla);

    for (int i = 0; i < n; i++) {
        datos.push_back(g.decimal(1.0, 5000.0));
    }

    return datos;
}

inline vector<double> generarDecimalesRepetidos(int n) {
    vector<double> datos;
    datos.reserve(n);
    double base[] = {10.50, 20.00, 20.00, 99.99, 99.99, 150.75, 150.75, 300.10};
    for (int i = 0; i < n; i++) datos.push_back(base[i % 8]);
    return datos;
}

inline vector<double> generarRelevancia(int n, unsigned long long semilla = 246813579ULL) {
    vector<double> datos;
    datos.reserve(n);
    GeneradorDeterministico g(semilla);

    for (int i = 0; i < n; i++) {
        datos.push_back(g.decimal(0.0, 1.0));
    }

    return datos;
}

inline vector<double> generarTiemposCarrera(int n, unsigned long long semilla = 975318642ULL) {
    vector<double> datos;
    datos.reserve(n);
    GeneradorDeterministico g(semilla);

    for (int i = 0; i < n; i++) {
        datos.push_back(g.decimal(8.0, 300.0));
    }

    return datos;
}

inline vector<char> generarCaracteres(int n) {
    vector<char> datos;
    datos.reserve(n);
    string base = "zYxWvUtSrQpOnMlKjIhGfEdCbA9876543210@#%&";

    for (int i = 0; i < n; i++) {
        datos.push_back(base[i % base.size()]);
    }

    return datos;
}

inline vector<char> generarCaracteresIguales(int n) {
    return vector<char>(n, 'A');
}

inline vector<string> generarNombres(int n) {
    vector<string> datos;
    datos.reserve(n);
    vector<string> base = {"Carlos", "Ana", "Pedro", "Luis", "Maria", "Jose", "Lucia", "Rosa", "Miguel", "Sofia"};

    for (int i = n; i >= 1; i--) {
        datos.push_back(base[i % base.size()] + "_" + to_string(i));
    }

    return datos;
}

inline vector<string> generarNombresLargos(int n) {
    vector<string> datos;
    datos.reserve(n);

    for (int i = n; i >= 1; i--) {
        datos.push_back("Nombre_Largo_De_Estudiante_Para_Prueba_De_QuickSort_" + to_string(i));
    }

    return datos;
}

inline vector<bool> generarBooleanosAlternados(int n) {
    vector<bool> datos;
    datos.reserve(n);

    for (int i = 0; i < n; i++) {
        datos.push_back(i % 2 == 0);
    }

    return datos;
}

inline vector<bool> generarBooleanosRepetidos(int n, bool valor) {
    return vector<bool>(n, valor);
}

inline string fechaDesdeIndice(int indice) {
    int anio = 2020 + (indice % 7);
    int mes = 1 + (indice % 12);
    int dia = 1 + (indice % 28);

    string sAnio = to_string(anio);
    string sMes = (mes < 10 ? "0" : "") + to_string(mes);
    string sDia = (dia < 10 ? "0" : "") + to_string(dia);

    return sAnio + "-" + sMes + "-" + sDia;
}

inline vector<string> generarFechas(int n) {
    vector<string> datos;
    datos.reserve(n);

    for (int i = n; i >= 1; i--) {
        datos.push_back(fechaDesdeIndice(i));
    }

    return datos;
}

inline vector<long long> generarTamaniosArchivo(int n, unsigned long long semilla = 135791357ULL) {
    vector<long long> datos;
    datos.reserve(n);
    GeneradorDeterministico g(semilla);

    for (int i = 0; i < n; i++) {
        datos.push_back(g.enteroLargo(1LL, 5LL * 1024LL * 1024LL * 1024LL)); // hasta 5 GB en bytes
    }

    return datos;
}

#endif
