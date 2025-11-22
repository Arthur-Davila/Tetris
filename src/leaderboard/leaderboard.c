#include "leaderboard.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LEADERBOARD_FILE "leaderboard.txt"

void initLeaderboard(Leaderboard *lb) {
    lb->count = 0;
    for (int i = 0; i < MAX_RECORDS; i++) {
        strcpy(lb->records[i].name, "");
        lb->records[i].score = 0;
        lb->records[i].minutes = 0;
        lb->records[i].seconds = 0;
    }
}

void loadLeaderboard(Leaderboard *lb) {
    FILE *file = fopen(LEADERBOARD_FILE, "r");
    if (!file) {
        initLeaderboard(lb);
        return;
    }
    
    lb->count = 0;
    while (lb->count < MAX_RECORDS && 
           fscanf(file, "%19s %d %d %d\n", 
                  lb->records[lb->count].name,
                  &lb->records[lb->count].score,
                  &lb->records[lb->count].minutes,
                  &lb->records[lb->count].seconds) == 4) {
        lb->count++;
    }
    
    fclose(file);
}

void saveLeaderboard(Leaderboard *lb) {
    FILE *file = fopen(LEADERBOARD_FILE, "w");
    if (!file) return;
    
    for (int i = 0; i < lb->count; i++) {
        fprintf(file, "%s %d %d %d\n",
                lb->records[i].name,
                lb->records[i].score,
                lb->records[i].minutes,
                lb->records[i].seconds);
    }
    
    fclose(file);
}

void sortLeaderboard(Leaderboard *lb) {
    for (int i = 0; i < lb->count - 1; i++) {
        for (int j = 0; j < lb->count - i - 1; j++) {
            if (lb->records[j].score < lb->records[j + 1].score) {
                Record temp = lb->records[j];
                lb->records[j] = lb->records[j + 1];
                lb->records[j + 1] = temp;
            }
        }
    }
}

bool addRecord(Leaderboard *lb, const char *name, int score, int minutes, int seconds) {
    if (lb->count < MAX_RECORDS || score > lb->records[lb->count - 1].score) {
        int index = lb->count < MAX_RECORDS ? lb->count : MAX_RECORDS - 1;
        
        strncpy(lb->records[index].name, name, NAME_LENGTH - 1);
        lb->records[index].name[NAME_LENGTH - 1] = '\0';
        lb->records[index].score = score;
        lb->records[index].minutes = minutes;
        lb->records[index].seconds = seconds;
        
        if (lb->count < MAX_RECORDS) lb->count++;
        
        sortLeaderboard(lb);
        saveLeaderboard(lb);
        return true;
    }
    return false;
}

bool isHighScore(Leaderboard *lb, int score) {
    return lb->count < MAX_RECORDS || score > lb->records[MAX_RECORDS - 1].score;
}