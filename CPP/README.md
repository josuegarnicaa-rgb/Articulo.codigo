# Quick Sort en C++ - Benchmark completo

Esta carpeta contiene la parte de C++ para el articulo de comparacion de Quick Sort en C++, Rust y Haskell.

## Que cumple

- Casos por tipo de dato.
- Cantidades minimas, promedio y maximas: 1.000, 10.000 y 100.000 elementos.
- 10 repeticiones por caso.
- Tiempo minimo, maximo y promedio en milisegundos.
- Memoria estimada en MB.
- Verificacion de resultado correcto.
- Casos especiales: repetidos, orden inverso, peor caso aproximado, cadenas, fechas y registros combinados.

## Tipos incluidos

- Enteros: notas de estudiantes (`int`).
- Decimales: precios de productos (`double`).
- Caracteres: letras o codigos simples (`char`).
- Cadenas: nombres (`string`).
- Booleanos: verdadero/falso (`bool`).
- Fechas: formato `YYYY-MM-DD` como `string`.
- Archivos: tamanios en bytes (`long long`).
- Relevancia: puntajes decimales entre 0 y 1 (`double`).
- Tiempos de carrera: segundos (`double`).
- Registros combinados: `struct Estudiante`.

## Ejecutar todo desde PowerShell

Desde la raiz del repositorio:

```powershell
cd "D:\semestre_1-2026\Estructura Y Semantica de lenguajes de programacion\ARTICULO\REPO-GIT\Articulo.codigo"
Set-ExecutionPolicy -Scope Process -ExecutionPolicy Bypass
.\CPP\ejecutar_cpp.ps1
```

## Compilar un archivo manualmente

Ejemplo con enteros:

```powershell
g++ -std=c++17 -O2 -Wno-stringop-overflow CPP\entero\entero.cpp -o CPP\entero\entero.exe
.\CPP\entero\entero.exe
```

## Nota sobre memoria

La memoria mostrada es una estimacion de los datos utilizados por el vector original y el resultado ordenado. No representa toda la memoria real del proceso del sistema operativo.

## Nota sobre tiempos

Los tiempos pueden variar entre ejecuciones por procesos del sistema, carga de CPU y configuracion del equipo. Por eso se ejecuta cada caso 10 veces y se registra minimo, maximo y promedio.
