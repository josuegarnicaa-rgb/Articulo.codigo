$ErrorActionPreference = "Stop"

$ROOT = Split-Path -Parent $MyInvocation.MyCommand.Path
$RESULTADOS = Join-Path $ROOT "resultados_globales"

New-Item -ItemType Directory -Force -Path $RESULTADOS | Out-Null

$resumenCsv = Join-Path $RESULTADOS "resumen_general.csv"
"Lenguaje,Estado,Detalle,Tiempo_total_ms" | Out-File -Encoding UTF8 $resumenCsv

function Existe-Comando($cmd) {
    return [bool](Get-Command $cmd -ErrorAction SilentlyContinue)
}

function Agregar-Resumen($lenguaje, $estado, $detalle, $tiempo) {
    $linea = "$lenguaje,$estado,$detalle,$tiempo"
    Add-Content -Encoding UTF8 -Path $resumenCsv -Value $linea
}

Write-Host "------------------------------"
Write-Host " EJECUCION GENERAL - QUICKSORT"
Write-Host " Rust + C++ + Haskell"
Write-Host "------------------------------"

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
    try {
        Push-Location $rutaRust

        if (Test-Path "Cargo.toml") {
            Write-Host "[1] COMPILANDO RUST..."
            cargo build --release 2>&1 | Tee-Object -FilePath (Join-Path $RESULTADOS "rust_build.log")

            Write-Host "`n[1] EJECUTANDO RUST..."
            $tiempoRust = Measure-Command {
                cargo run --release -- 3 2>&1 | Tee-Object -FilePath (Join-Path $RESULTADOS "rust_salida.txt")
            }

            Write-Host "Rust finalizado en $([Math]::Round($tiempoRust.TotalMilliseconds, 3)) ms"
            Agregar-Resumen "Rust" "OK" "Ejecutado con cargo" "$([Math]::Round($tiempoRust.TotalMilliseconds, 3))"
        }
        else {
            Write-Host "No se encontro Cargo.toml en RUST. Se omite Rust."
            Agregar-Resumen "Rust" "OMITIDO" "No se encontro Cargo.toml" "0"
        }

        Pop-Location
    }
    catch {
        Pop-Location
        Write-Host "Error en Rust. Se continua con los demas."
        Write-Host $_
        Agregar-Resumen "Rust" "ERROR" "Fallo al compilar o ejecutar" "0"
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

            g++ -std=c++17 -O2 "$archivoCppPrincipal" -o "$exeCpp" 2>&1 | Tee-Object -FilePath (Join-Path $RESULTADOS "cpp_build.log")

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
$csvHaskell = Join-Path $RESULTADOS "haskell_tiempos.csv"
"Archivo,Tiempo_total_ms" | Out-File -Encoding UTF8 $csvHaskell

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
        $archivosHs = Get-ChildItem -Path $rutaHaskell -Recurse -Filter "*.hs" | Where-Object {
            $_.Name -notlike "*test*"
        }

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
                    ghc -O2 "$($archivo.FullName)" -o "$exeHs" 2>&1 | Tee-Object -Append -FilePath (Join-Path $RESULTADOS "haskell_build.log")

                    Write-Host "Ejecutando Haskell: $nombreBase"
                    $tiempoHs = Measure-Command {
                        & $exeHs 2>&1 | Tee-Object -Append -FilePath (Join-Path $RESULTADOS "haskell_salida.txt")
                    }

                    $tiempoFinal = [Math]::Round($tiempoHs.TotalMilliseconds, 3)
                    Add-Content -Encoding UTF8 -Path $csvHaskell -Value "$($archivo.Name),$tiempoFinal"
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

Write-Host "`n------------------------------"
Write-Host " EJECUCION FINALIZADA"
Write-Host "------------------------------"
Write-Host "Resultados guardados en:"
Write-Host $RESULTADOS
Write-Host "`nResumen general:"
Write-Host $resumenCsv