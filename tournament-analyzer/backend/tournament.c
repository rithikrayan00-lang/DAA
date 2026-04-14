#include "tournament.h"

/* ==========================================
 * DIVIDE & CONQUER: Find Winner
 * ========================================== */
Player findWinner(Player* arr, int left, int right) {
    // Base case: single player
    if (left == right) {
        return arr[left];
    }
    
    // Divide
    int mid = left + (right - left) / 2;
    
    // Conquer
    Player leftWinner = findWinner(arr, left, mid);
    Player rightWinner = findWinner(arr, mid + 1, right);
    
    // Combine: return player with higher score
    if (leftWinner.score >= rightWinner.score) {
        return leftWinner;
    } else {
        return rightWinner;
    }
}

/* ==========================================
 * DIVIDE & CONQUER: Merge Sort by Score
 * ========================================== */
void merge(Player* arr, int left, int mid, int right) {
    int leftLen = mid - left + 1;
    int rightLen = right - mid;
    
    Player* leftArr = (Player*)malloc(leftLen * sizeof(Player));
    Player* rightArr = (Player*)malloc(rightLen * sizeof(Player));
    
    for (int i = 0; i < leftLen; i++) {
        leftArr[i] = arr[left + i];
    }
    for (int j = 0; j < rightLen; j++) {
        rightArr[j] = arr[mid + 1 + j];
    }
    
    int i = 0, j = 0, k = left;
    
    // Merge: compare scores in descending order
    while (i < leftLen && j < rightLen) {
        if (leftArr[i].score >= rightArr[j].score) {
            arr[k++] = leftArr[i++];
        } else {
            arr[k++] = rightArr[j++];
        }
    }
    
    while (i < leftLen) {
        arr[k++] = leftArr[i++];
    }
    
    while (j < rightLen) {
        arr[k++] = rightArr[j++];
    }
    
    free(leftArr);
    free(rightArr);
}

Player* mergeSort(Player* arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        // Divide & Conquer
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        
        // Combine
        merge(arr, left, mid, right);
    }
    return arr;
}

/* ==========================================
 * DIVIDE & CONQUER: Quickselect for Top K
 * ========================================== */
int partition(Player* arr, int left, int right) {
    Player pivot = arr[right];
    int i = left - 1;
    
    for (int j = left; j < right; j++) {
        if (arr[j].score > pivot.score) {
            i++;
            Player temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    Player temp = arr[i + 1];
    arr[i + 1] = arr[right];
    arr[right] = temp;
    return i + 1;
}

Player findTopK(Player* arr, int left, int right, int k) {
    if (left == right) {
        return arr[left];
    }
    
    int pivot = partition(arr, left, right);
    
    if (k == pivot) {
        return arr[k];
    } else if (k < pivot) {
        return findTopK(arr, left, pivot - 1, k);
    } else {
        return findTopK(arr, pivot + 1, right, k);
    }
}

/* ==========================================
 * Utility Functions
 * ========================================== */
void initPlayer(Player* p, int id, const char* name, int score) {
    p->id = id;
    strncpy(p->name, name, 49);
    p->name[49] = '\0';
    p->score = score;
    p->rank = 0;
}

void printPlayer(Player p) {
    printf("Player %d: %s | Score: %d | Rank: %d\n", p.id, p.name, p.score, p.rank);
}

void sortPlayersByScore(Player* arr, int n) {
    mergeSort(arr, 0, n - 1);
    // Assign ranks
    for (int i = 0; i < n; i++) {
        arr[i].rank = i + 1;
    }
}
