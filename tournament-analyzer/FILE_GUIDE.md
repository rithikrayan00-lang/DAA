# 📁 Project File Structure & Guide

## Complete Directory Map

```
tournament-analyzer/
│
├── README.md                    (📖 Full documentation)
├── GETTING_STARTED.md           (🚀 Quick start guide)
├── WINDOWS_SETUP.md             (🪟 Windows installation)
├── DEVELOPMENT.md               (👨‍💻 Developer guide)
└── FILE_GUIDE.md                (This file)
│
├── backend/
│   ├── tournament.h             (💾 Data structures & declarations)
│   ├── tournament.c             (🧠 D&C algorithm implementations)
│   ├── api_server.c             (🌐 HTTP server & routing)
│   ├── Makefile                 (🔨 Build configuration)
│   ├── build.bat                (⚙️ Windows build script)
│   ├── build.ps1                (⚙️ PowerShell build script)
│   ├── run.bat                  (▶️ Windows run script)
│   └── run.ps1                  (▶️ PowerShell run script)
│
└── frontend/
    ├── index.html               (🎨 DOM structure & layout)
    ├── style.css                (🎭 Styling & animations)
    ├── app.js                   (⚡ Logic & D&C in JavaScript)
    └── README.md                (📋 Frontend documentation)
```

---

## File Descriptions

### 📄 Root Documentation

| File | Purpose | Audience |
|------|---------|----------|
| **README.md** | Complete project documentation, API reference, algorithm explanation | Everyone |
| **GETTING_STARTED.md** | 5-minute quick start guide | New users |
| **WINDOWS_SETUP.md** | Step-by-step Windows installation with troubleshooting | Windows users |
| **DEVELOPMENT.md** | Architecture, code walkthrough, extension guide | Developers |
| **FILE_GUIDE.md** | This file - project structure overview | Everyone |

---

### 🧠 Backend Files

#### **tournament.h** (112 lines)
```c
Purpose: Header file with structure definitions and function declarations
Defines:
  - Player struct (id, name, score, rank)
  - TournamentBracket struct (players, count, winner)
  - AnalysisResult struct (winners, steps)
Functions declared:
  - findWinner()          - Core D&C tournament logic
  - mergeSort()           - O(n log n) merge sort
  - findTopK()            - Quickselect for top-K
  - buildBracket()        - Tournament bracket generation
  - Utility functions
```

#### **tournament.c** (180 lines)
```c
Purpose: Core algorithm implementations using Divide & Conquer
Key functions:
  1. findWinner(left, right)
     - Time: O(n) - compares each player once
     - Recursively finds tournament winner
     - Base case: single player returns themselves
     - Divide: split array in half
     - Conquer: recursively find winner of each half
     - Combine: compare winners, return higher score
  
  2. mergeSort(left, right)
     - Time: O(n log n)
     - Sorts players by score (descending)
     - Used for final rankings
  
  3. merge(left, mid, right)
     - Helper for merge sort
     - Combines two sorted arrays
  
  4. findTopK(left, right, k)
     - Time: O(n) average
     - Quickselect algorithm
     - Finds k-th highest scorer
  
  5. buildBracket(arr, n, bracket)
     - Initializes bracket structure
     - Populates winner
  
  6. Utility functions
     - initPlayer(): Create player
     - printPlayer(): Debug output
     - sortPlayersByScore(): Rank players
```

#### **api_server.c** (400+ lines)
```c
Purpose: HTTP server implementation with JSON API
Architecture:
  - POSIX sockets binding (port 8080)
  - HTTP request parsing
  - JSON generation
  - Request routing & handling
  
Key sections:
  1. JSON Utilities
     - jsonEscapeString(): Escape JSON strings
     - playerToJson(): Convert player to JSON
     - playersArrayToJson(): Convert array to JSON
  
  2. Response Builders
     - buildJsonResponse(): Wrap data in HTTP response
     - buildErrorResponse(): Error messages
  
  3. Request Parsers
     - parsePlayerFromJson(): Extract player from JSON
     - parsePlayerFromJsonFromPtr(): Parse player object
  
  4. Route Handlers
     - handleGetPlayers(): GET /api/players
     - handleAnalyze(): POST /api/analyze
     - handleGetBracket(): GET /api/bracket
     - handleGetTop(): GET /api/top?k=N
  
  5. Request Router
     - routeRequest(): Main routing logic
     - Handles OPTIONS for CORS preflight
  
  6. Main Server Loop
     - WSAStartup(): Initialize Windows sockets
     - socket(), bind(), listen(): Setup server
     - accept(), recv(), send(): Handle connections
     - Infinite loop accepting clients
```

#### **Makefile** (25 lines)
```makefile
Purpose: Build configuration for Unix/Linux/macOS
Targets:
  - all: Build server executable (default)
  - %.o: Compile .c to .o object files
  - run: Build and run server
  - clean: Remove build artifacts
  - help: Show available targets
Variables:
  - CC: Compiler (gcc)
  - CFLAGS: Compiler flags (-Wall -O2)
  - LDFLAGS: Linker flags (-lm -lws2_32)
  - SRCS: Source files
  - OBJS: Object files
  - TARGET: Output executable
```

#### **build.bat** (35 lines)
```batch
Purpose: Windows batch script for building
Features:
  - Checks if GCC is installed
  - Provides installation instructions if missing
  - Compiles with appropriate flags
  - Reports success/failure
Usage: build.bat
```

#### **build.ps1** (50 lines)
```powershell
Purpose: PowerShell script for building (alternative to batch)
Features:
  - Color-coded output
  - GCC availability check
  - Detailed error messages
  - Installation guidance
Usage: .\build.ps1
```

#### **run.bat** (20 lines)
```batch
Purpose: Windows script to build and run server
Features:
  - Auto-builds if needed
  - Starts server on port 8080
  - Shows connection info
Usage: run.bat
```

#### **run.ps1** (30 lines)
```powershell
Purpose: PowerShell script to build and run server
Features:
  - Automatic build if needed
  - Color-coded output
  - Error handling
Usage: .\run.ps1
```

---

### 🎨 Frontend Files

#### **index.html** (180 lines)
```html
Purpose: Main UI structure and layout
Sections:
  1. Head
     - Meta tags for viewport & charset
     - Font imports (Bebas Neue, Fira Code)
     - CSS stylesheet link
  
  2. Header
     - Logo (trophy emoji)
     - Title "TOURNAMENT ANALYZER"
     - Subtitle with algorithm info
  
  3. Main Container (2-column layout)
     Left Column: Player Management Panel
       - Add player form (name + score inputs)
       - Button group (ADD, LOAD SAMPLE)
       - Player roster (scrollable list)
       - ANALYZE TOURNAMENT button
     
     Right Column: Results Panel
       - Winner card (glowing, animated)
       - D&C steps animation timeline
       - Top 3 podium visualization
       - SVG tournament bracket
       - Rankings table with badges
       - Statistics box grid
  
  4. Footer
     - Attribution text
  
  5. Loading Spinner
     - Hidden by default
     - Shows during analysis
  
DOM Structure optimized for:
  - Visibility toggling (display: none/block)
  - CSS animations
  - JavaScript manipulation
```

#### **style.css** (900+ lines)
```css
Purpose: Complete styling without frameworks
Organization:
  1. CSS Variables (Color system)
     - Primary colors: navy, gold, crimson, white
     - Secondary: grey, success, warning, info
     - Transitions & animations
  
  2. Base Styles
     - Reset (*, body, html)
     - Typography defaults
  
  3. Background Animations
     - Particle float animation
     - Radial gradients
  
  4. Header Styling
     - Logo glow effects
     - Title text-shadow glow
     - Trophy pulse animation
  
  5. Layout
     - Container grid (2-column → 1 on mobile)
     - Panel styling (dark theme)
     - Responsive breakpoints
  
  6. Components
     - Forms: input fields with focus states
     - Buttons: primary, secondary, analyze
     - Cards: winner card with animations
     - Tables: rankings with hover effects
     - Podium: visual 1st/2nd/3rd display
  
  7. Animations
     - float-particles: 20s cycle
     - trophy-pulse: 2s infinite
     - glow-text: 3s infinite
     - winnerCardAppear: 0.8s on reveal
     - trophy-shake: 0.6s celebration
     - podiumBounce: staggered entrance
     - stepAppear: 0.6s animation
  
  8. Responsive Design
     - Desktop: Full 2-column
     - Tablet: 1-column, optimized
     - Mobile: Adjusted font sizes
  
  9. Scrollbar Styling
     - Custom colors matching theme
     - Dark gold styling
```

#### **app.js** (500+ lines)
```javascript
Purpose: Frontend logic, API interaction, and D&C visualization
Class: TournamentApp

Properties:
  - players[]           : Array of player objects
  - brackets[]          : Tournament bracket data
  - winner              : Current winner object
  - steps[]             : D&C animation steps
  - apiUrl              : Backend API base URL
  - backendAvailable    : Connection status flag

Methods - Initialization:
  - init()                      : Setup event listeners
  - checkBackendAvailability()  : Test connection

Methods - Player Management:
  - addPlayer()        : Add new player
  - deletePlayer()     : Remove player
  - loadSampleData()   : Fill with 8 sample players
  - renderRoster()     : Update player list HTML
  - updateAnalyzeButton() : Enable/disable button

Methods - D&C Algorithms (JavaScript):
  - findWinner(arr, left, right, steps) : Core D&C
  - mergeSort(arr, left, right) : Sort players
  - merge(arr, left, mid, right) : Merge helper

Methods - Analysis:
  - analyze()              : Main orchestrator
  - analyzeWithBackend()   : Call C API
  - analyzeWithJavaScript(): Fallback JS D&C
  - displayResults()       : Show all result views

Methods - Rendering:
  - renderWinnerCard()    : Glowing winner display
  - renderSteps()         : Animated D&C steps
  - renderPodium()        : Top 3 medals
  - renderBracket()       : Draw SVG tree
  - drawBracketTree()     : Recursive SVG drawing
  - renderRankings()      : Results table
  - renderStats()         : Statistics display
  - resetResults()        : Clear all results
  - showLoadingSpinner()  : Toggle spinner

Methods - Local Storage:
  - saveToLocalStorage()   : Persist players
  - loadFromLocalStorage() : Restore players

Features:
  - Automatic fallback if backend unreachable
  - D&C animation with 600ms step delays
  - Color-coded steps (divide/conquer/combine)
  - SVG bracket tree visualization
  - Responsive podium animation
  - Full localStorage support

Initialization:
  - DOMContentLoaded listener
  - Creates global `app` instance
  - Loads saved players
  - Tests backend connection
```

---

## Size & Complexity

| File | Lines | Purpose | Complexity |
|------|-------|---------|-----------|
| tournament.h | 45 | Headers | Simple |
| tournament.c | 180 | Algorithms | Medium |
| api_server.c | 400 | HTTP Server | High |
| index.html | 180 | DOM | Medium |
| style.css | 950 | Styling | Medium |
| app.js | 500 | Logic | Medium |
| **Total Backend** | **625** | **C Code** | **High** |
| **Total Frontend** | **1630** | **Web UI** | **Medium** |

---

## Dependencies

### Backend (C)
```
Standard Library:
  - stdio.h    : I/O functions
  - stdlib.h   : Memory allocation
  - string.h   : String operations
  - ctype.h    : Character functions
  - math.h     : Math operations (log2)
  
Windows-Specific:
  - winsock2.h : Socket API
  - ws2tcpip.h : TCP/IP
  
Linker Flags:
  - -lm       : Math library (log2, etc.)
  - -lws2_32  : Windows socket library
```

### Frontend
```
No external dependencies!

Using only:
  - Vanilla HTML5
  - CSS3 (modern browser)
  - ECMAScript 2015 (ES6)
  - Fetch API (for HTTP)
  - SVG (for bracket)
  - localStorage API
  
Fonts (from CDN):
  - Bebas Neue (Google Fonts)
  - Fira Code (Google Fonts)
```

---

## How to Use Each File

### For Running
```
1. Backend Setup
   ├─ Read: WINDOWS_SETUP.md (if on Windows)
   ├─ Run: build.bat or build.ps1
   └─ Run: run.bat or run.ps1

2. Frontend
   └─ Open: index.html in browser
```

### For Development
```
1. Understanding Algorithm
   ├─ Read: tournament.h (data structures)
   ├─ Read: tournament.c (implementation)
   └─ Read: app.js lines 90-140 (JS version)

2. Understanding API
   ├─ Read: api_server.c routes section
   └─ Check: README.md API Endpoints

3. Understanding UI
   ├─ Read: index.html structure
   ├─ Read: style.css components
   └─ Read: app.js render methods

4. Extending Code
   └─ Read: DEVELOPMENT.md "Extending the Code"
```

### For Debugging
```
1. Compilation Errors
   └─ Read: WINDOWS_SETUP.md Troubleshooting

2. Runtime Errors
   ├─ Check: Browser console (F12)
   └─ Check: Backend terminal output

3. Algorithm Issues
   ├─ Add: printf() in tournament.c
   ├─ Add: console.log() in app.js
   └─ Read: DEVELOPMENT.md Debugging section
```

---

## File Size Reference

```
Backend executable (server.exe after compilation):
  - Debug build: ~200-300 KB
  - Release build: ~50-100 KB
  - Size includes: algorithms, HTTP server, core libs

Frontend files (uncompressed):
  - index.html: ~8 KB
  - style.css: ~40 KB
  - app.js: ~25 KB
  - Total size: ~73 KB

Typical browser load:
  - Initial: ~80 KB (all files + fonts)
  - Memory: ~5-10 MB (app running)
  - Network: <1s (localhost), ~2-3s (internet)
```

---

## Build Artifacts

After compilation, these files appear:
```
backend/
├── tournament.o    (Object file, ~10 KB)
├── api_server.o    (Object file, ~20 KB)
└── server.exe      (Executable, ~100-200 KB)
```

To clean:
```
make clean          (on Unix/Linux/Mac)
build.bat clean     (Windows)
```

---

## Read Order Recommendation

### For Quick Start
1. GETTING_STARTED.md
2. index.html (skim)
3. Try the app!

### For Understanding
1. README.md (overview)
2. tournament.h (data structures)
3. tournament.c (algorithm logic)
4. app.js (D&C in JavaScript)
5. index.html (DOM structure)
6. style.css (styling)

### For Development
1. DEVELOPMENT.md (architecture)
2. All source files (with comments)
3. TEST with modifications

---

## Checklist Before Distribution

- ✅ All source files present
- ✅ All README files included
- ✅ Build scripts working (batch & PowerShell)
- ✅ Frontend works without backend
- ✅ No hardcoded paths
- ✅ No external dependencies (except fonts)
- ✅ Clean code with comments
- ✅ Responsive design tested
- ✅ Algorithms documented

---

## Project Statistics

```
Total Files: 15
Total Lines of Code: 2,255+
Languages: C, JavaScript, HTML, CSS, Batch, PowerShell, Markdown

Backend:
  - Lines: 625+
  - Functions: 20+
  - Algorithms: 3 (findWinner, mergeSort, findTopK)

Frontend:
  - Lines: 1,630+
  - Methods: 25+
  - Animations: 10+
  - CSS Variables: 15+

Documentation:
  - Files: 5 markdown guides
  - Pages: 50+ detailed pages

Complexity: Medium
Performance: O(n log n)
Scalability: 2-1000 players
```

---

## Support & Troubleshooting

For issues with specific files:
- **Compilation**: WINDOWS_SETUP.md
- **API Usage**: README.md → API Endpoints
- **Algorithm**: README.md → Algorithm section
- **Code Understanding**: DEVELOPMENT.md
- **Frontend Issues**: Check console (F12)
- **Extension Ideas**: DEVELOPMENT.md → Extending

---

**Happy exploring! 🏆**
