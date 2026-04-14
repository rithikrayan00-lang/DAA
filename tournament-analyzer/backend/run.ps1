# Tournament Analyzer - PowerShell Server Runner
# Usage: .\run.ps1

# Color output
$Blue = "Blue"
$Green = "Green"
$Yellow = "Yellow"

# Check if server executable exists
if (-not (Test-Path "server.exe")) {
    Write-Host "Server not built. Building now..." -ForegroundColor $Yellow
    & .\build.ps1
    
    if ($LASTEXITCODE -ne 0) {
        Write-Host "Build failed!" -ForegroundColor $Red
        exit 1
    }
}

# Start the server
Write-Host "`n========================================" -ForegroundColor $Blue
Write-Host "Starting Tournament API Server" -ForegroundColor $Blue
Write-Host "========================================`n" -ForegroundColor $Blue

Write-Host "Server: " -NoNewline -ForegroundColor $Yellow
Write-Host "http://localhost:3000/api" -ForegroundColor $Green

Write-Host "Frontend: " -NoNewline -ForegroundColor $Yellow
Write-Host "Open frontend/index.html in browser" -ForegroundColor $Green

Write-Host ""
Write-Host "Press Ctrl+C to stop the server" -ForegroundColor $Yellow
Write-Host ""

# Run the server
& .\server.exe
