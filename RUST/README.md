# Quicksort en Rust

Este proyecto implementa el algoritmo **Quicksort en Rust** para ordenar datasets almacenados en archivos `.txt`.

El programa permite leer datos desde archivos, guardarlos en vectores, ordenar con Quicksort, medir tiempo de ejecución, estimar memoria utilizada y verificar si el resultado quedó correctamente ordenado.

## 1. Objetivo del proyecto

El objetivo es evaluar el comportamiento del algoritmo **Quicksort** usando Rust, principalmente sobre archivos de datos grandes.

El programa mide:

* Tiempo mínimo de ordenamiento.
* Tiempo máximo de ordenamiento.
* Tiempo promedio.
* Memoria aproximada usada por el vector.
* Cantidad de datos procesados.
* Verificación de ordenamiento correcto.
* Longitud aproximada del código.

## 2. Requisitos previos

Antes de ejecutar el proyecto, se necesita tener instalado:

* Rust
* Cargo
* Visual Studio Code
* Extensión `rust-analyzer` para VS Code

Para verificar si Rust está instalado, ejecutar:

```powershell
rustc --version
cargo --version
```

Si ambos comandos muestran una versión, Rust está instalado correctamente.

## 3. Estructura del proyecto

La estructura recomendada del proyecto es:

```text
quicksort_rust/
├── Cargo.toml
├── README.md
├── data/
│   ├── booleanos/
│   │   ├── booleanos_10mil.txt
│   │   ├── booleanos_100mil.txt
│   │   └── booleanos_500mil.txt
│   │
│   ├── cadenas/
│   │   ├── cadenas_10mil.txt
│   │   ├── cadenas_100mil.txt
│   │   └── cadenas_500mil.txt
│   │
│   ├── decimales/
│   │   ├── decimal_10mil.txt
│   │   ├── decimales_100mil.txt
│   │   └── decimal_500mil.txt
│   │
│   ├── enteros/
│   │   ├── enteros_10mil.txt
│   │   ├── enteros_100mil.txt
│   │   └── enteros_500mil.txt
│   │
│   └── fechas/
│       ├── fechas_10mil.txt
│       ├── fechas_100mil.txt
│       └── fechas_500mil.txt
│
└── src/
    ├── main.rs
    ├── quicksort.rs
    ├── lectura.rs
    ├── medicion.rs
    └── reporte.rs
```

## 4. Función de cada archivo

### `main.rs`

Es el archivo principal del programa.

Se encarga de:

* Ejecutar el programa.
* Definir las carpetas de datos.
* Recorrer los archivos `.txt`.
* Llamar a las funciones de medición.
* Mostrar la tabla final.

### `quicksort.rs`

Contiene únicamente el algoritmo **Quicksort**.

Incluye:

* Función de ordenamiento.
* Función para verificar si un vector está ordenado.

### `lectura.rs`

Contiene las funciones para leer los archivos `.txt`.

Permite leer:

* Enteros
* Decimales
* Booleanos
* Cadenas
* Fechas

### `medicion.rs`

Contiene las funciones para medir los resultados experimentales.

Calcula:

* Tiempo mínimo
* Tiempo máximo
* Tiempo promedio
* Memoria aproximada
* Cantidad de elementos
* Si el resultado es correcto

### `reporte.rs`

Contiene las funciones para mostrar los resultados.

Genera:

* Tabla en consola.
* Resumen para el artículo.

## 5. Configuración de `Cargo.toml`

El archivo `Cargo.toml` debe contener estas dependencias:

```toml
[package]
name = "quicksort_rust"
version = "0.1.0"
edition = "2021"

[dependencies]
comfy-table = "7"
chrono = "0.4"
```

### Librerías usadas

* `comfy-table`: sirve para mostrar tablas bonitas en consola.
* `chrono`: sirve para trabajar con fechas.
* `std::time::Instant`: sirve para medir tiempo de ejecución.
* `std::mem::size_of`: sirve para estimar memoria usada.

## 6. Cómo ejecutar el proyecto

Abrir la terminal dentro de la carpeta del proyecto:

```powershell
cd "Articulo.codigo\quicksort_rust"
```

Verificar que estés dentro del proyecto:

```powershell
dir
```

Debe aparecer:

```text
Cargo.toml
src
data
README.md
```

Después revisar que el código compile:

```powershell
cargo check
```

Si no hay errores, ejecutar el programa en modo optimizado:

```powershell
cargo run --release
```

## 7. Ejecutar con repeticiones

El programa permite indicar cuántas veces se repetirá cada prueba.

Ejecutar con 1 repetición:

```powershell
cargo run --release -- 1
```

Ejecutar con 3 repeticiones:

```powershell
cargo run --release -- 3
```

Ejecutar con 5 repeticiones:

```powershell
cargo run --release -- 5
```

Ejecutar con 10 repeticiones:

```powershell
cargo run --release -- 10
```

Para resultados más confiables en el artículo, se recomienda usar:

```powershell
cargo run --release -- 10
```

## 8. Significado del comando

El comando:

```powershell
cargo run --release -- 10
```

significa:

```text
cargo run      → ejecuta el programa
--release      → usa compilación optimizada
--             → separa los argumentos de Cargo
10             → número de repeticiones por archivo
```

## 9. Salida esperada

El programa muestra una tabla como esta:

```text
+----------------------+----------+----------+---------+---------+----------+---------+----------+
| Caso                 | Tipo     | Cantidad | Min(ms) | Max(ms) | Prom(ms) | Mem(MB) | Correcto |
+----------------------+----------+----------+---------+---------+----------+---------+----------+
| enteros_10mil.txt    | Entero   | 10000    | 0.452   | 0.554   | 0.483    | 0.076   | Sí       |
| enteros_100mil.txt   | Entero   | 100000   | 4.608   | 4.810   | 4.690    | 0.763   | Sí       |
| enteros_500mil.txt   | Entero   | 500000   | 19.843  | 22.697  | 20.408   | 3.815   | Sí       |
+----------------------+----------+----------+---------+---------+----------+---------+----------+
```

## 10. Significado de cada columna

| Columna  | Significado                            |
| -------- | -------------------------------------- |
| Caso     | Nombre del archivo procesado           |
| Tipo     | Tipo de dato ordenado                  |
| Cantidad | Cantidad de elementos leídos           |
| Min(ms)  | Menor tiempo obtenido                  |
| Max(ms)  | Mayor tiempo obtenido                  |
| Prom(ms) | Tiempo promedio                        |
| Mem(MB)  | Memoria aproximada usada por el vector |
| Correcto | Indica si el vector quedó ordenado     |

## 11. Probar solo enteros

Para trabajar únicamente con enteros, abrir `src/main.rs` y dejar esta parte así:

```rust
let carpetas = [
    ("data/enteros", "enteros"),
];
```

Con esto el programa solo procesará:

```text
enteros_10mil.txt
enteros_100mil.txt
enteros_500mil.txt
```

Esto es recomendable si el artículo se enfoca primero en:

```text
Rust + Quicksort + números enteros
```

## 12. Probar todos los tipos de datos

Para procesar todos los archivos, usar esta configuración en `main.rs`:

```rust
let carpetas = [
    ("data/enteros", "enteros"),
    ("data/decimales", "decimales"),
    ("data/booleanos", "booleanos"),
    ("data/cadenas", "cadenas"),
    ("data/fechas", "fechas"),
];
```

Con esto se procesan todos los archivos dentro de las carpetas de `data`.

## 13. Importante sobre los archivos originales

El programa no modifica los archivos `.txt`.

El proceso es:

```text
leer archivo → guardar datos en vector → ordenar vector → medir tiempo → mostrar resultado
```

Los archivos originales permanecen iguales.

## 14. Recomendaciones para obtener mejores resultados

Para obtener resultados útiles para un artículo científico:

1. Ejecutar siempre en modo optimizado:

```powershell
cargo run --release -- 10
```

2. Cerrar programas innecesarios antes de medir.

3. No usar solo:

```powershell
cargo run
```

porque ejecuta en modo desarrollo y los tiempos pueden ser más lentos.

4. Usar la misma computadora para todas las pruebas.

5. Usar la misma cantidad de repeticiones para todos los casos.

## 15. Posibles errores y soluciones

### Error: `cargo no se reconoce como comando`

Significa que Rust no está instalado o no está agregado al PATH.

Solución:

* Instalar Rust.
* Cerrar y volver a abrir la terminal.
* Probar otra vez:

```powershell
cargo --version
```

## 16. Conclusión

Este proyecto permite ejecutar pruebas experimentales de Quicksort en Rust sobre datasets en formato `.txt`.

La salida generada puede usarse como base para tablas y análisis dentro de un artículo científico comparativo.
