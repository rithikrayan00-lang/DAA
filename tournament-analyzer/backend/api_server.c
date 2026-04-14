#include "tournament.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#pragma comment(lib, "Ws2_32.lib")

// Forward declarations
void parsePlayerFromJsonFromPtr(const char* ptr, Player* p);

#define PORT 3000
#define BUFFER_SIZE 8192
#define MAX_PLAYERS 100

typedef struct {
    Player players[MAX_PLAYERS];
    int count;
} PlayerDatabase;

PlayerDatabase db = {0};

/* ==========================================
 * JSON Utilities
 * ========================================== */
char* jsonEscapeString(const char* str) {
    char* result = (char*)malloc(strlen(str) * 2 + 1);
    int j = 0;
    for (int i = 0; str[i]; i++) {
        if (str[i] == '"' || str[i] == '\\') {
            result[j++] = '\\';
        }
        result[j++] = str[i];
    }
    result[j] = '\0';
    return result;
}

char* playerToJson(Player p) {
    char* buffer = (char*)malloc(256);
    snprintf(buffer, 256, "{\"id\":%d,\"name\":\"%s\",\"score\":%d,\"rank\":%d}",
             p.id, p.name, p.score, p.rank);
    return buffer;
}

char* playersArrayToJson(Player* arr, int count) {
    char* result = (char*)malloc(BUFFER_SIZE);
    strcpy(result, "[");
    
    for (int i = 0; i < count; i++) {
        char* playerJson = playerToJson(arr[i]);
        strcat(result, playerJson);
        if (i < count - 1) strcat(result, ",");
        free(playerJson);
    }
    
    strcat(result, "]");
    return result;
}

/* ==========================================
 * HTTP Response Builders
 * ========================================== */
char* buildJsonResponse(const char* json) {
    char* response = (char*)malloc(BUFFER_SIZE);
    snprintf(response, BUFFER_SIZE,
             "HTTP/1.1 200 OK\r\n"
             "Content-Type: application/json\r\n"
             "Access-Control-Allow-Origin: *\r\n"
             "Access-Control-Allow-Methods: GET, POST, OPTIONS\r\n"
             "Access-Control-Allow-Headers: Content-Type\r\n"
             "Content-Length: %zu\r\n"
             "Connection: close\r\n"
             "\r\n%s", strlen(json), json);
    return response;
}

char* buildErrorResponse(const char* error) {
    char* json = (char*)malloc(256);
    snprintf(json, 256, "{\"error\":\"%s\"}", error);
    char* response = buildJsonResponse(json);
    free(json);
    return response;
}

/* ==========================================
 * Request Parsers
 * ========================================== */
void parsePlayerFromJson(const char* json, Player* p) {
    // Simple JSON parser for {"name":"X","score":N}
    char nameBuffer[50] = {0};
    int score = 0;
    
    // Extract name
    const char* nameStart = strstr(json, "\"name\":\"");
    if (nameStart) {
        nameStart += 8;
        int i = 0;
        while (nameStart[i] && nameStart[i] != '\"' && i < 49) {
            nameBuffer[i] = nameStart[i];
            i++;
        }
        nameBuffer[i] = '\0';
    }
    
    // Extract score
    const char* scoreStart = strstr(json, "\"score\":");
    if (scoreStart) {
        sscanf(scoreStart, "\"score\":%d", &score);
    }
    
    p->id = db.count + 1;
    strncpy(p->name, nameBuffer, 49);
    p->name[49] = '\0';
    p->score = score;
    p->rank = 0;
}

void parsePlayerFromJsonFromPtr(const char* ptr, Player* p) {
    // Find the closing brace
    char buffer[256];
    int braceCount = 0;
    int i = 0;
    
    while (ptr[i] && i < 255) {
        if (ptr[i] == '{') braceCount++;
        if (ptr[i] == '}') braceCount--;
        buffer[i] = ptr[i];
        i++;
        if (braceCount == 0 && i > 1) break;
    }
    buffer[i] = '\0';
    
    parsePlayerFromJson(buffer, p);
}

/* ==========================================
 * Route Handlers
 * ========================================== */

// GET /api/players
char* handleGetPlayers() {
    char* playersJson = playersArrayToJson(db.players, db.count);
    char* response = buildJsonResponse(playersJson);
    free(playersJson);
    return response;
}

// POST /api/analyze
char* handleAnalyze(const char* body) {
    // Parse players from JSON array in body
    PlayerDatabase tempDb = db;
    
    // Simple extraction: find all objects with name and score
    int playerCount = 0;
    const char* ptr = body;
    
    while ((ptr = strstr(ptr, "\"name\":")) && playerCount < MAX_PLAYERS) {
        Player p = {0};
        parsePlayerFromJsonFromPtr(ptr, &p);
        if (strlen(p.name) > 0 && p.score > 0) {
            p.id = playerCount + 1;
            db.players[playerCount] = p;
            playerCount++;
        }
        ptr++;
    }
    db.count = playerCount;
    
    if (playerCount == 0) {
        char* response = buildErrorResponse("No valid players provided");
        db = tempDb;
        return response;
    }
    
    // Run D&C to find winner
    Player winner = findWinner(db.players, 0, playerCount - 1);
    
    // Sort by score
    sortPlayersByScore(db.players, playerCount);
    
    // Build response
    char* playersJson = playersArrayToJson(db.players, playerCount);
    char* winnerJson = playerToJson(winner);
    
    char* fullJson = (char*)malloc(BUFFER_SIZE);
    snprintf(fullJson, BUFFER_SIZE,
             "{\"winner\":%s,\"players\":%s,\"totalPlayers\":%d,\"algorithm\":\"Divide and Conquer\"}",
             winnerJson, playersJson, playerCount);
    
    char* response = buildJsonResponse(fullJson);
    
    free(playersJson);
    free(winnerJson);
    free(fullJson);
    
    return response;
}

// GET /api/top?k=3
char* handleGetTop(const char* query) {
    int k = 3;
    
    // Parse k from query string
    const char* kPtr = strstr(query, "k=");
    if (kPtr) {
        sscanf(kPtr, "k=%d", &k);
    }
    
    if (k > db.count) k = db.count;
    if (k <= 0) k = 1;
    
    // Make a copy to avoid modifying original
    Player* copy = (Player*)malloc(db.count * sizeof(Player));
    memcpy(copy, db.players, db.count * sizeof(Player));
    
    // Sort to get top k
    mergeSort(copy, 0, db.count - 1);
    
    // Get top k
    Player* topK = (Player*)malloc(k * sizeof(Player));
    for (int i = 0; i < k; i++) {
        topK[i] = copy[i];
        topK[i].rank = i + 1;
    }
    
    char* topKJson = playersArrayToJson(topK, k);
    char* fullJson = (char*)malloc(BUFFER_SIZE);
    snprintf(fullJson, BUFFER_SIZE,
             "{\"k\":%d,\"topPlayers\":%s}",
             k, topKJson);
    
    char* response = buildJsonResponse(fullJson);
    
    free(copy);
    free(topK);
    free(topKJson);
    free(fullJson);
    
    return response;
}

/* ==========================================
 * Static File Server
 * ========================================== */
char* serveStaticFile(const char* path) {
    const char* filePath = path;
    const char* contentType = "text/html";
    char fullPath[512] = {0};
    
    // Determine file path and content type
    if (strcmp(path, "/") == 0 || strcmp(path, "/index.html") == 0) {
        filePath = "..\\frontend\\index.html";
        contentType = "text/html";
    }
    else if (strcmp(path, "/style.css") == 0) {
        filePath = "..\\frontend\\style.css";
        contentType = "text/css";
    }
    else if (strcmp(path, "/app.js") == 0) {
        filePath = "..\\frontend\\app.js";
        contentType = "text/javascript";
    }
    else {
        return buildErrorResponse("File not found");
    }
    
    // Read file
    FILE* file = fopen(filePath, "rb");
    if (!file) {
        return buildErrorResponse("File not found");
    }
    
    // Get file size
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    // Read file content
    char* fileContent = (char*)malloc(fileSize + 1);
    size_t bytesRead = fread(fileContent, 1, fileSize, file);
    fileContent[bytesRead] = '\0';
    fclose(file);
    
    // Build response
    char* response = (char*)malloc(fileSize + 512);
    snprintf(response, fileSize + 512,
             "HTTP/1.1 200 OK\r\n"
             "Content-Type: %s\r\n"
             "Access-Control-Allow-Origin: *\r\n"
             "Content-Length: %ld\r\n"
             "Connection: close\r\n"
             "\r\n", contentType, fileSize);
    
    // Append file content
    strcat(response, fileContent);
    
    free(fileContent);
    return response;
}

/* ==========================================
 * Request Router
 * ========================================== */
char* routeRequest(const char* method, const char* path, const char* query, const char* body) {
    // Handle CORS preflight
    if (strcmp(method, "OPTIONS") == 0) {
        char* response = (char*)malloc(BUFFER_SIZE);
        snprintf(response, BUFFER_SIZE,
                 "HTTP/1.1 204 No Content\r\n"
                 "Access-Control-Allow-Origin: *\r\n"
                 "Access-Control-Allow-Methods: GET, POST, OPTIONS\r\n"
                 "Access-Control-Allow-Headers: Content-Type\r\n"
                 "Connection: close\r\n\r\n");
        return response;
    }
    
    // Handle API routes
    if (strcmp(path, "/api/players") == 0 && strcmp(method, "GET") == 0) {
        return handleGetPlayers();
    }
    else if (strcmp(path, "/api/analyze") == 0 && strcmp(method, "POST") == 0) {
        return handleAnalyze(body);
    }
    else if (strstr(path, "/api/top") && strcmp(method, "GET") == 0) {
        return handleGetTop(query);
    }
    // Handle static files
    else if (strcmp(method, "GET") == 0 && (strcmp(path, "/") == 0 || 
             strcmp(path, "/index.html") == 0 || 
             strcmp(path, "/style.css") == 0 || 
             strcmp(path, "/app.js") == 0)) {
        return serveStaticFile(path);
    }
    else {
        return buildErrorResponse("Route not found");
    }
}

/* ==========================================
 * HTTP Server
 * ========================================== */
int main() {
    WSADATA wsaData;
    SOCKET listenSocket = INVALID_SOCKET;
    SOCKET clientSocket = INVALID_SOCKET;
    struct sockaddr_in serverAddr, clientAddr;
    int clientAddrLen = sizeof(clientAddr);
    
    // Initialize Winsock
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed: %d\n", iResult);
        return 1;
    }
    
    // Create listening socket
    listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listenSocket == INVALID_SOCKET) {
        printf("socket failed: %ld\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    
    // Bind socket
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddr.sin_port = htons(PORT);
    
    iResult = bind(listenSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if (iResult == SOCKET_ERROR) {
        printf("bind failed: %ld\n", WSAGetLastError());
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }
    
    // Listen
    if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR) {
        printf("listen failed: %ld\n", WSAGetLastError());
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }
    
    printf("Tournament API Server running on http://127.0.0.1:%d\n", PORT);
    printf("Press Ctrl+C to stop...\n");
    
    // Accept connections
    while (1) {
        clientSocket = accept(listenSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
        if (clientSocket == INVALID_SOCKET) {
            printf("accept failed: %ld\n", WSAGetLastError());
            continue;
        }
        
        // Receive request
        char buffer[BUFFER_SIZE] = {0};
        int recvResult = recv(clientSocket, buffer, BUFFER_SIZE - 1, 0);
        
        if (recvResult == SOCKET_ERROR) {
            printf("recv failed: %ld\n", WSAGetLastError());
            closesocket(clientSocket);
            continue;
        }
        
        if (recvResult == 0) {
            closesocket(clientSocket);
            continue;
        }
        
        buffer[recvResult] = '\0';
        
        // Parse HTTP request
        char method[16] = {0};
        char path[256] = {0};
        char query[512] = {0};
        char body[BUFFER_SIZE] = {0};
        
        // Parse request line
        sscanf(buffer, "%s %s HTTP/1.1", method, path);
        
        // Extract query string from path
        char* queryPtr = strchr(path, '?');
        if (queryPtr) {
            *queryPtr = '\0';
            strcpy(query, queryPtr + 1);
        }
        
        // Extract body (after headers)
        char* bodyPtr = strstr(buffer, "\r\n\r\n");
        if (bodyPtr) {
            strcpy(body, bodyPtr + 4);
        }
        
        // Route and respond
        char* response = routeRequest(method, path, query, body);
        
        // Send response
        send(clientSocket, response, (int)strlen(response), 0);
        
        free(response);
        closesocket(clientSocket);
    }
    
    closesocket(listenSocket);
    WSACleanup();
    return 0;
}
