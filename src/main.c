#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include "colors/colors.h"
#include "blocks/blocks.h"
#include "grid/grid.h"
#include "menu/menu.h"
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

    InitWindow(500, 620, "Raylib no Arch Linux");
    SetExitKey(KEY_NULL);
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(DARKBLUE);

        switch (game.state) {
            case MENU:
                DrawMenu(&game);
                break;
            case GAME:
                handleInput(&game);
                if (eventTriggered(0.3)) moveBlockDown(&game);
                DrawGame(&game); // Aqui deve desenhar o painel lateral
                DrawText("Score", 345, 15, 38, WHITE);
                DrawText("Next", 360, 175, 38, WHITE);
                DrawRectangleRounded((Rectangle){320, 55, 170, 60}, 0.3, 6, (Color){100, 20, 30, 128});
                DrawRectangleRounded((Rectangle){320, 215, 170, 180}, 0.3, 6, (Color){100, 20, 30, 128});
                DrawText(TextFormat("%d", game.score), 395, 65, 40, WHITE);
                if (game.gameOver) game.state = GAMEOVER;
                break;

            case CREDITS:
                DrawCredits(&game);
                break;
            case GAMEOVER:
                DrawGameOver(&game);
                break;
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}