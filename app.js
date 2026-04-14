/* ==========================================
 * Tournament Analyzer - Frontend
 * ========================================== */

class TournamentApp {
    constructor() {
        this.players = [];
        this.winner = null;
        this.steps = [];
        this.apiUrl = 'http://localhost:3000/api';
        this.backendAvailable = false;
        this.isLoggedIn = false;
        this.currentUser = null;
        this.init();
    }

    init() {
        // Setup login form
        const loginForm = document.getElementById('loginForm');
        if (loginForm) {
            loginForm.addEventListener('submit', (e) => {
                e.preventDefault();
                this.handleLogin();
            });
        }
        
        // Setup logout button
        const logoutBtn = document.getElementById('logoutBtn');
        if (logoutBtn) {
            logoutBtn.addEventListener('click', () => this.handleLogout());
        }
        
        // Check if user is already logged in
        const savedUser = localStorage.getItem('currentUser');
        if (savedUser) {
            this.isLoggedIn = true;
            this.currentUser = savedUser;
            this.showApp();
        } else {
            this.showLogin();
        }
    }

    handleLogin() {
        const username = document.getElementById('username').value.trim();
        const password = document.getElementById('password').value.trim();
        
        if (!username) {
            alert('Please enter username');
            return;
        }
        if (!password) {
            alert('Please enter password');
            return;
        }
        
        // Simple authentication (for demo)
        localStorage.setItem('currentUser', username);
        this.isLoggedIn = true;
        this.currentUser = username;
        
        // Clear login form
        document.getElementById('loginForm').reset();
        
        // Show app
        this.showApp();
    }

    handleLogout() {
        this.isLoggedIn = false;
        this.currentUser = null;
        localStorage.removeItem('currentUser');
        this.players = [];
        localStorage.removeItem('players');
        this.showLogin();
    }

    showLogin() {
        document.getElementById('loginModal').classList.remove('hidden');
        document.getElementById('mainHeader').style.display = 'none';
        document.getElementById('mainContainer').style.display = 'none';
        document.getElementById('mainFooter').style.display = 'none';
    }

    showApp() {
        document.getElementById('loginModal').classList.add('hidden');
        document.getElementById('mainHeader').style.display = 'block';
        document.getElementById('mainContainer').style.display = 'grid';
        document.getElementById('mainFooter').style.display = 'block';
        
        // Load saved players
        this.loadFromLocalStorage();
        
        // Event listeners for app
        if (!document.getElementById('addPlayerBtn').dataset.listenersInitialized) {
            document.getElementById('addPlayerBtn').addEventListener('click', () => this.addPlayer());
            document.getElementById('playerNameInput').addEventListener('keypress', (e) => {
                if (e.key === 'Enter') this.addPlayer();
            });
            document.getElementById('playerScoreInput').addEventListener('keypress', (e) => {
                if (e.key === 'Enter') this.addPlayer();
            });
            document.getElementById('loadSampleBtn').addEventListener('click', () => this.loadSampleData());
            document.getElementById('analyzeBtn').addEventListener('click', () => this.analyze());
            document.getElementById('addPlayerBtn').dataset.listenersInitialized = true;
        }

        // Check backend availability
        this.checkBackendAvailability();
    }

    checkBackendAvailability() {
        fetch(`${this.apiUrl}/players`)
            .then(() => {
                this.backendAvailable = true;
                console.log('✓ Backend available');
            })
            .catch(() => {
                this.backendAvailable = false;
                console.log('⚠ Backend unavailable - using JavaScript fallback');
            });
    }

    /* ==========================================
     * Player Management
     * ========================================== */
    addPlayer() {
        const nameInput = document.getElementById('playerNameInput');
        const scoreInput = document.getElementById('playerScoreInput');
        const name = nameInput.value.trim();
        const score = parseInt(scoreInput.value);

        if (!name) {
            alert('Please enter player name');
            return;
        }

        if (isNaN(score) || score < 0 || score > 100) {
            alert('Please enter valid score (0-100)');
            return;
        }

        const player = {
            id: this.players.length + 1,
            name: name,
            score: score,
            rank: 0
        };

        this.players.push(player);
        this.saveToLocalStorage();
        this.renderRoster();
        
        nameInput.value = '';
        scoreInput.value = '';
        nameInput.focus();

        this.updateAnalyzeButton();
    }

    deletePlayer(id) {
        this.players = this.players.filter(p => p.id !== id);
        this.saveToLocalStorage();
        this.renderRoster();
        this.resetResults();
        this.updateAnalyzeButton();
    }

    loadSampleData() {
        const samplePlayers = [
            { name: 'Alice', score: 87 },
            { name: 'Bob', score: 92 },
            { name: 'Charlie', score: 78 },
            { name: 'Diana', score: 95 },
            { name: 'Eve', score: 88 },
            { name: 'Frank', score: 71 },
            { name: 'Grace', score: 99 },
            { name: 'Hector', score: 84 }
        ];

        this.players = samplePlayers.map((p, idx) => ({
            id: idx + 1,
            name: p.name,
            score: p.score,
            rank: 0
        }));

        this.saveToLocalStorage();
        this.renderRoster();
        this.updateAnalyzeButton();
    }

    renderRoster() {
        const roster = document.getElementById('playerRoster');
        
        if (this.players.length === 0) {
            roster.innerHTML = '<p class="empty-state">No players added yet</p>';
            return;
        }

        roster.innerHTML = this.players.map(p => `
            <div class="player-row">
                <div class="player-info">
                    <div class="player-name">${p.name}</div>
                    <div class="player-score">Score: ${p.score}</div>
                </div>
                <button class="player-delete-btn" onclick="app.deletePlayer(${p.id})">REMOVE</button>
            </div>
        `).join('');
    }

    updateAnalyzeButton() {
        const btn = document.getElementById('analyzeBtn');
        btn.disabled = this.players.length < 2;
    }

    /* ==========================================
     * D&C Algorithms (JavaScript Implementation)
     * ========================================== */
    findWinner(arr, left, right, steps) {
        if (left === right) {
            return arr[left];
        }

        const mid = Math.floor(left + (right - left) / 2);
        
        steps.push({
            type: 'divide',
            content: `DIVIDE: [${arr.slice(left, mid + 1).map(p => p.name).join(', ')}] | [${arr.slice(mid + 1, right + 1).map(p => p.name).join(', ')}]`
        });

        const leftWinner = this.findWinner(arr, left, mid, steps);
        const rightWinner = this.findWinner(arr, mid + 1, right, steps);

        steps.push({
            type: 'conquer',
            content: `CONQUER: ${leftWinner.name}(${leftWinner.score}) vs ${rightWinner.name}(${rightWinner.score})`
        });

        const winner = leftWinner.score >= rightWinner.score ? leftWinner : rightWinner;
        
        steps.push({
            type: 'combine',
            content: `COMBINE: Winner → ${winner.name}(${winner.score})`
        });

        return winner;
    }

    mergeSort(arr, left, right) {
        if (left < right) {
            const mid = Math.floor(left + (right - left) / 2);
            this.mergeSort(arr, left, mid);
            this.mergeSort(arr, mid + 1, right);
            this.merge(arr, left, mid, right);
        }
        return arr;
    }

    merge(arr, left, mid, right) {
        const leftArr = arr.slice(left, mid + 1);
        const rightArr = arr.slice(mid + 1, right + 1);
        
        let i = 0, j = 0, k = left;
        
        while (i < leftArr.length && j < rightArr.length) {
            if (leftArr[i].score >= rightArr[j].score) {
                arr[k++] = leftArr[i++];
            } else {
                arr[k++] = rightArr[j++];
            }
        }
        
        while (i < leftArr.length) {
            arr[k++] = leftArr[i++];
        }
        
        while (j < rightArr.length) {
            arr[k++] = rightArr[j++];
        }
    }

    /* ==========================================
     * Analysis
     * ========================================== */
    async analyze() {
        if (this.players.length === 0) return;

        this.showLoadingSpinner(true);
        this.resetResults();

        try {
            if (this.backendAvailable) {
                await this.analyzeWithBackend();
            } else {
                this.analyzeWithJavaScript();
            }
        } catch (error) {
            console.error('Analysis error:', error);
            this.analyzeWithJavaScript();
        }

        this.showLoadingSpinner(false);
    }

    async analyzeWithBackend() {
        const payload = {
            players: this.players.map(p => ({
                name: p.name,
                score: p.score
            }))
        };

        try {
            const response = await fetch(`${this.apiUrl}/analyze`, {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify(payload)
            });

            if (!response.ok) throw new Error('Backend error');
            
            const data = await response.json();
            this.winner = data.winner;
            
            // Sort players by score
            this.players.sort((a, b) => b.score - a.score);
            this.players.forEach((p, idx) => { p.rank = idx + 1; });

            this.displayResults();
        } catch (error) {
            console.error('Backend analysis failed:', error);
            throw error;
        }
    }

    analyzeWithJavaScript() {
        // Make a copy to avoid modifying original
        const playersCopy = JSON.parse(JSON.stringify(this.players));
        
        // Find winner using D&C
        this.steps = [];
        this.winner = this.findWinner(playersCopy, 0, playersCopy.length - 1, this.steps);

        // Sort by score
        this.players.sort((a, b) => b.score - a.score);
        this.players.forEach((p, idx) => { p.rank = idx + 1; });

        this.displayResults();
    }

    displayResults() {
        this.renderWinnerCard();
        this.renderSteps();
        this.renderPodium();
        this.renderRankings();
        this.renderStats();
        this.renderScoreChart();
        this.renderComparisonChart();
        this.renderFlowchart();
    }

    /* ==========================================
     * Result Rendering
     * ========================================== */
    renderWinnerCard() {
        const container = document.getElementById('winnerCardContainer');
        document.getElementById('winnerName').textContent = this.winner.name;
        document.getElementById('winnerScore').textContent = `Score: ${this.winner.score}`;
        container.style.display = 'block';
    }

    renderSteps() {
        const container = document.getElementById('stepsContainer');
        const stepsList = document.getElementById('stepsList');
        
        if (this.steps.length === 0) {
            container.style.display = 'none';
            return;
        }

        container.style.display = 'block';
        stepsList.innerHTML = '';

        this.steps.forEach((step, idx) => {
            setTimeout(() => {
                const stepEl = document.createElement('div');
                stepEl.className = 'step-item';
                stepEl.innerHTML = `
                    <div class="step-type ${step.type}">${step.type}</div>
                    <div class="step-content">${step.content}</div>
                `;
                stepsList.appendChild(stepEl);
                stepsList.scrollTop = stepsList.scrollHeight;
            }, idx * 600);
        });
    }

    renderPodium() {
        const container = document.getElementById('podiumContainer');
        if (this.players.length < 3) {
            container.style.display = 'none';
            return;
        }

        container.style.display = 'block';

        const top3 = this.players.slice(0, 3);
        if (top3.length >= 1) {
            document.getElementById('podium1').textContent = top3[0].name;
            document.getElementById('podium1-score').textContent = top3[0].score;
        }
        if (top3.length >= 2) {
            document.getElementById('podium2').textContent = top3[1].name;
            document.getElementById('podium2-score').textContent = top3[1].score;
        }
        if (top3.length >= 3) {
            document.getElementById('podium3').textContent = top3[2].name;
            document.getElementById('podium3-score').textContent = top3[2].score;
        }
    }

    renderRankings() {
        const container = document.getElementById('rankingsContainer');
        const table = document.getElementById('rankingsTable');

        if (this.players.length === 0) {
            container.style.display = 'none';
            return;
        }

        container.style.display = 'block';

        let html = '<div class="rankings-header">' +
            '<div>Rank</div>' +
            '<div>Player</div>' +
            '<div>Score</div>' +
            '<div>Status</div>' +
            '</div>';

        this.players.forEach((p, idx) => {
            let status = idx === 0 ? '🥇 WINNER' : idx === 1 ? '🥈 RUNNER-UP' : idx === 2 ? '🥉 3RD PLACE' : '';
            html += `<div class="rankings-row">
                <div><span class="rank-badge">${idx + 1}</span></div>
                <div class="rank-name">${p.name}</div>
                <div class="rank-score">${p.score}</div>
                <div>${status}</div>
            </div>`;
        });

        table.innerHTML = html;
    }

    renderStats() {
        const container = document.getElementById('statsContainer');
        container.style.display = 'block';

        const totalPlayers = this.players.length;
        const rounds = Math.ceil(Math.log2(totalPlayers));
        const comparisons = totalPlayers - 1;

        document.getElementById('statPlayers').textContent = totalPlayers;
        document.getElementById('statRounds').textContent = rounds;
        document.getElementById('statComparisons').textContent = comparisons;
    }

    renderScoreChart() {
        const container = document.getElementById('scoreChartContainer');
        if (this.players.length === 0) {
            container.style.display = 'none';
            return;
        }

        container.style.display = 'block';
        const ctx = document.getElementById('scoreChart').getContext('2d');
        
        // Destroy existing chart if it exists
        if (this.scoreChartInstance) {
            this.scoreChartInstance.destroy();
        }

        this.scoreChartInstance = new Chart(ctx, {
            type: 'bar',
            data: {
                labels: this.players.map(p => p.name),
                datasets: [{
                    label: 'Player Scores',
                    data: this.players.map(p => p.score),
                    backgroundColor: this.players.map((p, idx) => {
                        if (idx === 0) return 'rgba(245, 197, 24, 0.8)';
                        if (idx === 1) return 'rgba(192, 192, 192, 0.8)';
                        if (idx === 2) return 'rgba(205, 127, 50, 0.8)';
                        return 'rgba(16, 185, 129, 0.8)';
                    }),
                    borderColor: 'rgba(255, 255, 255, 0.5)',
                    borderWidth: 2,
                    borderRadius: 5
                }]
            },
            options: {
                responsive: true,
                maintainAspectRatio: true,
                plugins: {
                    legend: {
                        labels: {
                            color: 'rgba(255, 255, 255, 0.8)',
                            font: { size: 12 }
                        }
                    }
                },
                scales: {
                    y: {
                        beginAtZero: true,
                        max: 100,
                        ticks: { color: 'rgba(255, 255, 255, 0.6)' },
                        grid: { color: 'rgba(255, 255, 255, 0.1)' }
                    },
                    x: {
                        ticks: { color: 'rgba(255, 255, 255, 0.6)' },
                        grid: { color: 'rgba(255, 255, 255, 0.1)' }
                    }
                }
            }
        });
    }

    renderComparisonChart() {
        const container = document.getElementById('comparisonChartContainer');
        if (this.players.length < 2) {
            container.style.display = 'none';
            return;
        }

        container.style.display = 'block';
        const ctx = document.getElementById('comparisonChart').getContext('2d');
        
        // Destroy existing chart if it exists
        if (this.comparisonChartInstance) {
            this.comparisonChartInstance.destroy();
        }

        const topPlayers = this.players.slice(0, Math.min(5, this.players.length));

        this.comparisonChartInstance = new Chart(ctx, {
            type: 'line',
            data: {
                labels: topPlayers.map(p => p.name),
                datasets: [{
                    label: 'Top Players Scores',
                    data: topPlayers.map(p => p.score),
                    borderColor: 'rgba(245, 197, 24, 1)',
                    backgroundColor: 'rgba(245, 197, 24, 0.1)',
                    borderWidth: 3,
                    fill: true,
                    tension: 0.4,
                    pointRadius: 6,
                    pointBackgroundColor: 'rgba(245, 197, 24, 1)',
                    pointBorderColor: 'rgba(255, 255, 255, 0.8)',
                    pointBorderWidth: 2,
                    pointHoverRadius: 8
                }]
            },
            options: {
                responsive: true,
                maintainAspectRatio: true,
                plugins: {
                    legend: {
                        labels: {
                            color: 'rgba(255, 255, 255, 0.8)',
                            font: { size: 12 }
                        }
                    }
                },
                scales: {
                    y: {
                        beginAtZero: true,
                        max: 100,
                        ticks: { color: 'rgba(255, 255, 255, 0.6)' },
                        grid: { color: 'rgba(255, 255, 255, 0.1)' }
                    },
                    x: {
                        ticks: { color: 'rgba(255, 255, 255, 0.6)' },
                        grid: { color: 'rgba(255, 255, 255, 0.1)' }
                    }
                }
            }
        });
    }

    renderFlowchart() {
        const container = document.getElementById('flowchartContainer');
        if (this.players.length < 2) {
            container.style.display = 'none';
            return;
        }

        container.style.display = 'block';
        
        // Initialize mermaid
        if (typeof mermaid !== 'undefined') {
            mermaid.contentLoaded();
        }
    }

    resetResults() {
        document.getElementById('winnerCardContainer').style.display = 'none';
        document.getElementById('stepsContainer').style.display = 'none';
        document.getElementById('podiumContainer').style.display = 'none';
        document.getElementById('rankingsContainer').style.display = 'none';
        document.getElementById('statsContainer').style.display = 'none';
        document.getElementById('scoreChartContainer').style.display = 'none';
        document.getElementById('comparisonChartContainer').style.display = 'none';
        document.getElementById('flowchartContainer').style.display = 'none';
    }

    showLoadingSpinner(show) {
        document.getElementById('loadingSpinner').style.display = show ? 'block' : 'none';
    }

    /* ==========================================
     * Local Storage
     * ========================================== */
    saveToLocalStorage() {
        localStorage.setItem('tournamentPlayers', JSON.stringify(this.players));
    }

    loadFromLocalStorage() {
        const saved = localStorage.getItem('tournamentPlayers');
        if (saved) {
            this.players = JSON.parse(saved);
            this.renderRoster();
            this.updateAnalyzeButton();
        }
    }
}

// Initialize app when DOM is ready
let app;
document.addEventListener('DOMContentLoaded', () => {
    app = new TournamentApp();
});
