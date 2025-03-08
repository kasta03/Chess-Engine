$folderPath = "."

$outputFile = "output.txt"

Get-ChildItem -Path $folderPath -Filter "*.h" | ForEach-Object {
    Add-Content -Path $outputFile -Value "===== $_ ====="
    Get-Content $_.FullName | Add-Content -Path $outputFile
    Add-Content -Path $outputFile -Value "`n"
}

Write-Host "Scalono wszystkie pliki .h do $outputFile"
