// Game/game.h (Corrigido)

#ifndef GAME_H
#define GAME_H

#include "../grid/grid.h"
#include "../blocks/blocks.h" // Garante que Block está definido

// 1. Nó da lista de blocos (DEVE VIR PRIMEIRO)
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

#endif