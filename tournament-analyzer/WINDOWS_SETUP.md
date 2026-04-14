# 🛠️ Windows Setup Guide

## Prerequisites Installation

This guide helps you set up the Tournament Analyzer on Windows.

### Step 1: Install GCC Compiler

The C backend requires a GCC compiler. Choose one:

#### **Option A: MinGW-w64 (Recommended)**

1. Download from: https://www.mingw-w64.org/
   - Download the **Online Installer**
   - Choose: `x86_64` architecture, `Win32` threads, `SJLJ` exceptions

2. Run installer and select installation folder (e.g., `C:\mingw64`)

3. Add to PATH:
   - Right-click **This PC** → **Properties**
   - Click **Advanced system settings**
   - Click **Environment Variables**
   - Edit **Path** variable, add: `C:\mingw64\bin` (or your installation path)
   - Click OK

4. Verify installation:
   ```cmd
   gcc --version
   ```
   Should show version info

#### **Option B: TDM-GCC**

1. Download from: https://jmeubank.github.io/tdm-gcc/
2. Run installer, use default settings
3. Verify: `gcc --version`

#### **Option C: Windows Subsystem for Linux (WSL2)**

If you have WSL2 with Ubuntu:
```bash
sudo apt-get update
sudo apt-get install build-essential
```

---

### Step 2: Build the Backend

#### **Using the Build Script (Easiest)**

1. Navigate to the `backend` folder:
   ```cmd
   cd tournament-analyzer\backend
   ```

2. Run the build script:
   ```cmd
   build.bat
   ```

3. Wait for compilation to complete

If successful, you'll see:
```
Build successful!
Server executable: server.exe
```

#### **Manual Compilation**

If `build.bat` doesn't work:
```cmd
gcc -Wall -O2 -o server.exe tournament.c api_server.c -lm -lws2_32
```

---

### Step 3: Start the Server

#### **Using the Run Script (Easiest)**

In the `backend` folder:
```cmd
run.bat
```

The server will automatically:
- Build if needed
- Start on `http://localhost:8080`
- Display connection info

#### **Manual Start**

Double-click `server.exe` in the backend folder

Or from command line:
```cmd
./server.exe
```

---

## Using the Frontend

### Open the UI

1. Navigate to: `frontend/index.html`
2. Right-click → **Open with** → Choose your browser
3. Or drag the file into your browser window

### Test the Connection

1. With the server running, click **LOAD SAMPLE DATA**
2. Click **ANALYZE TOURNAMENT**
3. If results appear → ✅ Connection working!

### If Results Don't Appear

The frontend automatically falls back to JavaScript:
1. Check browser console: `F12` → **Console**
2. Should see: `⚠ Backend unavailable - using JavaScript fallback`
3. This is normal and the app will still work!

---

## Troubleshooting

### "gcc: command not found"

**Solution:**
1. Install MinGW-w64 or TDM-GCC (see Step 1)
2. Add compiler to PATH (see Step 1, Option A, step 3)
3. Restart Command Prompt or PowerShell
4. Try `gcc --version` again

### "Port 8080 already in use"

**Solution - Option 1: Stop existing process**
```cmd
taskkill /F /IM server.exe
```

**Solution - Option 2: Use different port**
1. Open `api_server.c`
2. Find: `#define PORT 8080`
3. Change to: `#define PORT 8081` (or any available port)
4. Rebuild: `build.bat`

### Server starts but frontend shows no results

**This is expected behavior.**
- The frontend has a built-in JavaScript fallback
- Results will still appear using JavaScript
- Check console to confirm: `F12` → **Console**

### "Build failed with errors"

1. Check GCC version: `gcc --version` (should be 4.9+)
2. Verify files exist in backend folder:
   - `tournament.c`
   - `tournament.h`
   - `api_server.c`
3. Try manual compilation with full paths:
   ```cmd
   cd "c:\Users\YourName\OneDrive\Documents\DAA\tournament-analyzer\backend"
   gcc -Wall -O2 -o server.exe tournament.c api_server.c -lm -lws2_32
   ```

---

## Quick Start Summary

```
1. Install GCC → https://www.mingw-w64.org/
2. Add to PATH → `C:\mingw64\bin` (or installation folder)
3. Restart terminal
4. Open Command Prompt in backend folder
5. Run: build.bat
6. Run: run.bat
7. Open frontend/index.html in browser
8. Click "LOAD SAMPLE DATA"
9. Click "ANALYZE TOURNAMENT"
10. 🎉 See results!
```

---

## Advanced: Using Make

If you have `make` installed (via MinGW or Chocolatey):

```cmd
cd backend
make all      # Build
make run      # Run server
make clean    # Remove build files
```

---

## Common Questions

**Q: Do I need to restart the server after changes?**  
A: Yes, rebuild with `build.bat` and restart `run.bat`

**Q: Can I use a different port?**  
A: Yes, edit `#define PORT` in `api_server.c` and rebuild

**Q: Is the frontend dependent on the backend?**  
A: No! The frontend works standalone with JavaScript fallback

**Q: How do I stop the server?**  
A: Press `Ctrl+C` in the command prompt window

**Q: Can I run this on Linux/Mac?**  
A: Yes! Use the Makefile directly (make, make run)

---

## Support

If you encounter issues:
1. Check this guide's Troubleshooting section
2. Verify GCC is installed: `gcc --version`
3. Check files are in correct locations
4. Review console output for error messages
5. Try the JavaScript-only version (frontend works standalone)

---

**You're all set! 🚀 Happy analyzing!**
