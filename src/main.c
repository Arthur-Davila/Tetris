#include "raylib.h"
#include <stdio.h>
#include <stdlib.h> // adicionado para malloc e free
#include "colors/colors.h"
#include "blocks/blocks.h"
#include "grid/grid.h"
#include "Game/game.h"

double lastTime = 0;

bool eventTriggered(double interval) {
    double currentTime = GetTime();
    if (currentTime - lastTime >= interval) {
        lastTime = currentTime;
        return true;
    }
    return false;

}
int main(void) {
    Game game;
    initGame(&game);
    SetWindowTitle("Tetris Game");
    InitWindow(500, 620, "Raylib no Arch Linux");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        handleInput(&game);
        if (eventTriggered(0.2)) {
            moveBlockDown(&game);
        }
        BeginDrawing();
        ClearBackground(DARKBLUE);
        DrawGame(&game);
        if (game.gameOver) {
            Color semiBlack = { 0, 0, 0, 128 }; // 128 = 50% de opacidade
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), semiBlack);
            DrawText("Game Over!", 50, 300, 40, RED);
        }
        EndDrawing();
    }

    CloseWindow();


    return 0;
}
