#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[50];
    int score;
    int rank;
} Player;

typedef struct {
    Player* winners;
    int count;
    char** steps;
    int step_count;
} AnalysisResult;

// Core Divide & Conquer Functions
Player findWinner(Player* arr, int left, int right);
Player* mergeSort(Player* arr, int left, int right);
Player findTopK(Player* arr, int left, int right, int k);

// Utility Functions
void initPlayer(Player* p, int id, const char* name, int score);
void printPlayer(Player p);
void sortPlayersByScore(Player* arr, int n);

#endif
