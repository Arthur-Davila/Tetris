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
void moveBlockDown(Block *block); // Protótipo para mover bloco para baixo
#endif