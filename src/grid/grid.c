#include "grid.h"
#include "../colors/colors.h"
#include "../blocks/blocks.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

void inicializarMatriz(Grid *grid) {
    for (int i = 0; i < LINHAS; i++)
        for (int j = 0; j < COLUNAS; j++)
            grid->matriz[i][j] = 0;
}

void imprimirMatriz(Grid *grid) {
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++)
            printf("%d ", grid->matriz[i][j]);
        printf("\n");
    }
}

void Desenhar(Grid *grid) {
    Color *colors = getCellColors();
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            int valueCell = grid->matriz[i][j];
            DrawRectangle(j * (CELLSIZE + 1), i * (CELLSIZE + 1),
                          CELLSIZE - 1, CELLSIZE - 1, colors[valueCell]);
        }
    }
}
bool outSide( Block *block,int posX, int posY) {
    
    for (int i = 0; i < 4; i++) {

        if ((block->pos[rotatioState][i].x + posX) < 0 || (block->pos[rotatioState][i].y + posY) >=LINHAS || (block->pos[rotatioState][i].x + posX) >= COLUNAS) {

            return true;
        }
        
        

    }
    return false;

}

