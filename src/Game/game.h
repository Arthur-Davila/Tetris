#ifndef GAME_H
#define GAME_H

#include "../grid/grid.h"
#include "../blocks/blocks.h" 
#include "../Leaderboard/leaderboard.h"

typedef struct BlockNode {
    Block block;
    struct BlockNode *next;
} BlockNode;

typedef enum {
    MENU,
    GAME,
    CREDITS,
    GAMEOVER,
    LEADERBOARD,  
    ENTER_NAME
} GameState;

typedef struct {
    Grid grid;
    BlockNode *nextBlocks;   // lista encadeada de blocos disponíveis
    Block currentBlock;
    Block nextBlock;
    bool gameOver;
    int score ;
    GameState state;
    int menuOption;
    double startTime;
    double finalTime;
    Leaderboard leaderboard;
    char playerName[NAME_LENGTH]; 
    int nameLength;
    int level;          
    int linesCleared;
} Game;

void initGame(Game *game);
void DrawGame(Game *game);
void DrawHUD(Game *game);
BlockNode* create_node(Block block);
BlockNode* getBlocks(void);
Block getRandomBlock(BlockNode **head);
void handleInput(Game *game);
void moveBlockLeft(Game *game);
void moveBlockRight(Game *game);
void moveBlockDown(Game *game);
bool blockFits(Game *game, int posX, int posY);
void rotateBlock(Game *game);
void lockBlockToGrid(Game *game);
double getDropSpeed(int level);
void updateLevel(Game *game);
const char* getLevelName(int level);

#endif