#ifndef QUICKSORT_HPP
#define QUICKSORT_HPP

#include <vector>

template <typename T>
class QuickSort {
public:
    std::vector<T> ordenar(const std::vector<T>& lista) {
        if (lista.size() <= 1) {
            return lista;
        }

        T pivote = lista[lista.size() / 2];

        std::vector<T> menores;
        std::vector<T> iguales;
        std::vector<T> mayores;

        for (T elemento : lista) {
            if (elemento < pivote) {
                menores.push_back(elemento);
            } else if (elemento == pivote) {
                iguales.push_back(elemento);
            } else {
                mayores.push_back(elemento);
            }
        }

        std::vector<T> resultado = ordenar(menores);

        resultado.insert(resultado.end(), iguales.begin(), iguales.end());

        std::vector<T> mayoresOrdenados = ordenar(mayores);
        resultado.insert(resultado.end(), mayoresOrdenados.begin(), mayoresOrdenados.end());

        return resultado;
    }
};

#endif