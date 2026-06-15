# Implementación de Quick Sort en C++

## 1. Planteamiento del problema

El problema consiste en implementar el algoritmo **Quick Sort** en el lenguaje de programación **C++**, aplicándolo a diferentes tipos de datos para demostrar la capacidad del lenguaje de trabajar con programación genérica, clases y polimorfismo.

Quick Sort es un algoritmo de ordenamiento basado en la técnica **divide y vencerás**. Su funcionamiento consiste en seleccionar un elemento llamado **pivote**, separar los datos en tres grupos: menores, iguales y mayores al pivote, y luego ordenar recursivamente los grupos menores y mayores.

El objetivo principal es resolver el mismo problema de ordenamiento para distintos tipos de datos:

* Enteros
* Decimales
* Cadenas
* Caracteres
* Booleanos
* Prueba combinada con varios tipos

De esta manera, se demuestra que en C++ se puede reutilizar el mismo algoritmo utilizando `template <typename T>`, evitando repetir la lógica de Quick Sort para cada tipo de dato.

## 2. tipos de datos acepta

El algoritmo acepta cualquier tipo de dato que pueda compararse usando los operadores `<`, `>` y `==`.

| Tipo de dato | ¿Acepta? | Ejemplo                  |
| ------------ | -------- | ------------------------ |
| `int`        | Sí       | `8 3 1 7 0`              |
| `double`     | Sí       | `2.5 1.1 8.7`            |
| `string`     | Sí       | `"rust" "cpp" "haskell"` |
| `char`       | Sí       | `'z' 'a' 'm'`            |
| `bool`       | Sí       | `true false true`        |

No acepta directamente tipos personalizados si no tienen definidos los operadores de comparación.

## 3. Cómo ejecutar desde la terminal

Primero se debe abrir una terminal en la raíz del proyecto:

Compilar:

    cd "D:...\Articulo.codigo"