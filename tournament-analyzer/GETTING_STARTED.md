# 🚀 Getting Started - Quick Reference

## 5-Minute Quick Start

### Windows User?
See [WINDOWS_SETUP.md](WINDOWS_SETUP.md) for detailed instructions

### Prerequisites Check
```bash
# Verify you have:
gcc --version        # Should show version
make --version       # Or just run build.bat
```

### Build & Run

**On Windows (with MinGW):**
```cmd
cd backend
build.bat     # Or: gcc -Wall -O2 -o server.exe tournament.c api_server.c -lm -lws2_32
run.bat       # Starts server at http://localhost:8080
```

**On Linux/Mac:**
```bash
cd backend
make all      # Build
make run      # Start server
```

### Test the App

1. **Open the UI**
   - Navigate to: `frontend/index.html`
   - Open in any modern browser (Chrome, Firefox, Edge, Safari)

2. **Try it**
   - Click: **LOAD SAMPLE DATA** (adds 8 sample players)
   - Click: **ANALYZE TOURNAMENT** (runs D&C algorithm)
   - See results with animations!

3. **Add Custom Players**
   - Enter player name: `John`
   - Enter score: `85`
   - Click: **ADD PLAYER**
   - Repeat for more players
   - Click: **ANALYZE TOURNAMENT**

### That's It! ✅

The frontend works **with or without** the backend:
- **With backend**: Uses fast C server (when available)
- **Without backend**: Uses JavaScript fallback (always works!)

---

## Project Structure

```
tournament-analyzer/
├── backend/              # C HTTP server
│   ├── tournament.c      # D&C algorithms
│   ├── tournament.h      # Header file
│   ├── api_server.c      # HTTP server
│   ├── Makefile          # Build config
│   ├── build.bat         # Windows build script
│   └── run.bat           # Windows run script
│
├── frontend/             # Web UI
│   ├── index.html        # Main page
│   ├── style.css         # Styling
│   └── app.js            # Logic & D&C implementation
│
├── README.md             # Full documentation
├── WINDOWS_SETUP.md      # Windows installation
└── GETTING_STARTED.md    # This file
```

---

## API Endpoints (Optional - For Testing)

If backend is running at `http://localhost:8080/api`:

```bash
# Get all players
curl http://localhost:8080/api/players

# Get top 3 players
curl "http://localhost:8080/api/top?k=3"

# Analyze tournament (POST)
curl -X POST http://localhost:8080/api/analyze \
  -H "Content-Type: application/json" \
  -d '{"players":[{"name":"Alice","score":87},{"name":"Bob","score":92}]}'

# Get bracket info
curl http://localhost:8080/api/bracket
```

---

## Features at a Glance

✅ **Divide & Conquer Algorithm**
- Finds tournament winner in O(n log n)
- Visualizes algorithm steps
- Shows divide/conquer/combine phases

✅ **Multiple Result Views**
- 🏆 Winner card (glowing animation)
- 📊 Player rankings table
- 🥇 Podium visualization
- 🌳 Tournament bracket tree
- 📈 Algorithm statistics

✅ **Smart Features**
- Loads sample tournament data
- Persistent player storage (localStorage)
- Responsive design (desktop + tablet)
- Dark cyberpunk theme
- Works offline (no backend needed)

✅ **Production Quality**
- Pure C backend (no dependencies)
- Vanilla JavaScript frontend
- Custom CSS (no frameworks)
- Clean, documented code

---

## Keyboard Shortcuts

| Action | Shortcut |
|--------|----------|
| Add Player | Enter (in score field) |
| Delete Player | Click "REMOVE" button |
| Clear All | `localStorage.clear()` in console |
| Open Console | F12 (Chrome/Firefox/Edge) |

---

## Troubleshooting

### "GCC not found"
→ Install MinGW-w64: https://www.mingw-w64.org/  
→ Add to PATH and restart terminal

### "Port 8080 already in use"
→ Kill existing: `taskkill /F /IM server.exe`  
→ Or change port in `api_server.c` and rebuild

### "No results showing"
→ Check browser console (F12) for errors  
→ Frontend works without backend - JavaScript fallback is active

### "Compilation errors"
→ See [WINDOWS_SETUP.md](WINDOWS_SETUP.md)  
→ Or open issue with error message

---

## Performance

**Algorithm Complexity**: O(n log n)
- 8 players: ~24 comparisons
- 100 players: ~665 comparisons
- 1000 players: ~9,965 comparisons

**Speed (typical)**:
- 10 players: <1ms
- 100 players: <10ms
- Results display with animations: 2-3 seconds

---

## Learn More

- **README.md**: Complete project documentation
- **backend/tournament.c**: Algorithm implementation
- **frontend/app.js**: D&C JavaScript implementation
- **frontend/style.css**: UI styling guide

---

## Next Steps

1. ✅ Build & run the server
2. ✅ Test with sample data
3. ✅ Add custom players
4. ✅ Analyze tournaments
5. ✅ Read the code and understand the algorithm
6. 🔄 Extend with new features!

---

## Questions?

- **Backend compilation**: See WINDOWS_SETUP.md
- **Algorithm details**: Read README.md Algorithm section
- **API usage**: Check README.md API Endpoints section
- **Code walkthrough**: Review the source files with comments

---

**Happy analyzing! 🏆 May your tournaments be well-ordered!**
