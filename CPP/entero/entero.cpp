#include <iostream>
#include <vector>

#include "../include/Utilidades.hpp"

using namespace std;

vector<int> generarAleatorios(int n) {
    vector<int> datos;
    long long semilla = 123456789;

    for (int i = 0; i < n; i++) {
        semilla = (semilla * 1103515245 + 12345) % 2147483648;
        int numero = (int)(semilla % 2000000) - 1000000;
        datos.push_back(numero);
    }

    return datos;
}

vector<int> generarOrdenado(int n) {
    vector<int> datos;

    for (int i = 1; i <= n; i++) {
        datos.push_back(i);
    }

    return datos;
}

vector<int> generarInverso(int n) {
    vector<int> datos;

    for (int i = n; i >= 1; i--) {
        datos.push_back(i);
    }

    return datos;
}

vector<int> generarTodosIguales(int n) {
    return vector<int>(n, 7);
}

vector<int> generarPeorCasoCentro(int n) {
    vector<int> datos(n);
    vector<int> posiciones;

    for (int i = 0; i < n; i++) {
        posiciones.push_back(i);
    }

    int valor = 1;

    while (!posiciones.empty()) {
        int medio = posiciones.size() / 2;
        int posicionReal = posiciones[medio];

        datos[posicionReal] = valor;
        valor++;

        posiciones.erase(posiciones.begin() + medio);
    }

    return datos;
}

int main() {
    cout << "=============================================" << endl;
    cout << "QUICK SORT EN C++ - TIPO ENTERO" << endl;
    cout << "=============================================" << endl;

    ejecutarPrueba<int>("Sencillo", {8, 3, 1, 7, 0, 10, 2});
    ejecutarPrueba<int>("Ya ordenado pequeno", {1, 2, 3, 4, 5});
    ejecutarPrueba<int>("Orden inverso pequeno", {5, 4, 3, 2, 1});
    ejecutarPrueba<int>("Negativos y positivos", {3, -1, -7, 8, 0, -2, 5});
    ejecutarPrueba<int>("Repetidos", {5, 3, 8, 5, 2, 5, 1, 3});
    ejecutarPrueba<int>("Todos iguales pequeno", {7, 7, 7, 7, 7});
    ejecutarPrueba<int>("Valores grandes", {1000000, -1000000, 500, 0, 999999});

    ejecutarPrueba<int>("Aleatorio 1000", generarAleatorios(1000), false);
    ejecutarPrueba<int>("Aleatorio 10000", generarAleatorios(10000), false);
    ejecutarPrueba<int>("Ordenado 10000", generarOrdenado(10000), false);
    ejecutarPrueba<int>("Inverso 10000", generarInverso(10000), false);
    ejecutarPrueba<int>("Todos iguales 10000", generarTodosIguales(10000), false);
    ejecutarPrueba<int>("Peor caso aproximado 5000", generarPeorCasoCentro(5000), false);

    return 0;
}

/*
g++ -std=c++17 -O2 CPP\entero\entero.cpp -o CPP\entero\entero.exe
.\CPP\entero\entero.exe
*/
