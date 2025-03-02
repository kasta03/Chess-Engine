# Ustawienie ścieżki do folderu, w którym znajdują się pliki .h
$folderPath = "."  # Zmień na właściwą ścieżkę

# Ustawienie nazwy pliku wynikowego
$outputFile = "output.txt"  # Zmień na właściwą ścieżkę

# Pobranie wszystkich plików .h i zapisanie ich treści do jednego pliku
Get-ChildItem -Path $folderPath -Filter "*.h" | ForEach-Object {
    Add-Content -Path $outputFile -Value "===== $_ ====="
    Get-Content $_.FullName | Add-Content -Path $outputFile
    Add-Content -Path $outputFile -Value "`n"
}

Write-Host "Scalono wszystkie pliki .h do $outputFile"
