#include <iostream>
#include <vector>
#include "../include/Utilidades.hpp"

using namespace std;

vector<double> generarDecimalesAleatorios(int n) {
    vector<double> datos;
    long long semilla = 987654321;

    for (int i = 0; i < n; i++) {
        semilla = (semilla * 1103515245 + 12345) % 2147483648;
        double numero = ((double)(semilla % 2000000) - 1000000) / 100.0;
        datos.push_back(numero);
    }

    return datos;
}

vector<double> generarDecimalesInversos(int n) {
    vector<double> datos;

    for (int i = n; i >= 1; i--) {
        datos.push_back(i + 0.5);
    }

    return datos;
}

vector<double> generarDecimalesIguales(int n) {
    return vector<double>(n, 3.14);
}

int main() {
    cout << "=============================================" << endl;
    cout << "QUICK SORT EN C++ - TIPO DECIMAL" << endl;
    cout << "=============================================" << endl;

    ejecutarPrueba<double>("Sencillo", {2.5, 1.1, 8.7, 3.3, 0.5});
    ejecutarPrueba<double>("Negativos y positivos", {3.5, -1.2, -7.8, 0.0, 2.4});
    ejecutarPrueba<double>("Repetidos", {1.5, 2.5, 1.5, 0.5, 2.5});
    ejecutarPrueba<double>("Decimales pequenos", {0.001, 0.01, -0.5, 0.0});
    ejecutarPrueba<double>("Ya ordenado", {1.1, 2.2, 3.3, 4.4});
    ejecutarPrueba<double>("Orden inverso", {9.9, 7.7, 5.5, 3.3, 1.1});
    ejecutarPrueba<double>("Valores grandes", {1000000.5, -999999.9, 20.2, 0.0});

    ejecutarPrueba<double>("Aleatorio 1000", generarDecimalesAleatorios(1000), false);
    ejecutarPrueba<double>("Aleatorio 10000", generarDecimalesAleatorios(10000), false);
    ejecutarPrueba<double>("Inverso 10000", generarDecimalesInversos(10000), false);
    ejecutarPrueba<double>("Todos iguales 10000", generarDecimalesIguales(10000), false);

    return 0;
}
/*
g++ -std=c++17 -O2 CPP\decimales\decimal.cpp -o CPP\decimales\decimal.exe
.\CPP\decimales\decimal.exe
*/