#ifndef GAME_H
#define GAME_H

#include "../grid/grid.h"
#include "../blocks/blocks.h" 
typedef struct BlockNode {
    Block block;
    struct BlockNode *next;
} BlockNode;

typedef enum {
    MENU,
    GAME,
    CREDITS,
    GAMEOVER
} GameState;

// 2. Estado do jogo (Pode agora usar BlockNode)
typedef struct {
    Grid grid;
    BlockNode *nextBlocks;   // lista encadeada de blocos disponíveis
    Block currentBlock;
    Block nextBlock;
    bool gameOver;
    int score ;
    GameState state;
    int menuOption;
} Game;

// Protótipos das funções
void initGame(Game *game);
void DrawGame(Game *game);
BlockNode* create_node(Block block);
BlockNode* getBlocks(void);
Block getRandomBlock(BlockNode **head);
void handleInput(Game *game); // Protótipo para função de entrada do jogador
void moveBlockLeft(Game *game); // Protótipo para mover bloco para a esquerda
void moveBlockRight(Game *game); // Protótipo para mover bloco para a direita
void moveBlockDown(Game *game); // Protótipo para mover bloco para baixo
bool blockFits(Game *game, int posX, int posY); // Protótipo para verificar se o bloco cabe na grade
void rotateBlock(Game *game); // Protótipo para rotacionar o bloco
void lockBlockToGrid(Game *game); // Protótipo para travar o bloco na grade
#endif