# 👨‍💻 Developer Guide

## Architecture Overview

```
┌─────────────────────────────────────────┐
│         Web Browser (Frontend)          │
│  ┌─────────────────────────────────────┐│
│  │ HTML/CSS/JavaScript                 ││
│  │ - Vanilla JS (no frameworks)        ││
│  │ - Dark theme CSS                    ││
│  │ - D&C algorithm implementation      ││
│  └─────────────────────────────────────┘│
└──────────────────┬──────────────────────┘
                   │ fetch() API calls
                   ↓
┌─────────────────────────────────────────┐
│   HTTP Server (backend/api_server.c)    │
│  ┌─────────────────────────────────────┐│
│  │ POSIX Sockets on port 8080          ││
│  │ - Parse HTTP requests               ││
│  │ - Route to handlers                 ││
│  │ - Return JSON responses             ││
│  └─────────────────────────────────────┘│
└──────────────────┬──────────────────────┘
                   │ function calls
                   ↓
┌─────────────────────────────────────────┐
│   Core Algorithms (backend/tournament.c)│
│  ┌─────────────────────────────────────┐│
│  │ - findWinner() - D&C tournament     ││
│  │ - mergeSort() - Sort by score       ││
│  │ - findTopK() - Top K selection      ││
│  │ - buildBracket() - Bracket gen      ││
│  └─────────────────────────────────────┘│
└─────────────────────────────────────────┘
```

---

## Backend Structure

### Files

**tournament.h** (Header definitions)
```c
struct Player {
    int id;           // Unique identifier
    char name[50];    // Player name
    int score;        // Tournament score
    int rank;         // Final ranking
};

struct TournamentBracket {
    Player* players;  // Player array
    int count;        // Number of players
    Player winner;    // Tournament winner
};
```

**tournament.c** (Algorithm implementations)

#### findWinner() - O(n) time
```
Algorithm: Recursive binary tournament
1. Base Case (n=1): Return single player
2. Divide Step: Split array into left/right halves
3. Conquer Step: Recursively find winner of each half
4. Combine Step: Compare sub-winners, return higher score

Tree structure for 4 players:
                    [P1,P2,P3,P4]
                    /            \
              [P1,P2]            [P3,P4]
              /     \            /     \
             P1     P2          P3     P4
```

#### mergeSort() - O(n log n) time
```
Standard D&C merge sort:
1. Divide: Split array in half
2. Conquer: Recursively sort left and right
3. Combine: Merge sorted halves

Properties:
- Stable sort (maintains order for equal scores)
- O(n) extra space for merging
- Predictable O(n log n) performance
```

#### buildBracket() - Tournament structure
```c
// Populate tournament bracket
// Generate match progression records
// Useful for visualizing tournament rounds
```

**api_server.c** (HTTP server implementation)

#### Request Flow
```
1. Listen on port 8080
2. Accept client connection
3. Read HTTP request
4. Parse method, path, query, body
5. Route to appropriate handler
6. Execute handler function
7. Build JSON response
8. Send response with headers
9. Close connection
```

#### Routes
```
GET  /api/players       → handGetPlayers()
POST /api/analyze       → handleAnalyze()
GET  /api/bracket       → handleGetBracket()
GET  /api/top?k=N       → handleGetTop()
```

---

## Frontend Structure

### Files

**index.html** (DOM structure)
```
<header>          - Logo, title, subtitle
<container>
  <player-panel>  - Add/view/delete players
  <results-panel>
    <winner-card>           - Winner display
    <steps-container>       - D&C animation
    <podium-container>      - Top 3 display
    <bracket-container>     - SVG bracket tree
    <rankings-container>    - Sorted table
    <stats-container>       - Algorithm stats
<footer>          - Attribution
```

**style.css** (700+ lines)
```
Key sections:
1. CSS Variables - Color system, transitions
2. Animations - Trophy pulse, text glow, podium bounce
3. Layout - Grid, flexbox, responsive design
4. Components - Panels, buttons, cards
5. Tables - Rankings display with badges
6. Brackets - SVG styling and positioning
```

**app.js** (JavaScript logic)
```
Class: TournamentApp
├── init()                 - Initialize event listeners
├── addPlayer()            - Add new player
├── deletePlayer()         - Remove player
├── loadSampleData()       - Populate 8 sample players
├── analyze()              - Run analysis
├── analyzeWithBackend()   - Use C server
├── analyzeWithJavaScript()- Fallback D&C
├── findWinner()           - JS D&C implementation
├── mergeSort()            - JS sort implementation
├── renderWinnerCard()     - Display winner
├── renderSteps()          - Animate D&C steps
├── renderPodium()         - Show top 3
├── renderBracket()        - Draw SVG bracket tree
├── renderRankings()       - Build rankings table
├── renderStats()          - Display statistics
├── saveToLocalStorage()   - Persist players
└── loadFromLocalStorage() - Restore players
```

---

## Algorithm Details

### D&C Tournament (findWinner)

**Pseudocode:**
```
function findWinner(arr, left, right):
    // Base case
    if left == right:
        return arr[left]
    
    // Divide
    mid = left + (right - left) / 2
    
    // Conquer
    leftWinner = findWinner(arr, left, mid)
    rightWinner = findWinner(arr, mid+1, right)
    
    // Combine
    if leftWinner.score >= rightWinner.score:
        return leftWinner
    else:
        return rightWinner
```

**Complexity Analysis:**
- Time: T(n) = 2T(n/2) + O(1)
  - By Master Theorem: T(n) = O(n)
- Space: O(log n) recursion depth
- Not O(n log n)! Winner finding is O(n)
- Merge sort for ranking is O(n log n)

**Call Tree (8 players):**
```
Level 0: findWinner([P1..P8])
Level 1: findWinner([P1..P4]) + findWinner([P5..P8])
Level 2: findWinner([P1,P2]) + findWinner([P3,P4]) + ...
Level 3: findWinner([P1]) findWinner([P2]) ... (8 leaf nodes)

Total comparisons: 7 (n-1)
Tree height: 3 (log n)
```

### Merge Sort (mergeSort)

**Pseudocode:**
```
function mergeSort(arr, left, right):
    if left < right:
        mid = left + (right - left) / 2
        mergeSort(arr, left, mid)          // Sort left half
        mergeSort(arr, mid+1, right)       // Sort right half
        merge(arr, left, mid, right)       // Merge halves

function merge(arr, left, mid, right):
    Create temp arrays leftArr, rightArr
    while both arrays have elements:
        if leftArr[i] >= rightArr[j]:
            arr[k++] = leftArr[i++]
        else:
            arr[k++] = rightArr[j++]
    Copy remaining elements
```

**Key Points:**
- O(n log n) guaranteed complexity
- Stable sort (equal scores maintain order)
- Divide: O(1) - just calculate midpoint
- Merge: O(n) - compare and copy
- Overall: O(n log n) = n comparisons per level × log n levels

---

## Extending the Code

### Adding a New Algorithm

**Example: Find max K-scorer**

1. Add to `tournament.h`:
```c
Player findMaxScorer(Player* arr, int left, int right);
```

2. Implement in `tournament.c`:
```c
Player findMaxScorer(Player* arr, int left, int right) {
    if (left == right) return arr[left];
    
    int mid = left + (right - left) / 2;
    Player leftMax = findMaxScorer(arr, left, mid);
    Player rightMax = findMaxScorer(arr, mid+1, right);
    
    return (leftMax.score > rightMax.score) ? leftMax : rightMax;
}
```

3. Add API endpoint in `api_server.c`:
```c
else if (strstr(path, "/api/maxscorer")) {
    return handleGetMaxScorer();
}

char* handleGetMaxScorer() {
    Player max = findMaxScorer(db.players, 0, db.count-1);
    char* json = playerToJson(max);
    return buildJsonResponse(json);
}
```

### Adding JavaScript D&C Visualization

**Example: Show divide steps**

```javascript
// In app.js
visualizeDivide(arr, left, right, depth) {
    if (left === right) return;
    
    const mid = Math.floor(left + (right - left) / 2);
    const indent = "  ".repeat(depth);
    
    console.log(`${indent}DIVIDE [${arr[left].name}..${arr[right].name}]`);
    console.log(`${indent}├─ Left  [${arr[left].name}..${arr[mid].name}]`);
    console.log(`${indent}└─ Right [${arr[mid+1].name}..${arr[right].name}]`);
    
    this.visualizeDivide(arr, left, mid, depth + 1);
    this.visualizeDivide(arr, mid + 1, right, depth + 1);
}
```

### Adding New UI Features

**Example: Add player search**

1. Add to `index.html`:
```html
<input id="searchInput" placeholder="Search players">
<div id="searchResults"></div>
```

2. Add to `app.js`:
```javascript
searchPlayers(query) {
    return this.players.filter(p => 
        p.name.toLowerCase().includes(query.toLowerCase())
    );
}
```

3. Add to `style.css`:
```css
#searchResults {
    /* styling */
}
```

---

## Testing

### Manual Testing

**Test Plan:**
```
1. Load with 2 players
   - Run analysis
   - Verify winner

2. Load with 8 sample players
   - Check Grace wins (score 99)
   - Verify bracket visualization
   - Check rankings are sorted

3. Add custom players
   - Names with spaces
   - Scores at boundaries (0, 100)
   - Duplicate names

4. Test without backend
   - Stop server
   - Run analysis
   - Should use JavaScript fallback
```

### Backend Testing

**Test API endpoints:**
```bash
# Get players
curl http://localhost:8080/api/players

# Get top 3
curl "http://localhost:8080/api/top?k=3"

# Analyze
curl -X POST http://localhost:8080/api/analyze \
  -H "Content-Type: application/json" \
  -d '{"players":[{"name":"A","score":50},{"name":"B","score":60}]}'
```

### Frontend Testing

**Browser Console:**
```javascript
// Test the app directly
app.addPlayer("TestPlayer", 75);
app.analyze();
console.log(app.winner);
console.log(app.players);
```

---

## Performance Optimization

### Current Bottlenecks
```
1. SVG bracket drawing: O(n) for n players
   - Solution: Use canvas or limit to 16 players
   
2. Array copying in JavaScript: O(n)
   - Solution: Use typed arrays or references
   
3. Network latency: Variable
   - Solution: Reduce response size, cache results
```

### Optimization Opportunities
```
1. Memoization
   - Cache sub-problem results
   - Skip redundant calculations

2. Iterative approach
   - Replace recursion with iteration
   - Reduce stack overhead

3. Batch operations
   - Process multiple tournaments
   - Parallel analysis

4. HTML5 Web Workers
   - Run D&C in separate thread
   - Keep UI responsive
```

---

## Debugging

### Backend Debugging

**Print debug info in tournament.c:**
```c
printf("DEBUG: Comparing %s(%d) vs %s(%d)\n", 
       left.name, left.score, right.name, right.score);
```

**Check HTTP requests in api_server.c:**
```c
printf("Request: %s %s\n", method, path);
printf("Body: %s\n", body);
```

### Frontend Debugging

**Chrome DevTools:**
```
1. F12 to open DevTools
2. Console tab for logs
3. Network tab to see API calls
4. Elements tab to inspect DOM
5. Sources tab for breakpoints
```

**Debug in code:**
```javascript
console.log('DEBUG:', this.winner, this.players);
debugger; // Breakpoint in DevTools
```

---

## Code Quality

### Checklist
- ✅ Functions have clear purposes
- ✅ Variables have descriptive names
- ✅ Comments explain algorithm logic
- ✅ Input validation is present
- ✅ Memory is properly managed
- ✅ No buffer overflows
- ✅ Follows C89/C99 standards
- ✅ CSS uses variables for colors
- ✅ JavaScript uses modern syntax
- ✅ Responsive design for all screens

### Standards Followed
- **C**: POSIX socket API, standard library
- **JavaScript**: ES6 classes, modern DOM APIs
- **CSS**: CSS custom properties, flexbox/grid
- **HTML**: Semantic markup, accessibility

---

## Future Enhancements

### Short Term
- [ ] Add more sorting algorithms (quick sort, heap sort)
- [ ] Implement parallel processing
- [ ] Add undo/redo functionality
- [ ] Export results to CSV

### Medium Term
- [ ] Real-time multiplayer tournaments
- [ ] Tournament brackets with eliminations
- [ ] Player statistics tracking
- [ ] Leaderboard system

### Long Term
- [ ] Machine learning ranking
- [ ] Tournament predictions
- [ ] Mobile app (React Native)
- [ ] Cloud deployment

---

## Contributing

### Code Style
```c
// C Code
function_name_style();
CONSTANT_STYLE = 0;
structName myVar;

variable_naming_style;
```

```javascript
// JavaScript
className {}
functionName() {}
variableName;
CONSTANT_NAME;
const MY_CONSTANT = 0;
```

### Commit Messages
```
[feature] Add quickselect algorithm
[fix] Handle empty player list
[refactor] Extract sorting logic
[docs] Update API documentation
[test] Add edge case tests
```

---

## Resources

### D&C Algorithm Learning
- Introduction to Algorithms (CLRS)
- Algorithm Design (Kleinberg & Tardos)
- YouTube: MIT 6.006 - Divide and Conquer

### Web Development
- MDN Web Docs (https://developer.mozilla.org)
- HTML5 Standard (https://html.spec.whatwg.org)
- CSS Specifications (https://www.w3.org/Style/CSS/)

### C Programming
- The C Programming Language (K&R)
- C Pointers and Dynamic Memory
- POSIX Sockets Programming

---

## Support

- **Issues**: Check browser console (F12)
- **Compilation**: See WINDOWS_SETUP.md
- **Algorithm**: Read README.md algorithm section
- **Code Review**: Check source comments

---

**Happy coding! 🚀**
