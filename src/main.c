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