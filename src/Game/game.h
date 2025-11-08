#ifndef GAME_H
#define GAME_H

#include "../grid/grid.h"
#include "../blocks/blocks.h" 
typedef struct BlockNode {
    Block block;
    struct BlockNode *next;
} BlockNode;

// 2. Estado do jogo (Pode agora usar BlockNode)
typedef struct {
    Grid grid;
    BlockNode *nextBlocks;   // lista encadeada de blocos disponíveis
    Block currentBlock;
    Block nextBlock;
} Game;

// Protótipos das funções
void initGame(Game *game);
void DrawGame(Game *game);
BlockNode* create_node(Block block);
BlockNode* getBlocks(void);
Block getRandomBlock(BlockNode **head);
void handleInput(Block *block); // Protótipo para função de entrada do jogador
void moveBlockLeft(Block *block); // Protótipo para mover bloco para a esquerda
void moveBlockRight(Block *block); // Protótipo para mover bloco para a direita
void moveBlockDown(Game *game); // Protótipo para mover bloco para baixo
bool blockFits(Game *game); // Protótipo para verificar se o bloco cabe na grade
void rotateBlock(Block *block); // Protótipo para rotacionar o bloco
void lockBlockToGrid(Game *game); // Protótipo para travar o bloco na grade
#endif