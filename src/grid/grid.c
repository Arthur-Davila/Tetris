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
bool isCellEmpty(int x, int y, Grid *grid) {
    if (y < 0 || y >= LINHAS || x < 0 || x >= COLUNAS) {
        return false; // Fora dos limites da grade
    }
    return grid->matriz[y][x] == 0; // Retorna true se a célula estiver vazia
}

bool isRowFull(Grid *grid, int row)
{
    for (int j = 0; j < COLUNAS; j++) {
        if (grid->matriz[row][j] == 0) {
            return false; // Encontrou uma célula vazia, a linha não está cheia
        }
    }
    return true; // Todas as células estão preenchidas
}

void clearRow(Grid *grid, int row)
{
    for (int j = 0; j < COLUNAS; j++) {
        grid->matriz[row][j] = 0;
    }
}

void shiftRowsDown(Grid *grid, int row,int rowNumber)
{
    for(int j = 0; j<COLUNAS;j++){
        grid->matriz[row+rowNumber][j]=grid->matriz[row][j];
        grid->matriz[row][j]=0;
    }
}

int clearFullRows(Grid *grid)
{   int completed = 0;
    for (int i = LINHAS - 1; i >= 0; i--) {
        if (isRowFull(grid, i)) {
            clearRow(grid, i);
            completed++;
            
        }
        else if (completed > 0) {
            shiftRowsDown(grid, i, completed); 
        }
    }
    return completed;
}
