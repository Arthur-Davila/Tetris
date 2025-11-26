#ifndef GRID_H
#define GRID_H

#include "raylib.h"
#include "../blocks/blocks.h"

#define LINHAS 20
#define COLUNAS 10
#define CELLSIZE 30

typedef struct {
    int matriz[LINHAS][COLUNAS];
} Grid;
bool outSide(Block *block,int posX, int posY);
void inicializarMatriz(Grid *grid);
void imprimirMatriz(Grid *grid);
void Desenhar(Grid *grid);
bool isCellEmpty(int x, int y, Grid *grid);
bool isRowFull(Grid *grid, int row);
void clearRow(Grid *grid, int row);
void shiftRowsDown(Grid *grid, int row, int numRows);
int clearFullRows(Grid *grid);
#endif
