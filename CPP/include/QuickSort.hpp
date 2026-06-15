#ifndef QUICKSORT_HPP
#define QUICKSORT_HPP

#include <algorithm>
#include <functional>
#include <vector>

/*
    QuickSort generico para C++.
    - Usa templates para ordenar diferentes tipos de datos.
    - Trabaja sobre una copia del vector original para no modificar la entrada.
    - Permite comparar tipos simples y tambien structs mediante comparadores.
*/

template <typename T>
class QuickSort {
public:
    std::vector<T> ordenar(const std::vector<T>& lista) const {
        return ordenar(lista, std::less<T>());
    }

    template <typename Compare>
    std::vector<T> ordenar(const std::vector<T>& lista, Compare comp) const {
        std::vector<T> resultado = lista;

        if (resultado.size() > 1) {
            quickSort(resultado, 0, static_cast<int>(resultado.size()) - 1, comp);
        }

        return resultado;
    }

private:
    template <typename Compare>
    void quickSort(std::vector<T>& datos, int izquierda, int derecha, Compare comp) const {
        int i = izquierda;
        int j = derecha;
        T pivote = datos[izquierda + (derecha - izquierda) / 2];

        while (i <= j) {
            while (comp(datos[i], pivote)) {
                i++;
            }

            while (comp(pivote, datos[j])) {
                j--;
            }

            if (i <= j) {
                std::iter_swap(datos.begin() + i, datos.begin() + j);
                i++;
                j--;
            }
        }

        if (izquierda < j) {
            quickSort(datos, izquierda, j, comp);
        }

        if (i < derecha) {
            quickSort(datos, i, derecha, comp);
        }
    }
};

#endif
