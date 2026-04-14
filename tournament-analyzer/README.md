# 🏆 Tournament Winner Analyzer
## Divide & Conquer Algorithm Visualizer

A complete full-stack application that implements the **Divide and Conquer algorithm** to find tournament winners, visualize bracket progression, and analyze player rankings. Features a C backend HTTP server and a stunning dark-themed frontend.

---

## 📋 Project Overview

This project demonstrates core computer science principles:
- **Algorithm**: Divide & Conquer pattern
- **Time Complexity**: O(n log n) for merge sort operations
- **Architecture**: RESTful API backend (C) + Interactive frontend (HTML/CSS/JS)
- **Data Structures**: Player structs, recursive bracket trees, JSON serialization

### Key Features
✅ Real-time tournament analysis using D&C algorithms  
✅ Visual D&C step-by-step animation  
✅ Tournament bracket tree visualization (SVG)  
✅ Top-3 podium display with medals  
✅ Player rankings table with sorting  
✅ Statistics panel (rounds, comparisons, total players)  
✅ Local storage for player persistence  
✅ Backend fallback (JavaScript) if C server unavailable  
✅ Dark cyberpunk-themed UI with animations  
✅ Fully responsive design (desktop & tablet)  

---

## 🚀 Quick Start

### Prerequisites
- **GCC** compiler (for Windows: MinGW or built-in)
- **Make** tool (included with MinGW)
- Modern web browser (Chrome, Firefox, Edge, Safari)

### Installation

1. **Clone/Navigate to project directory**
   ```bash
   cd tournament-analyzer
   ```

2. **Build the C backend**
   ```bash
   cd backend
   make all
   ```

3. **Start the HTTP server** (in Terminal/PowerShell)
   ```bash
   make run
   ```
   
   Server will start on `http://localhost:8080`

4. **Open the frontend**
   - Open `frontend/index.html` in your web browser
   - Or serve with a local HTTP server:
     ```bash
     cd frontend
     python -m http.server 8000
     # then open http://localhost:8000/index.html
     ```

---

## 📋 Architecture

```
tournament-analyzer/
├── backend/
│   ├── tournament.c         # D&C algorithm implementations
│   ├── tournament.h         # Header with struct definitions
│   ├── api_server.c         # HTTP server (POSIX sockets)
│   └── Makefile             # Build configuration
├── frontend/
│   ├── index.html           # UI structure & layout
│   ├── style.css            # Dark theme styling (no frameworks)
│   ├── app.js               # Tournament logic & API interaction
│   └── README.md            # This documentation
└── README.md
```

---

## 🧠 Divide & Conquer Algorithm

### How It Works

The tournament winner is found using the D&C pattern:

```
findWinner([P1, P2, P3, P4])
    ├─ DIVIDE: Split into [P1, P2] and [P3, P4]
    │
    ├─ CONQUER (left):  [P1 vs P2] → P2 (winner)
    ├─ CONQUER (right): [P3 vs P4] → P4 (winner)
    │
    └─ COMBINE: P2 vs P4 → TOURNAMENT WINNER!
```

### Algorithm Functions

**1. `findWinner(Player* arr, int left, int right)`**
- **Base case**: Single player returns themselves
- **Divide**: Split array in half
- **Conquer**: Recursively find winner of each half
- **Combine**: Compare sub-winners, return higher score
- **Time**: O(n) - each player compared once
- **Space**: O(log n) - recursion depth

**2. `mergeSort(Player* arr, int left, int right)`**
- Standard D&C merge sort implementation
- Sorts players by score (descending)
- **Time**: O(n log n)
- **Space**: O(n)

**3. `findTopK(Player* arr, int left, int right, int k)`**
- Quickselect algorithm using D&C pattern
- Finds k-th highest scorer efficiently
- **Time**: O(n) average, O(n²) worst
- **Space**: O(log n)

---

## 🔗 API Endpoints

### Base URL
```
http://localhost:8080/api
```

### Endpoints

#### **GET /api/players**
Returns all players in the current tournament
```json
{
  "id": 1,
  "name": "Alice",
  "score": 87,
  "rank": 0
}
```

#### **POST /api/analyze**
Analyzes tournament and returns winner + sorted rankings
```
Request body:
{
  "players": [
    {"name": "Alice", "score": 87},
    {"name": "Bob", "score": 92}
  ]
}

Response:
{
  "winner": {"id": 2, "name": "Bob", "score": 92, "rank": 1},
  "players": [
    {"id": 2, "name": "Bob", "score": 92, "rank": 1},
    {"id": 1, "name": "Alice", "score": 87, "rank": 2}
  ],
  "totalPlayers": 2,
  "algorithm": "Divide and Conquer"
}
```

#### **GET /api/bracket**
Returns tournament bracket information
```json
{
  "totalRounds": 3,
  "winner": {"id": 7, "name": "Grace", "score": 99, "rank": 1},
  "bracketSize": 8
}
```

#### **GET /api/top?k=3**
Returns top-k players by score
```
Query parameter: k (default: 3)

Response:
{
  "k": 3,
  "topPlayers": [
    {"id": 7, "name": "Grace", "score": 99, "rank": 1},
    {"id": 4, "name": "Diana", "score": 95, "rank": 2},
    {"id": 2, "name": "Bob", "score": 92, "rank": 3}
  ]
}
```

---

## 🎨 Frontend Features

### UI Sections

**1. Player Management Panel**
- Add players with name and score
- View player roster with delete buttons
- "Load Sample Data" button (8 pre-loaded players)
- "Analyze Tournament" button (disabled until 2+ players)

**2. Results Dashboard**
- **Winner Card**: Glowing card with trophy animation
- **D&C Steps**: Animated timeline showing algorithm execution
- **Podium**: Visual 1st/2nd/3rd place display
- **Bracket Tree**: SVG-drawn tournament bracket
- **Rankings Table**: All players sorted by score with rank badges
- **Statistics**: Total players, rounds, comparisons

### Theme & Styling
- **Color Palette**: Deep navy (#0a0e1a), gold (#f5c518), crimson (#dc2626)
- **Fonts**: Bebas Neue (headings), Fira Code (data)
- **Effects**: 
  - Animated particle background
  - Glowing text shadows
  - Trophy shake animation on winner reveal
  - Smooth transitions on all interactive elements
  - Responsive layout (desktop & tablet)

### Animations
```
Trophy pulse: 2s infinite
Text glow: 3s ease-in-out infinite
Winner card appear: 0.8s cubic-bezier reveal
Step animations: 600ms staggered delay
Podium bounce: 0.8s-1.1s cubic-bezier
```

---

## 💻 Usage Guide

### Adding Players
1. Enter player name in "Player name" field
2. Enter score (0-100) in "Score" field
3. Click "ADD PLAYER" or press Enter
4. Repeat for multiple players

### Running Analysis
1. Ensure 2+ players are added
2. Click "⚡ ANALYZE TOURNAMENT" button
3. Watch the loading spinner while analyzing
4. Results appear with animations:
   - Winner card glows and trophy shakes
   - D&C steps appear one-by-one (600ms each)
   - Podium animates with bounce effects
   - Bracket tree renders incrementally
   - Rankings table populates with badges

### Viewing Results
- **Winner**: Highlighted in large glowing card
- **Bracket**: SVG tree showing tournament progression
- **Podium**: Visual 1st/2nd/3rd place with medals
- **Rankings**: Sortable table with rank badges
- **Stats**: Algorithm statistics (O(n log n) complexity info)

### Persistent Storage
Players are automatically saved to browser localStorage:
- Survives page refresh
- Available on return visits (same browser)
- Can clear by calling `localStorage.clear()` in console

---

## 🧪 Sample Tournament Data

**Sample players (8-player tournament)**
```
1. Alice      - Score: 87
2. Bob        - Score: 92
3. Charlie    - Score: 78
4. Diana      - Score: 95
5. Eve        - Score: 88
6. Frank      - Score: 71
7. Grace      - Score: 99  ⭐ WINNER
8. Hector     - Score: 84
```

**Expected Results**
- Winner: Grace (99)
- Runner-up: Diana (95)
- 3rd Place: Bob (92)
- Rounds: 3 (log₂ 8)
- Comparisons: 7 (n - 1)

**Load with button**: Click "LOAD SAMPLE DATA" to populate these 8 players

---

## 🔧 Building & Compilation

### Full Build
```bash
cd backend
make all
```

### Clean Build
```bash
make clean
make all
```

### Run Server
```bash
make run
```
Server runs on `http://127.0.0.1:8080`

### Compiler Flags
```
-Wall      # All warnings
-O2        # Optimize for speed
-lm        # Link math library
-lws2_32   # Link Windows sockets (Windows only)
```

---

## 📊 Performance Analysis

### Time Complexity
- **Finding Winner**: O(n) - each player compared once
- **Merge Sort**: O(n log n) - standard merge sort
- **Top-K Selection**: O(n) average - quickselect
- **Overall**: O(n log n) dominated by sorting

### Space Complexity
- **Recursion Depth**: O(log n)
- **Merge Arrays**: O(n)
- **Total**: O(n)

### Scalability
- Tested with 2-100 players
- Instant results for typical tournament sizes
- Bracket visualization optimized for ~16 players
- Can handle larger datasets with UI pagination

---

## 🖥️ System Requirements

### Minimum
- Windows 7+ / macOS 10.12+ / Ubuntu 18.04+
- GCC 4.9+ or Clang 3.5+
- Make 3.82+
- 100 MB disk space
- Modern browser (2020+)

### Recommended
- Windows 10+
- GCC 9.0+
- 500 MB disk space
- Chrome/Edge/Firefox (latest)
- 1080p+ display

---

## 🐛 Troubleshooting

### Backend won't start
```
Error: Address already in use (port 8080)
→ Kill existing process: taskkill /F /IM server.exe (Windows)
→ Change port in api_server.c and rebuild
```

### Compilation fails
```
Error: gcc: command not found
→ Install MinGW or TDM-GCC for Windows
→ Ensure gcc is in PATH: gcc --version
```

### Frontend shows no results
```
Error: Backend unavailable
→ Check server is running: curl http://localhost:8080/api/players
→ Frontend automatically falls back to JavaScript
→ Check browser console for CORS errors
```

### Players not saving
```
Solution: Clear browser storage if localStorage is full
→ Open DevTools (F12) → Application → Clear site data
→ Try again with fewer players
```

---

## 📚 Algorithm Resources

### D&C Pattern
```
1. DIVIDE:   Break problem into subproblems
2. CONQUER:  Solve subproblems recursively
3. COMBINE:  Merge solutions into final answer
```

### Code Walkthrough
See `backend/tournament.c` for implementation:
- Lines 5-25: `findWinner()` - Core D&C tournament logic
- Lines 27-60: `mergeSort()` - Full merge sort implementation
- Lines 62-95: `merge()` - Merge step for combining sorted halves

### Complexity Analysis
- **Best case**: O(n) - winner found early in combine step
- **Average case**: O(n log n) - expected tree height
- **Worst case**: O(n log n) - guaranteed by D&C structure

---

## 🎯 Learning Outcomes

After working with this project, you'll understand:
✅ Divide and Conquer algorithm design pattern  
✅ Recursive algorithm implementation in C  
✅ HTTP server creation with sockets  
✅ JSON serialization and parsing  
✅ Full-stack web application architecture  
✅ Frontend state management (ES6 classes)  
✅ Algorithm complexity analysis (Big-O)  
✅ CORS and HTTP standards  

---

## 📝 License & Attribution

This is an educational project demonstrating fundamental CS concepts.
- Algorithm: Classic Divide & Conquer pattern
- HTTP Server: POSIX socket wrapper
- Frontend: Vanilla JavaScript (no frameworks)

---

## 🤝 Contributing

To extend this project:

1. **Add More Players**: Edit sample data in `app.js`
2. **New Algorithms**: Add to `tournament.c` and expose via API
3. **UI Enhancements**: Modify `style.css` for new effects
4. **Features**:
   - Weighted scoring system
   - Tournament elimination bracket
   - Player statistics tracking
   - Export results to CSV/PDF
   - Multiplayer tournaments (socket.io)

---

## 📞 Support

For issues or questions:
1. Check Troubleshooting section above
2. Review console logs (F12 → Console)
3. Verify backend is running on localhost:8080
4. Test with sample data first

---

**Made with 🏆 for learning Divide & Conquer algorithms**  
*O(n log n) complexity • Full-stack • Production-ready*
