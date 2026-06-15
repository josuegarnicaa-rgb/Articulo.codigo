$ErrorActionPreference = "Stop"

Write-Host ""
Write-Host "=============================================================="
Write-Host " EJECUTANDO BENCHMARK COMPLETO QUICK SORT - C++"
Write-Host "=============================================================="

function CompilarYEjecutar($nombre, $fuente, $salida) {
    Write-Host ""
    Write-Host "==================== $nombre ===================="
    g++ -std=c++17 -O2 -Wno-stringop-overflow $fuente -o $salida
    & $salida
}

CompilarYEjecutar "8.1 ENTEROS"      "CPP\entero\entero.cpp"        ".\CPP\entero\entero.exe"
CompilarYEjecutar "8.2 DECIMALES"    "CPP\decimales\decimal.cpp"    ".\CPP\decimales\decimal.exe"
CompilarYEjecutar "8.3 CARACTERES"   "CPP\caracter\caracter.cpp"    ".\CPP\caracter\caracter.exe"
CompilarYEjecutar "8.4 CADENAS"      "CPP\cadenas\cadena.cpp"       ".\CPP\cadenas\cadena.exe"
CompilarYEjecutar "8.5 BOOLEANOS"    "CPP\boolean\boolean.cpp"      ".\CPP\boolean\boolean.exe"
CompilarYEjecutar "8.6 FECHAS"       "CPP\fechas\fechas.cpp"        ".\CPP\fechas\fechas.exe"
CompilarYEjecutar "8.7 ARCHIVOS"     "CPP\archivos\archivos.cpp"    ".\CPP\archivos\archivos.exe"
CompilarYEjecutar "8.8 RELEVANCIA"   "CPP\relevancia\relevancia.cpp" ".\CPP\relevancia\relevancia.exe"
CompilarYEjecutar "8.9 TIEMPOS"      "CPP\tiempos\tiempos.cpp"      ".\CPP\tiempos\tiempos.exe"
CompilarYEjecutar "8.10 COMBINADO"   "CPP\combinado\todos.cpp"      ".\CPP\combinado\todos.exe"

Write-Host ""
Write-Host "=============================================================="
Write-Host " TODAS LAS PRUEBAS FINALIZARON"
Write-Host "=============================================================="
