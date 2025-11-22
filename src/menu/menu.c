#include "menu.h"
#include <raylib.h>

void DrawMenu(Game *game) {
    if (IsKeyPressed(KEY_UP)) game->menuOption = (game->menuOption - 1 + 2) % 2;
    if (IsKeyPressed(KEY_DOWN)) game->menuOption = (game->menuOption + 1) % 2;

    DrawText("TETRIS", 130, 80, 64, WHITE);
    DrawRectangle(140, 200, 220, 50, game->menuOption == 0 ? LIGHTGRAY : BLUE);
    DrawText("Iniciar Jogo", 160, 215, 30, WHITE);
    DrawRectangle(140, 270, 220, 50, game->menuOption == 1 ? LIGHTGRAY : BLUE);
    DrawText("Créditos", 180, 285, 30, WHITE);

    if (IsKeyPressed(KEY_ENTER)) {
        if (game->menuOption == 0) {
            initGame(game);
            game->state = GAME;
        } else {
            game->state = CREDITS;
        }
    }
}

void DrawCredits(Game *game) {
    DrawText("Créditos", 150, 100, 50, WHITE);
    DrawText("Arthur Davila", 170, 180, 30, WHITE);
    DrawText("Nathália Carvalho", 170, 230, 30, WHITE);
    DrawText("Maria Eduarda", 170, 280, 30, WHITE);
    DrawText("Pressione ESC para voltar", 120, 370, 20, LIGHTGRAY);
    if (IsKeyPressed(KEY_ESCAPE)) game->state = MENU;
}

void DrawGameOver(Game *game) {
    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_DOWN)) game->menuOption = 1 - game->menuOption;

    int minutes = (int)(game->finalTime / 60);
    int seconds = (int)game->finalTime % 60;

    DrawText("Game Over!", 130, 100, 48, RED);
    DrawText(TextFormat("Score: %d", game->score), 170, 170, 30, WHITE);
    DrawText(TextFormat("Time: %02d:%02d", minutes, seconds), 170, 210, 30, WHITE);

    DrawRectangle(100, 280, 300, 50, game->menuOption == 0 ? LIGHTGRAY : BLUE);
    DrawText("Tentar Novamente", 115, 294, 28, WHITE); 
    
    DrawRectangle(100, 350, 300, 50, game->menuOption == 1 ? LIGHTGRAY : BLUE);
    DrawText("Sair", 220, 364, 32, WHITE);

    if (IsKeyPressed(KEY_ENTER)) {
        if (game->menuOption == 0) {
            initGame(game);
            game->state = GAME;
        } else {
            CloseWindow();
        }
    }
}