#include "raylib.h"
#include <stdio.h>
#include <stdlib.h> // adicionado para malloc e free
#include "colors/colors.h"
#include "blocks/blocks.h"
#include "grid/grid.h"

int main(void) {
    Grid grid;
    inicializarMatriz(&grid);
    Block blocos = createBlockO(); // cria o bloco T

    InitWindow(300, 620, "Raylib no Arch Linux");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        Desenhar(&grid);
        Draw(blocos);
        EndDrawing();
    }

    CloseWindow();

    for (int i = 0; i < 4; i++) {
        free(blocos.pos[i]);
    }

    return 0;
}
