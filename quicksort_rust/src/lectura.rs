use chrono::NaiveDate;
use std::fs;
use std::path::Path;

pub fn leer_tokens(ruta: &str) -> Result<Vec<String>, String> {
    let contenido = fs::read_to_string(ruta)
        .map_err(|e| format!("No se pudo leer el archivo {}: {}", ruta, e))?;

    Ok(contenido
        .split_whitespace()
        .map(|s| s.to_string())
        .collect())
}

pub fn leer_enteros(ruta: &str) -> Result<Vec<i64>, String> {
    let tokens = leer_tokens(ruta)?;

    tokens
        .iter()
        .map(|x| {
            x.parse::<i64>()
                .map_err(|_| format!("No se pudo convertir '{}' a entero", x))
        })
        .collect()
}

pub fn leer_decimales(ruta: &str) -> Result<Vec<f64>, String> {
    let tokens = leer_tokens(ruta)?;

    tokens
        .iter()
        .map(|x| {
            x.parse::<f64>()
                .map_err(|_| format!("No se pudo convertir '{}' a decimal", x))
        })
        .collect()
}

pub fn leer_booleanos(ruta: &str) -> Result<Vec<bool>, String> {
    let tokens = leer_tokens(ruta)?;

    tokens
        .iter()
        .map(|x| match x.to_lowercase().as_str() {
            "true" | "1" | "verdadero" => Ok(true),
            "false" | "0" | "falso" => Ok(false),
            _ => Err(format!("No se pudo convertir '{}' a booleano", x)),
        })
        .collect()
}

pub fn leer_cadenas(ruta: &str) -> Result<Vec<String>, String> {
    leer_tokens(ruta)
}

pub fn leer_fechas(ruta: &str) -> Result<Vec<NaiveDate>, String> {
    let tokens = leer_tokens(ruta)?;

    tokens.iter().map(|x| parsear_fecha(x)).collect()
}

fn parsear_fecha(texto: &str) -> Result<NaiveDate, String> {
    let formatos = ["%Y-%m-%d", "%d/%m/%Y", "%d-%m-%Y", "%Y/%m/%d"];

    for formato in formatos {
        if let Ok(fecha) = NaiveDate::parse_from_str(texto, formato) {
            return Ok(fecha);
        }
    }

    Err(format!(
        "No se pudo convertir '{}' a fecha. Formatos aceptados: YYYY-MM-DD, DD/MM/YYYY, DD-MM-YYYY, YYYY/MM/DD",
        texto
    ))
}

pub fn nombre_archivo(ruta: &str) -> String {
    Path::new(ruta)
        .file_name()
        .unwrap()
        .to_string_lossy()
        .to_string()
}