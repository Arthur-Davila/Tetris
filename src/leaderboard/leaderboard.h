#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <stdbool.h>

#define MAX_RECORDS 10
#define NAME_LENGTH 20

typedef struct {
    char name[NAME_LENGTH];
    int score;
    int minutes;
    int seconds;
} Record;

typedef struct {
    Record records[MAX_RECORDS];
    int count;
} Leaderboard;

void initLeaderboard(Leaderboard *lb);
void loadLeaderboard(Leaderboard *lb);
void saveLeaderboard(Leaderboard *lb);
bool addRecord(Leaderboard *lb, const char *name, int score, int minutes, int seconds);
void sortLeaderboard(Leaderboard *lb);
bool isHighScore(Leaderboard *lb, int score);

#endif