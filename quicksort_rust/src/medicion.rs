use crate::lectura::{
    leer_booleanos, leer_cadenas, leer_decimales, leer_enteros, leer_fechas, nombre_archivo,
};
use crate::quicksort::{esta_ordenado_by, quicksort_by};

use std::cmp::Ordering;
use std::io::Write;
use std::mem::size_of;
use std::time::Instant;

#[derive(Debug)]
pub struct Resultado {
    pub caso: String,
    pub tipo: String,
    pub cantidad: usize,
    pub min_ms: f64,
    pub max_ms: f64,
    pub prom_ms: f64,
    pub memoria_mb: f64,
    pub correcto: bool,
}

pub fn memoria_vec_mb<T>(datos: &Vec<T>) -> f64 {
    let bytes_vector = size_of::<Vec<T>>();
    let bytes_datos = datos.capacity() * size_of::<T>();
    let total_bytes = bytes_vector + bytes_datos;

    total_bytes as f64 / (1024.0 * 1024.0)
}

pub fn memoria_strings_mb(datos: &Vec<String>) -> f64 {
    let bytes_vector = size_of::<Vec<String>>();
    let bytes_structs = datos.capacity() * size_of::<String>();
    let bytes_texto: usize = datos.iter().map(|s| s.capacity()).sum();

    let total_bytes = bytes_vector + bytes_structs + bytes_texto;

    total_bytes as f64 / (1024.0 * 1024.0)
}

pub fn medir_caso<T, F, M>(
    caso: &str,
    tipo: &str,
    datos_originales: &[T],
    repeticiones: usize,
    comparar: F,
    calcular_memoria: M,
) -> Resultado
where
    T: Clone,
    F: Fn(&T, &T) -> Ordering + Copy,
    M: Fn(&Vec<T>) -> f64 + Copy,
{
    let mut tiempos = Vec::new();
    let mut memoria_mb = 0.0;
    let mut correcto = true;

    for _ in 0..repeticiones {
        let mut datos = datos_originales.to_vec();

        let inicio = Instant::now();
        quicksort_by(&mut datos, comparar);
        let duracion = inicio.elapsed();

        let tiempo_ms = duracion.as_secs_f64() * 1000.0;

        tiempos.push(tiempo_ms);
        memoria_mb = calcular_memoria(&datos);

        if !esta_ordenado_by(&datos, comparar) {
            correcto = false;
        }
    }

    let min_ms = tiempos.iter().copied().fold(f64::INFINITY, f64::min);
    let max_ms = tiempos
        .iter()
        .copied()
        .fold(f64::NEG_INFINITY, f64::max);
    let prom_ms = tiempos.iter().sum::<f64>() / tiempos.len() as f64;

    Resultado {
        caso: caso.to_string(),
        tipo: tipo.to_string(),
        cantidad: datos_originales.len(),
        min_ms,
        max_ms,
        prom_ms,
        memoria_mb,
        correcto,
    }
}

pub fn procesar_archivo(ruta: &str, tipo: &str, repeticiones: usize) -> Option<Resultado> {
    let caso = nombre_archivo(ruta);

    println!("Procesando: {} ({})", caso, tipo);
    std::io::stdout().flush().unwrap();

    match tipo {
        "enteros" => match leer_enteros(ruta) {
            Ok(datos) => Some(medir_caso(
                &caso,
                "Entero",
                &datos,
                repeticiones,
                |a, b| a.cmp(b),
                memoria_vec_mb,
            )),
            Err(e) => {
                println!("Error en {}: {}", ruta, e);
                None
            }
        },

        "decimales" => match leer_decimales(ruta) {
            Ok(datos) => Some(medir_caso(
                &caso,
                "Decimal",
                &datos,
                repeticiones,
                |a, b| a.total_cmp(b),
                memoria_vec_mb,
            )),
            Err(e) => {
                println!("Error en {}: {}", ruta, e);
                None
            }
        },

        "booleanos" => match leer_booleanos(ruta) {
            Ok(datos) => Some(medir_caso(
                &caso,
                "Booleano",
                &datos,
                repeticiones,
                |a, b| a.cmp(b),
                memoria_vec_mb,
            )),
            Err(e) => {
                println!("Error en {}: {}", ruta, e);
                None
            }
        },

        "cadenas" => match leer_cadenas(ruta) {
            Ok(datos) => Some(medir_caso(
                &caso,
                "Cadena",
                &datos,
                repeticiones,
                |a, b| a.cmp(b),
                memoria_strings_mb,
            )),
            Err(e) => {
                println!("Error en {}: {}", ruta, e);
                None
            }
        },

        "fechas" => match leer_fechas(ruta) {
            Ok(datos) => Some(medir_caso(
                &caso,
                "Fecha",
                &datos,
                repeticiones,
                |a, b| a.cmp(b),
                memoria_vec_mb,
            )),
            Err(e) => {
                println!("Error en {}: {}", ruta, e);
                None
            }
        },

        _ => None,
    }
}