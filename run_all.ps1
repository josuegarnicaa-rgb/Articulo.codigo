$ErrorActionPreference = "Stop"

$ROOT = Split-Path -Parent $MyInvocation.MyCommand.Path
$RESULTADOS = Join-Path $ROOT "resultados_globales"

New-Item -ItemType Directory -Force -Path $RESULTADOS | Out-Null

$resumenCsv = Join-Path $RESULTADOS "resumen_general.csv"
$codigosCsv = Join-Path $RESULTADOS "codigos_encontrados.csv"
$csvHaskell = Join-Path $RESULTADOS "haskell_tiempos.csv"

$tablaResumen = @()
$tablaCodigos = @()
$tablaHaskell = @()

function Existe-Comando($cmd) {
    return [bool](Get-Command $cmd -ErrorAction SilentlyContinue)
}

function Ruta-Relativa($rutaCompleta) {
    return $rutaCompleta.Replace($ROOT + "\", "")
}

function Agregar-Resumen($lenguaje, $estado, $detalle, $tiempo) {
    $script:tablaResumen += [PSCustomObject]@{
        Lenguaje        = $lenguaje
        Estado          = $estado
        Detalle         = $detalle
        Tiempo_total_ms = $tiempo
    }
}

function Agregar-Codigo($lenguaje, $archivo, $ruta) {
    $script:tablaCodigos += [PSCustomObject]@{
        Lenguaje = $lenguaje
        Archivo  = $archivo
        Ruta     = Ruta-Relativa $ruta
    }
}

function Registrar-Codigos {
    $rutaRust = Join-Path $ROOT "RUST"
    $rutaCpp = Join-Path $ROOT "C++"
    $rutaHaskell = Join-Path $ROOT "HASKELL"

    if (Test-Path $rutaRust) {
        $codigosRust = @(Get-ChildItem -Path $rutaRust -Recurse -Filter "*.rs" -ErrorAction SilentlyContinue)
        foreach ($codigo in $codigosRust) {
            Agregar-Codigo "Rust" $codigo.Name $codigo.FullName
        }
    }

    if (Test-Path $rutaCpp) {
        $codigosCpp = @(Get-ChildItem -Path $rutaCpp -Recurse -Include "*.cpp", "*.h", "*.hpp" -ErrorAction SilentlyContinue)
        foreach ($codigo in $codigosCpp) {
            Agregar-Codigo "C++" $codigo.Name $codigo.FullName
        }
    }

    if (Test-Path $rutaHaskell) {
        $codigosHs = @(Get-ChildItem -Path $rutaHaskell -Recurse -Filter "*.hs" -ErrorAction SilentlyContinue)
        foreach ($codigo in $codigosHs) {
            Agregar-Codigo "Haskell" $codigo.Name $codigo.FullName
        }
    }
}

Write-Host "------------------------------"
Write-Host " EJECUCION GENERAL - QUICKSORT"
Write-Host " Rust + C++ + Haskell"
Write-Host "------------------------------"

Registrar-Codigos

# ------------------------------
# 1. RUST
# ------------------------------

Write-Host "`n[1] VERIFICANDO RUST..."

$rutaRust = Join-Path $ROOT "RUST"

if (!(Test-Path $rutaRust)) {
    Write-Host "No existe la carpeta RUST. Se omite Rust."
    Agregar-Resumen "Rust" "OMITIDO" "No existe carpeta RUST" "0"
}
elseif (!(Existe-Comando "cargo")) {
    Write-Host "No se encontro cargo. Se omite Rust."
    Agregar-Resumen "Rust" "OMITIDO" "No se encontro cargo" "0"
}
else {
    $entroRust = $false

    try {
        Push-Location $rutaRust
        $entroRust = $true

        if (Test-Path "Cargo.toml") {
            Write-Host "[1] COMPILANDO RUST..."
            cargo build --release 2>&1 | Tee-Object -FilePath (Join-Path $RESULTADOS "rust_build.log")

            Write-Host "`n[1] EJECUTANDO RUST..."

            $rutaRelease = Join-Path $rutaRust "target\release"
            $exeRust = Get-ChildItem -Path $rutaRelease -Filter "*.exe" -File |
                Sort-Object LastWriteTime -Descending |
                Select-Object -First 1

            if ($null -eq $exeRust) {
                Write-Host "No se encontro ejecutable Rust. Se ejecutara con cargo run."
                $tiempoRust = Measure-Command {
                    cargo run --release -- 3 2>&1 | Tee-Object -FilePath (Join-Path $RESULTADOS "rust_salida.txt")
                }
                Agregar-Resumen "Rust" "OK" "Ejecutado con cargo run" "$([Math]::Round($tiempoRust.TotalMilliseconds, 3))"
            }
            else {
                $tiempoRust = Measure-Command {
                    & $exeRust.FullName 3 2>&1 | Tee-Object -FilePath (Join-Path $RESULTADOS "rust_salida.txt")
                }
                Agregar-Resumen "Rust" "OK" "Ejecutado desde .exe" "$([Math]::Round($tiempoRust.TotalMilliseconds, 3))"
            }

            Write-Host "Rust finalizado en $([Math]::Round($tiempoRust.TotalMilliseconds, 3)) ms"
        }
        else {
            Write-Host "No se encontro Cargo.toml en RUST. Se omite Rust."
            Agregar-Resumen "Rust" "OMITIDO" "No se encontro Cargo.toml" "0"
        }
    }
    catch {
        Write-Host "Error en Rust. Se continua con los demas."
        Write-Host $_
        Agregar-Resumen "Rust" "ERROR" "Fallo al compilar o ejecutar" "0"
    }
    finally {
        if ($entroRust) {
            Pop-Location
        }
    }
}

# ------------------------------
# 2. C++
# ------------------------------

Write-Host "`n[2] VERIFICANDO C++..."

$rutaCpp = Join-Path $ROOT "C++"

if (!(Test-Path $rutaCpp)) {
    Write-Host "No existe la carpeta C++. Se omite C++."
    Agregar-Resumen "C++" "OMITIDO" "No existe carpeta C++" "0"
}
elseif (!(Existe-Comando "g++")) {
    Write-Host "No se encontro g++. Se omite C++."
    Agregar-Resumen "C++" "OMITIDO" "No se encontro g++" "0"
}
else {
    try {
        $archivoCppPrincipal = Join-Path $ROOT "C++\cpp\quicksort_cpp_archivos.cpp"

        if (!(Test-Path $archivoCppPrincipal)) {
            $archivoCpp = Get-ChildItem -Path $rutaCpp -Recurse -Filter "*.cpp" | Select-Object -First 1

            if ($null -eq $archivoCpp) {
                Write-Host "No se encontro ningun archivo .cpp. Se omite C++."
                Agregar-Resumen "C++" "OMITIDO" "No hay archivos .cpp" "0"
            }
            else {
                $archivoCppPrincipal = $archivoCpp.FullName
            }
        }

        if (Test-Path $archivoCppPrincipal) {
            Write-Host "[2] COMPILANDO C++..."
            $exeCpp = Join-Path $RESULTADOS "quicksort_cpp.exe"

            g++ -std=c++17 -O2 "$archivoCppPrincipal" -o "$exeCpp" 2>&1 |
                Tee-Object -FilePath (Join-Path $RESULTADOS "cpp_build.log")

            Write-Host "`n[2] EJECUTANDO C++..."

            $tiempoCpp = Measure-Command {
                & $exeCpp 2>&1 | Tee-Object -FilePath (Join-Path $RESULTADOS "cpp_salida.txt")
            }

            Write-Host "C++ finalizado en $([Math]::Round($tiempoCpp.TotalMilliseconds, 3)) ms"
            Agregar-Resumen "C++" "OK" "Ejecutado con g++" "$([Math]::Round($tiempoCpp.TotalMilliseconds, 3))"
        }
    }
    catch {
        Write-Host "Error en C++. Se continua con los demas."
        Write-Host $_
        Agregar-Resumen "C++" "ERROR" "Fallo al compilar o ejecutar" "0"
    }
}

# ------------------------------
# 3. HASKELL
# ------------------------------

Write-Host "`n[3] VERIFICANDO HASKELL..."

$rutaHaskell = Join-Path $ROOT "HASKELL"

if (!(Test-Path $rutaHaskell)) {
    Write-Host "No existe la carpeta HASKELL. Se omite Haskell."
    Agregar-Resumen "Haskell" "OMITIDO" "No existe carpeta HASKELL" "0"
}
elseif (!(Existe-Comando "ghc")) {
    Write-Host "No se encontro ghc. Se omite Haskell."
    Agregar-Resumen "Haskell" "OMITIDO" "No se encontro ghc" "0"
}
else {
    try {
        $archivosHs = @(Get-ChildItem -Path $rutaHaskell -Recurse -Filter "*.hs" | Where-Object {
            $_.Name -notlike "*test*"
        })

        if ($archivosHs.Count -eq 0) {
            Write-Host "No se encontraron archivos .hs. Se omite Haskell."
            Agregar-Resumen "Haskell" "OMITIDO" "No hay archivos .hs" "0"
        }
        else {
            foreach ($archivo in $archivosHs) {
                try {
                    $nombreBase = [System.IO.Path]::GetFileNameWithoutExtension($archivo.Name)
                    $exeHs = Join-Path $RESULTADOS "$nombreBase`_haskell.exe"

                    Write-Host "`nCompilando Haskell: $($archivo.FullName)"

                    ghc -O2 "$($archivo.FullName)" -o "$exeHs" 2>&1 |
                        Tee-Object -Append -FilePath (Join-Path $RESULTADOS "haskell_build.log")

                    Write-Host "Ejecutando Haskell: $nombreBase"

                    $tiempoHs = Measure-Command {
                        & $exeHs 2>&1 | Tee-Object -Append -FilePath (Join-Path $RESULTADOS "haskell_salida.txt")
                    }

                    $tiempoFinal = [Math]::Round($tiempoHs.TotalMilliseconds, 3)

                    $tablaHaskell += [PSCustomObject]@{
                        Archivo         = $archivo.Name
                        Tiempo_total_ms = $tiempoFinal
                    }

                    Agregar-Resumen "Haskell" "OK" "$($archivo.Name)" "$tiempoFinal"
                }
                catch {
                    Write-Host "Error en archivo Haskell: $($archivo.Name). Se continua."
                    Write-Host $_
                    Agregar-Resumen "Haskell" "ERROR" "$($archivo.Name)" "0"
                }
            }
        }
    }
    catch {
        Write-Host "Error general en Haskell. Se continua."
        Write-Host $_
        Agregar-Resumen "Haskell" "ERROR" "Fallo general" "0"
    }
}

# ------------------------------
# GUARDAR RESULTADOS
# ------------------------------

$tablaResumen | Export-Csv -Path $resumenCsv -NoTypeInformation -Encoding UTF8
$tablaCodigos | Export-Csv -Path $codigosCsv -NoTypeInformation -Encoding UTF8

if ($tablaHaskell.Count -gt 0) {
    $tablaHaskell | Export-Csv -Path $csvHaskell -NoTypeInformation -Encoding UTF8
}
else {
    "Archivo,Tiempo_total_ms" | Out-File -Encoding UTF8 $csvHaskell
}

# ------------------------------
# MOSTRAR TABLAS
# ------------------------------

Write-Host "`n------------------------------"
Write-Host " EJECUCION FINALIZADA"
Write-Host "------------------------------"

Write-Host "`nTABLA DE RESULTADOS:"
if ($tablaResumen.Count -gt 0) {
    $tablaResumen | Format-Table -AutoSize
}
else {
    Write-Host "No hay resultados registrados."
}

Write-Host "`nCODIGOS ENCONTRADOS:"
if ($tablaCodigos.Count -gt 0) {
    $tablaCodigos | Format-Table -AutoSize
}
else {
    Write-Host "No se encontraron archivos de codigo."
}

Write-Host "`nARCHIVOS GENERADOS:"
Write-Host "Resultados: $RESULTADOS"
Write-Host "Resumen:    $resumenCsv"
Write-Host "Codigos:    $codigosCsv"
Write-Host "Haskell:    $csvHaskell"