@echo off
REM Tournament Analyzer Server Runner
REM Ensures the server is built and running

REM Check if server.exe exists
if not exist "server.exe" (
    echo Building server...
    call build.bat
    if %errorlevel% neq 0 (
        echo Build failed!
        pause
        exit /b 1
    )
)

echo.
echo ========================================
echo Starting Tournament API Server
echo ========================================
echo.
echo Server: http://localhost:8080/api
echo Frontend: Open frontend/index.html in browser
echo.
echo Press Ctrl+C to stop the server
echo.

server.exe
pause
