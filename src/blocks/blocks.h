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
    Pos* pos[4];
    int id;
    int offsetCol;
    int offsetRow;

} Block;

Block createBlockL(void);
Block createBlockT(void);
Block createBlockO(void);
Block createBlockJ(void);
Block createBlockS(void);
Block createBlockZ(void);
Block createBlockI(void);
void Draw(Block block);
void DrawBlockInPanel(Block block, int panelX, int panelY, int panelWidth, int panelHeight);
void moveBlock(int col, int row, Block *block);
void rotate(Block *block);
void undoRotate(Block *block);

#endif
