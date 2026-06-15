#include <iostream>
#include <vector>
#include <string>

#include "../include/Utilidades.hpp"

using namespace std;

vector<string> generarCadenas(int n) {
    vector<string> datos;

    for (int i = n; i >= 1; i--) {
        datos.push_back("dato" + to_string(i));
    }

    return datos;
}

vector<string> generarCadenasLargas(int n) {
    vector<string> datos;

    for (int i = n; i >= 1; i--) {
        datos.push_back("palabra_larga_de_prueba_numero_" + to_string(i));
    }

    return datos;
}

vector<string> generarCadenasRepetidas(int n) {
    vector<string> base = {"rust", "cpp", "haskell", "java", "python"};
    vector<string> datos;

    for (int i = 0; i < n; i++) {
        datos.push_back(base[i % base.size()]);
    }

    return datos;
}

int main() {
    cout << "=============================================" << endl;
    cout << "QUICK SORT EN C++ - TIPO CADENA" << endl;
    cout << "=============================================" << endl;

    ejecutarPrueba<string>("Sencillo", {"rust", "cpp", "haskell", "python", "java"});
    ejecutarPrueba<string>("Ya ordenado", {"ana", "beto", "carlos", "diego"});
    ejecutarPrueba<string>("Orden inverso", {"zorro", "perro", "gato", "casa"});
    ejecutarPrueba<string>("Repetidos", {"java", "rust", "java", "cpp", "rust"});
    ejecutarPrueba<string>("Mayusculas y minusculas", {"Rust", "rust", "Cpp", "cpp", "Haskell", "haskell"});
    ejecutarPrueba<string>("Palabras cortas y largas", {"a", "algoritmo", "quicksort", "orden", "lenguaje"});
    ejecutarPrueba<string>("Numeros como texto", {"dato10", "dato2", "dato1", "dato20"});

    ejecutarPrueba<string>("Cadenas 1000 en orden inverso", generarCadenas(1000), false);
    ejecutarPrueba<string>("Cadenas largas 1000", generarCadenasLargas(1000), false);
    ejecutarPrueba<string>("Cadenas repetidas 10000", generarCadenasRepetidas(10000), false);

    return 0;
}

/*
g++ -std=c++17 -O2 CPP\cadenas\cadena.cpp -o CPP\cadenas\cadena.exe
.\CPP\cadenas\cadena.exe
*/