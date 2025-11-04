#ifndef BLOCKS_H
#define BLOCKS_H

#include "raylib.h"
#include "colors.h"

extern int cellsize;
extern int rotatioState;

typedef struct {
    int x;
    int y;
} Pos;

typedef struct {
    Color color;
    Pos* pos[4]; // 4 rotações, cada uma com 4 posições
    int id;
} Block;

Block createBlockL(void);
Block createBlockT(void);
Block createBlockO(void);
Block createBlockJ(void);
Block createBlockS(void);
Block createBlockZ(void);
Block createBlockI(void);
void Draw(Block block);

#endif
