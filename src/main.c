#include "raylib.h"
#include <stdio.h>
#include <stdlib.h> // adicionado para malloc e free
#include "colors/colors.h"
#include "blocks/blocks.h"
#include "grid/grid.h"
#include "Game/game.h"
int main(void) {
    Game game;
    initGame(&game);
    SetWindowTitle("Tetris Game");
    InitWindow(300, 620, "Raylib no Arch Linux");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        handleInput(&game.currentBlock);
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawGame(&game);
        EndDrawing();
    }

    CloseWindow();


    return 0;
}
