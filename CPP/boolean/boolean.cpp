#include <iostream>
#include <vector>

#include "../include/Utilidades.hpp"

using namespace std;

vector<bool> generarBooleanosAlternados(int n) {
    vector<bool> datos;

    for (int i = 0; i < n; i++) {
        datos.push_back(i % 2 == 0);
    }

    return datos;
}

vector<bool> generarBooleanosIgualesTrue(int n) {
    return vector<bool>(n, true);
}

vector<bool> generarBooleanosIgualesFalse(int n) {
    return vector<bool>(n, false);
}

int main() {
    cout << "=============================================" << endl;
    cout << "QUICK SORT EN C++ - TIPO BOOLEANO" << endl;
    cout << "=============================================" << endl;

    ejecutarPrueba<bool>("Sencillo", {true, false, true, false});
    ejecutarPrueba<bool>("Todos true", {true, true, true});
    ejecutarPrueba<bool>("Todos false", {false, false, false});
    ejecutarPrueba<bool>("Un solo valor", {true});
    ejecutarPrueba<bool>("Alternado", {true, false, true, false, true, false});
    ejecutarPrueba<bool>("Mas false que true", {false, true, false, false, true});
    ejecutarPrueba<bool>("Mas true que false", {true, true, false, true, false});

    ejecutarPrueba<bool>("Booleanos alternados 10000", generarBooleanosAlternados(10000), false);
    ejecutarPrueba<bool>("Todos true 10000", generarBooleanosIgualesTrue(10000), false);
    ejecutarPrueba<bool>("Todos false 10000", generarBooleanosIgualesFalse(10000), false);

    return 0;
}

/*
g++ -std=c++17 -O2 CPP\boolean\boolean.cpp -o CPP\boolean\boolean.exe
.\CPP\boolean\boolean.exe
*/