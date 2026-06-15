Write-Host ""
Write-Host "========================================"
Write-Host " LINEAS DE CODIGO C++"
Write-Host "========================================"

Get-ChildItem -Path CPP -Recurse -Include *.cpp,*.hpp |
    Where-Object { $_.FullName -notmatch "\.exe$" } |
    ForEach-Object {
        $lineas = (Get-Content $_.FullName | Measure-Object -Line).Lines
        [PSCustomObject]@{
            Archivo = $_.FullName.Replace((Get-Location).Path + "\", "")
            Lineas = $lineas
        }
    } | Format-Table -AutoSize
