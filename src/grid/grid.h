#ifndef GRID_H
#define GRID_H

#include "raylib.h"

#define LINHAS 20
#define COLUNAS 10
#define CELLSIZE 30   // define o tamanho da célula aqui para todos os módulos

typedef struct {
    int matriz[LINHAS][COLUNAS];
} Grid;

void inicializarMatriz(Grid *grid);
void imprimirMatriz(Grid *grid);
void Desenhar(Grid *grid);

#endif
