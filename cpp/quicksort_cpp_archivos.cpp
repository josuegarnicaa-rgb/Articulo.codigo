#include <algorithm>
#include <chrono>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
namespace fs = std::filesystem;

// ================================================================
// QUICKSORT GENERICO CON PARTICION DE 3 VIAS
// ================================================================
// Esta version fue implementada manualmente para el articulo.
// No usa sort() de la libreria estandar.
// Se usa particion de 3 vias para manejar mejor valores repetidos.

template <typename T>
void quickSort(vector<T>& datos, int izquierda, int derecha) {
    if (izquierda >= derecha) return;

    T pivote = datos[izquierda + (derecha - izquierda) / 2];
    int menor = izquierda;
    int actual = izquierda;
    int mayor = derecha;

    while (actual <= mayor) {
        if (datos[actual] < pivote) {
            swap(datos[menor], datos[actual]);
            menor++;
            actual++;
        } else if (pivote < datos[actual]) {
            swap(datos[actual], datos[mayor]);
            mayor--;
        } else {
            actual++;
        }
    }

    quickSort(datos, izquierda, menor - 1);
    quickSort(datos, mayor + 1, derecha);
}

template <typename T>
void ejecutarQuickSort(vector<T>& datos) {
    if (!datos.empty()) {
        quickSort(datos, 0, static_cast<int>(datos.size()) - 1);
    }
}

// ================================================================
// LECTURA DE ARCHIVOS TXT
// ================================================================

vector<string> leerTokens(const string& ruta) {
    ifstream archivo(ruta);
    vector<string> tokens;
    string valor;

    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo: " << ruta << endl;
        return tokens;
    }

    while (archivo >> valor) {
        tokens.push_back(valor);
    }
    return tokens;
}

vector<int> leerEnteros(const string& ruta) {
    vector<string> tokens = leerTokens(ruta);
    vector<int> datos;
    datos.reserve(tokens.size());
    for (const string& t : tokens) datos.push_back(stoi(t));
    return datos;
}

vector<double> leerDecimales(const string& ruta) {
    vector<string> tokens = leerTokens(ruta);
    vector<double> datos;
    datos.reserve(tokens.size());
    for (const string& t : tokens) datos.push_back(stod(t));
    return datos;
}

vector<int> leerBooleanos(const string& ruta) {
    vector<string> tokens = leerTokens(ruta);
    vector<int> datos;
    datos.reserve(tokens.size());
    for (string t : tokens) {
        for (char& c : t) c = static_cast<char>(tolower(c));
        datos.push_back((t == "true" || t == "1") ? 1 : 0);
    }
    return datos;
}

vector<string> leerCadenasOFechas(const string& ruta) {
    return leerTokens(ruta);
}

// ================================================================
// MEDICION
// ================================================================

struct Resultado {
    string lenguaje;
    string archivo;
    string tipo;
    long long cantidad;
    int repeticiones;
    double minimoMs;
    double maximoMs;
    double promedioMs;
    double memoriaMB;
    string correcto;
};

template <typename T>
double estimarMemoriaMB(const vector<T>& datos) {
    return (static_cast<double>(datos.size()) * sizeof(T)) / (1024.0 * 1024.0);
}

double estimarMemoriaMBStrings(const vector<string>& datos) {
    size_t total = datos.size() * sizeof(string);
    for (const auto& s : datos) total += s.size();
    return static_cast<double>(total) / (1024.0 * 1024.0);
}

template <typename T>
Resultado medirCaso(const string& archivo, const string& tipo, const vector<T>& datosOriginales, int repeticiones, double memoriaMB) {
    vector<double> tiempos;
    tiempos.reserve(repeticiones);
    bool correcto = true;

    for (int r = 0; r < repeticiones; r++) {
        vector<T> copia = datosOriginales; // Se mide solo el ordenamiento, no la lectura del archivo.

        auto inicio = chrono::high_resolution_clock::now();
        ejecutarQuickSort(copia);
        auto fin = chrono::high_resolution_clock::now();

        chrono::duration<double, milli> duracion = fin - inicio;
        tiempos.push_back(duracion.count());

        if (!is_sorted(copia.begin(), copia.end())) {
            correcto = false;
        }
    }

    double minimo = *min_element(tiempos.begin(), tiempos.end());
    double maximo = *max_element(tiempos.begin(), tiempos.end());
    double suma = 0.0;
    for (double t : tiempos) suma += t;

    Resultado res;
    res.lenguaje = "C++";
    res.archivo = archivo;
    res.tipo = tipo;
    res.cantidad = static_cast<long long>(datosOriginales.size());
    res.repeticiones = repeticiones;
    res.minimoMs = minimo;
    res.maximoMs = maximo;
    res.promedioMs = suma / repeticiones;
    res.memoriaMB = memoriaMB;
    res.correcto = correcto ? "SI" : "NO";
    return res;
}

int repeticionesPorCantidad(long long cantidad) {
    if (cantidad >= 1000000) return 3;
    return 5;
}

string tipoDesdeArchivo(const string& nombre) {
    if (nombre.rfind("enteros_", 0) == 0) return "Enteros";
    if (nombre.rfind("decimales_", 0) == 0) return "Decimales";
    if (nombre.rfind("cadenas_", 0) == 0) return "Cadenas";
    if (nombre.rfind("booleanos_", 0) == 0) return "Booleanos";
    if (nombre.rfind("fechas_", 0) == 0) return "Fechas";
    return "Desconocido";
}

int ordenTipo(const string& tipo) {
    if (tipo == "Enteros") return 1;
    if (tipo == "Decimales") return 2;
    if (tipo == "Cadenas") return 3;
    if (tipo == "Booleanos") return 4;
    if (tipo == "Fechas") return 5;
    return 99;
}

int ordenTamano(const string& nombre) {
    if (nombre.find("100mil") != string::npos) return 1;
    if (nombre.find("500mil") != string::npos) return 2;
    if (nombre.find("1millon") != string::npos) return 3;
    return 99;
}

void imprimirTabla(const vector<Resultado>& resultados, ostream& out) {
    out << "====================================================================================================================\n";
    out << "PRUEBAS DE QUICKSORT - C++ - LECTURA DESDE ARCHIVOS TXT\n";
    out << "====================================================================================================================\n";
    out << left << setw(24) << "Archivo"
        << setw(12) << "Tipo"
        << right << setw(12) << "Cantidad"
        << setw(8) << "Rep"
        << setw(12) << "Min(ms)"
        << setw(12) << "Max(ms)"
        << setw(12) << "Prom(ms)"
        << setw(12) << "Mem(MB)"
        << setw(12) << "Correcto" << "\n";
    out << string(116, '-') << "\n";

    out << fixed << setprecision(3);
    for (const auto& r : resultados) {
        out << left << setw(24) << r.archivo
            << setw(12) << r.tipo
            << right << setw(12) << r.cantidad
            << setw(8) << r.repeticiones
            << setw(12) << r.minimoMs
            << setw(12) << r.maximoMs
            << setw(12) << r.promedioMs
            << setw(12) << r.memoriaMB
            << setw(12) << r.correcto << "\n";
    }

    out << "\nNota: Mem(MB) es una estimacion del espacio ocupado por los datos cargados en memoria.\n";
    out << "La medicion de tiempo considera el ordenamiento, no la lectura del archivo.\n";
}

void escribirCSV(const vector<Resultado>& resultados, const string& ruta) {
    ofstream csv(ruta);
    csv << "Lenguaje,Archivo,Tipo,Cantidad,Repeticiones,Min_ms,Max_ms,Prom_ms,Mem_MB,Correcto\n";
    csv << fixed << setprecision(3);
    for (const auto& r : resultados) {
        csv << r.lenguaje << ","
            << r.archivo << ","
            << r.tipo << ","
            << r.cantidad << ","
            << r.repeticiones << ","
            << r.minimoMs << ","
            << r.maximoMs << ","
            << r.promedioMs << ","
            << r.memoriaMB << ","
            << r.correcto << "\n";
    }
}

int main() {
    fs::path carpetaDatos = "../datos";
    fs::path carpetaResultados = "../resultados";

    if (!fs::exists(carpetaDatos)) {
        carpetaDatos = "datos";
    }
    if (!fs::exists(carpetaResultados)) {
        carpetaResultados = "resultados";
    }
    fs::create_directories(carpetaResultados);

    vector<fs::path> archivos;
    for (const auto& entrada : fs::directory_iterator(carpetaDatos)) {
        if (entrada.is_regular_file() && entrada.path().extension() == ".txt") {
            archivos.push_back(entrada.path());
        }
    }

    sort(archivos.begin(), archivos.end(), [](const fs::path& a, const fs::path& b) {
        string na = a.filename().string();
        string nb = b.filename().string();
        string ta = tipoDesdeArchivo(na);
        string tb = tipoDesdeArchivo(nb);
        if (ordenTipo(ta) != ordenTipo(tb)) return ordenTipo(ta) < ordenTipo(tb);
        if (ordenTamano(na) != ordenTamano(nb)) return ordenTamano(na) < ordenTamano(nb);
        return na < nb;
    });

    vector<Resultado> resultados;

    for (const auto& ruta : archivos) {
        string nombre = ruta.filename().string();
        string tipo = tipoDesdeArchivo(nombre);
        string rutaStr = ruta.string();

        cout << "Leyendo: " << nombre << " ..." << endl;

        if (tipo == "Enteros") {
            auto datos = leerEnteros(rutaStr);
            resultados.push_back(medirCaso(nombre, tipo, datos, repeticionesPorCantidad(datos.size()), estimarMemoriaMB(datos)));
        } else if (tipo == "Decimales") {
            auto datos = leerDecimales(rutaStr);
            resultados.push_back(medirCaso(nombre, tipo, datos, repeticionesPorCantidad(datos.size()), estimarMemoriaMB(datos)));
        } else if (tipo == "Booleanos") {
            auto datos = leerBooleanos(rutaStr);
            resultados.push_back(medirCaso(nombre, tipo, datos, repeticionesPorCantidad(datos.size()), estimarMemoriaMB(datos)));
        } else if (tipo == "Cadenas" || tipo == "Fechas") {
            auto datos = leerCadenasOFechas(rutaStr);
            resultados.push_back(medirCaso(nombre, tipo, datos, repeticionesPorCantidad(datos.size()), estimarMemoriaMBStrings(datos)));
        }
    }

    cout << "\n";
    imprimirTabla(resultados, cout);

    fs::path rutaTxt = carpetaResultados / "resultado_cpp_archivos.txt";
    fs::path rutaCsv = carpetaResultados / "resultado_cpp_archivos.csv";

    ofstream txt(rutaTxt);
    imprimirTabla(resultados, txt);
    escribirCSV(resultados, rutaCsv.string());

    cout << "\nArchivos creados automaticamente:\n";
    cout << "- " << rutaTxt.string() << "\n";
    cout << "- " << rutaCsv.string() << "\n";

    return 0;
}
