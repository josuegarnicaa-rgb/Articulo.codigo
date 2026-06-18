use crate::medicion::Resultado;
use comfy_table::{Cell, Table};
use std::fs;

pub fn imprimir_tabla(resultados: &[Resultado]) {
    let mut tabla = Table::new();

    tabla.set_header(vec![
        "Caso",
        "Tipo",
        "Cantidad",
        "Min(ms)",
        "Max(ms)",
        "Prom(ms)",
        "Mem(MB)",
        "Correcto",
    ]);

    for r in resultados {
        tabla.add_row(vec![
            Cell::new(&r.caso),
            Cell::new(&r.tipo),
            Cell::new(r.cantidad),
            Cell::new(format!("{:.3}", r.min_ms)),
            Cell::new(format!("{:.3}", r.max_ms)),
            Cell::new(format!("{:.3}", r.prom_ms)),
            Cell::new(format!("{:.3}", r.memoria_mb)),
            Cell::new(if r.correcto { "Sí" } else { "No" }),
        ]);
    }

    println!();
    println!("{tabla}");
}

pub fn imprimir_resumen(resultados: &[Resultado]) {
    println!();
    println!("RESUMEN PARA EL ARTÍCULO");
    println!("------------------------");

    let limite_ms = 5000.0;

    let mejor_caso = resultados
        .iter()
        .filter(|r| r.prom_ms <= limite_ms)
        .max_by_key(|r| r.cantidad);

    match mejor_caso {
        Some(r) => {
            println!(
                "Mayor cantidad ordenada antes de superar 5 segundos: {} datos en '{}', con promedio {:.3} ms.",
                r.cantidad, r.caso, r.prom_ms
            );
        }
        None => {
            println!("Ningún caso quedó por debajo de 5 segundos.");
        }
    }

    if let Ok(codigo) = fs::read_to_string("src/main.rs") {
        let lineas = codigo.lines().count();
        println!("Longitud aproximada del archivo main.rs: {} líneas.", lineas);
    }

    if let Ok(codigo) = fs::read_to_string("src/quicksort.rs") {
        let lineas = codigo.lines().count();
        println!("Longitud aproximada del algoritmo Quicksort: {} líneas.", lineas);
    }
}