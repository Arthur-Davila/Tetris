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

    InitWindow(500, 620, "Tetris");
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
                if (game.startTime == 0) {
                    game.startTime = GetTime();
                }
                
                handleInput(&game);

                double dropSpeed = getDropSpeed(game.level);

                if (eventTriggered(dropSpeed)){
                    moveBlockDown(&game);
                }

                DrawGame(&game);
                
                double elapsedTime = GetTime() - game.startTime;
                int minutes = (int)(elapsedTime / 60);
                int seconds = (int)elapsedTime % 60;
                
                DrawText("Next", 360, 15, 38, WHITE);
                DrawRectangleRounded((Rectangle){320, 55, 170, 180}, 0.3, 6, (Color){100, 20, 30, 128});
                DrawBlockInPanel(game.nextBlock, 320, 55, 170, 180);
                
                DrawText("Time", 360, 255, 38, WHITE);
                DrawRectangleRounded((Rectangle){320, 295, 170, 60}, 0.3, 6, (Color){100, 20, 30, 128});
                DrawText(TextFormat("%02d:%02d", minutes, seconds), 360, 310, 35, WHITE);
                
                DrawText("Score", 350, 375, 38, WHITE);
                DrawRectangleRounded((Rectangle){320, 415, 170, 60}, 0.3, 6, (Color){100, 20, 30, 128});
                DrawText(TextFormat("%d", game.score), 395, 430, 40, WHITE);

                DrawText("Level", 350, 495, 38, WHITE);
                DrawRectangleRounded((Rectangle){320, 535, 170, 60}, 0.3, 6, (Color){100, 20, 30, 128});
                DrawText(TextFormat("%d - %s", game.level, getLevelName(game.level)), 345, 550, 30, WHITE);

                break;
            case LEADERBOARD:
                DrawLeaderboard(&game);
                break;
            case ENTER_NAME:
                DrawEnterName(&game);
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