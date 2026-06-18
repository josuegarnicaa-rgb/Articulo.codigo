mod lectura;
mod medicion;
mod quicksort;
mod reporte;

use medicion::{procesar_archivo, Resultado};
use reporte::{imprimir_resumen, imprimir_tabla};

use std::env;
use std::fs;

fn main() {
    let repeticiones = env::args()
        .nth(1)
        .and_then(|x| x.parse::<usize>().ok())
        .unwrap_or(3);

    println!("ALGORITMO QUICKSORT EN RUST");
    println!("Repeticiones por archivo: {}", repeticiones);
    println!();

    let carpetas = [
        ("data/enteros", "enteros"),
        ("data/decimales", "decimales"),
        ("data/booleanos", "booleanos"),
        ("data/cadenas", "cadenas"),
        ("data/fechas", "fechas"),
    ];

    let mut resultados: Vec<Resultado> = Vec::new();

    for (carpeta, tipo) in carpetas {
        let entradas = match fs::read_dir(carpeta) {
            Ok(e) => e,
            Err(_) => {
                println!("No se encontró la carpeta: {}", carpeta);
                continue;
            }
        };

        for entrada in entradas {
            if let Ok(archivo) = entrada {
                let ruta = archivo.path();

                if ruta.extension().and_then(|e| e.to_str()) == Some("txt") {
                    let ruta_texto = ruta.to_string_lossy().to_string();

                    if let Some(resultado) = procesar_archivo(&ruta_texto, tipo, repeticiones) {
                        resultados.push(resultado);
                    }
                }
            }
        }
    }

    resultados.sort_by(|a, b| {
        a.tipo
            .cmp(&b.tipo)
            .then(a.cantidad.cmp(&b.cantidad))
            .then(a.caso.cmp(&b.caso))
    });

    imprimir_tabla(&resultados);
    imprimir_resumen(&resultados);
}