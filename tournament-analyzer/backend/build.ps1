# Tournament Analyzer - PowerShell Build & Run Script
# Usage: .\build.ps1

# Color output
$Red = "Red"
$Green = "Green"
$Yellow = "Yellow"
$Blue = "Blue"

Write-Host "`n========================================" -ForegroundColor $Blue
Write-Host "Tournament Analyzer - Build Script" -ForegroundColor $Blue
Write-Host "========================================`n" -ForegroundColor $Blue

# Check if GCC is available
Write-Host "Checking for GCC compiler..." -ForegroundColor $Yellow
$gccCheck = Where-Object -InputObject (Get-Command gcc -ErrorAction SilentlyContinue) { $_ }

if (-not $gccCheck) {
    Write-Host "ERROR: GCC not found!" -ForegroundColor $Red
    Write-Host ""
    Write-Host "Please install MinGW-w64 or TDM-GCC:" -ForegroundColor $Yellow
    Write-Host "1. Download: https://www.mingw-w64.org/" -ForegroundColor $Yellow
    Write-Host "2. Add to PATH: C:\mingw64\bin" -ForegroundColor $Yellow
    Write-Host "3. Restart PowerShell" -ForegroundColor $Yellow
    Write-Host "4. Run this script again" -ForegroundColor $Yellow
    Write-Host ""
    Read-Host "Press Enter to exit"
    exit 1
}

# Show GCC version
Write-Host "GCC found: " -ForegroundColor $Green
gcc --version | Select-Object -First 1 | Write-Host -ForegroundColor $Green
Write-Host ""

# Build
Write-Host "Compiling Tournament Analyzer..." -ForegroundColor $Yellow

$compileCommand = "gcc -Wall -O2 -o server.exe tournament.c api_server.c -lm -lws2_32"
Invoke-Expression $compileCommand

if ($LASTEXITCODE -ne 0) {
    Write-Host ""
    Write-Host "ERROR: Compilation failed!" -ForegroundColor $Red
    Write-Host "Details above" -ForegroundColor $Red
    Write-Host ""
    Read-Host "Press Enter to exit"
    exit 1
}

Write-Host ""
Write-Host "========================================" -ForegroundColor $Green
Write-Host "Build successful!" -ForegroundColor $Green
Write-Host "========================================`n" -ForegroundColor $Green

Write-Host "Server executable: server.exe" -ForegroundColor $Blue
Write-Host ""
Write-Host "To start the server, run:" -ForegroundColor $Yellow
Write-Host "  .\run.ps1" -ForegroundColor $Green
Write-Host ""
Write-Host "Then open: frontend/index.html in your browser" -ForegroundColor $Yellow
Write-Host ""
