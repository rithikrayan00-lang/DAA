@echo off
REM Tournament Analyzer Build Script for Windows
REM Requires: GCC (MinGW or TDM-GCC)

echo.
echo ========================================
echo Tournament Analyzer - Build Script
echo ========================================
echo.

REM Check if gcc is available
gcc --version >nul 2>&1
if %errorlevel% neq 0 (
    echo ERROR: GCC not found!
    echo.
    echo Please install MinGW or TDM-GCC:
    echo 1. Download from: https://www.mingw-w64.org/
    echo 2. Add GCC to PATH
    echo 3. Run this script again
    echo.
    pause
    exit /b 1
)

echo GCC found: 
gcc --version | findstr /R "^gcc"
echo.

echo Building Tournament Analyzer...
echo.

cd /d "%~dp0"

echo Compiling...
gcc -Wall -O2 -o server.exe tournament.c api_server.c -lm -lws2_32

if %errorlevel% neq 0 (
    echo.
    echo ERROR: Compilation failed!
    pause
    exit /b 1
)

echo.
echo ========================================
echo Build successful!
echo ========================================
echo.
echo Server executable: server.exe
echo.
echo To start the server, run:
echo   server.exe
echo.
echo Then open: frontend/index.html in your browser
echo.
pause
