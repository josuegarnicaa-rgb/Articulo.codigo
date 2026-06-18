# Ejecución del proyecto Quicksort

Este proyecto ejecuta las implementaciones del algoritmo **Quicksort** en los lenguajes **Rust**, **C++** y **Haskell** mediante un script general en PowerShell.

## Requisitos

Antes de ejecutar el proyecto, verificar que estén instalados los compiladores necesarios:

```powershell
cargo --version
g++ --version
ghc --version
```

Si `ghc` no está instalado, el script omitirá automáticamente Haskell y ejecutará solo los lenguajes disponibles.

## Estructura del proyecto

El archivo principal de ejecución debe estar en la carpeta raíz del proyecto:

```text
Articulo.codigo/
├── C++
├── HASKELL
├── RUST
├── README.md
└── run_all.ps1
```

## Cómo ejecutar

Abrir PowerShell o la terminal de VS Code en la carpeta raíz del proyecto:

```powershell
cd "C:\Users\USUARIO\Documents\SEMANTICA\ARTUCULO 2026\git.articulo\Articulo.codigo"
```

Permitir la ejecución temporal de scripts:

```powershell
Set-ExecutionPolicy -Scope Process -ExecutionPolicy Bypass
```

Ejecutar el script general:

```powershell
.\run_all.ps1
```

## Qué hace el script

El script realiza automáticamente lo siguiente:

```text
1. Verifica si existe la carpeta RUST.
2. Compila y ejecuta Rust si cargo está disponible.
3. Verifica si existe la carpeta C++.
4. Compila y ejecuta C++ si g++ está disponible.
5. Verifica si existe la carpeta HASKELL.
6. Ejecuta Haskell si ghc está disponible.
7. Si falta algún compilador, omite ese lenguaje y continúa con los demás.
8. Muestra una tabla de resultados en consola.
9. Muestra todos los archivos de código encontrados.
10. Guarda los resultados en archivos CSV.
```

## Archivos generados

Después de ejecutar el script, se crea la carpeta:

```text
resultados_globales/
```

Dentro se generan archivos como:

```text
resumen_general.csv
codigos_encontrados.csv
rust_salida.txt
cpp_salida.txt
haskell_tiempos.csv
```

## Ver resultados

Para ver el resumen general desde PowerShell:

```powershell
Import-Csv .\resultados_globales\resumen_general.csv | Format-Table -AutoSize
```

Para ver los códigos encontrados:

```powershell
Import-Csv .\resultados_globales\codigos_encontrados.csv | Format-Table -AutoSize
```

Para ver la salida de Rust:

```powershell
Get-Content .\resultados_globales\rust_salida.txt
```

Para ver la salida de C++:

```powershell
Get-Content .\resultados_globales\cpp_salida.txt
```

## Nota

Si Haskell aparece como `OMITIDO`, significa que `ghc` no está instalado o no está configurado en el PATH de Windows. En ese caso, Rust y C++ se ejecutarán normalmente.
