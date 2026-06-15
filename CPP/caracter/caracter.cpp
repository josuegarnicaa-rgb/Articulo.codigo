#include <iostream>
#include <vector>

#include "../include/Utilidades.hpp"

using namespace std;

vector<char> generarCaracteresAleatorios(int n) {
    vector<char> datos;
    string base = "zYxWvUtSrQpOnMlKjIhGfEdCbA9876543210@#%&";

    for (int i = 0; i < n; i++) {
        datos.push_back(base[i % base.size()]);
    }

    return datos;
}

vector<char> generarCaracteresIguales(int n) {
    return vector<char>(n, 'a');
}

int main() {
    cout << "=============================================" << endl;
    cout << "QUICK SORT EN C++ - TIPO CARACTER" << endl;
    cout << "=============================================" << endl;

    ejecutarPrueba<char>("Sencillo", {'z', 'a', 'm', 'b', 'x', 'c'});
    ejecutarPrueba<char>("Ya ordenado", {'a', 'b', 'c', 'd', 'e'});
    ejecutarPrueba<char>("Orden inverso", {'e', 'd', 'c', 'b', 'a'});
    ejecutarPrueba<char>("Repetidos", {'a', 'z', 'a', 'b', 'z', 'c'});
    ejecutarPrueba<char>("Mayusculas y minusculas", {'a', 'A', 'z', 'Z', 'b', 'B'});
    ejecutarPrueba<char>("Digitos como caracteres", {'5', '1', '9', '2', '0'});
    ejecutarPrueba<char>("Simbolos y letras", {'@', '#', 'a', 'Z', '1'});

    ejecutarPrueba<char>("Caracteres variados 1000", generarCaracteresAleatorios(1000), false);
    ejecutarPrueba<char>("Caracteres variados 10000", generarCaracteresAleatorios(10000), false);
    ejecutarPrueba<char>("Todos iguales 10000", generarCaracteresIguales(10000), false);

    return 0;
}

/*
g++ -std=c++17 -O2 CPP\caracter\caracter.cpp -o CPP\caracter\caracter.exe
.\CPP\caracter\caracter.exe
*/