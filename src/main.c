#include "raylib.h"
#include <stdio.h>
#include <stdlib.h> // adicionado para malloc e free
#include "colors/colors.h"
#include "blocks/blocks.h"

#define LINHAS 20
#define COLUNAS 10
#define cellsize 30

void inicializarMatriz(int matriz[LINHAS][COLUNAS]) {
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            matriz[i][j] = 0;
        }
    }
}

void imprimirMatriz(int matriz[LINHAS][COLUNAS]) {
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

void desenhar(int grid[LINHAS][COLUNAS], Color *colors) {
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            int valueCell = grid[i][j];
            DrawRectangle(j * (cellsize + 1), i * (cellsize + 1),
                          cellsize - 1, cellsize - 1, colors[valueCell]);
        }
    }
}

int main(void) {
    int grid[LINHAS][COLUNAS];
    Color *colors = getCellColors();
    inicializarMatriz(grid);

    Block blocos = createBlockT(); // cria o bloco T

    InitWindow(300, 620, "Raylib no Arch Linux");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        desenhar(grid, colors);
        Draw(blocos);
        EndDrawing();
    }

    CloseWindow();

    for (int i = 0; i < 4; i++) {
        free(blocos.pos[i]);
    }

    return 0;
}
