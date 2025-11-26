#include "menu.h"
#include <stdio.h>
#include <raylib.h>

void DrawMenu(Game *game) {
    if (IsKeyPressed(KEY_UP)) game->menuOption = (game->menuOption - 1 + 4) % 4;
    if (IsKeyPressed(KEY_DOWN)) game->menuOption = (game->menuOption + 1) % 4;

    DrawText("T", 120, 80, 64, RED);
    DrawText("E", 170, 80, 64, ORANGE);
    DrawText("T", 220, 80, 64, YELLOW);
    DrawText("R", 270, 80, 64, GREEN);
    DrawText("I", 320, 80, 64, BLUE);
    DrawText("S", 350, 80, 64, purple);
    
    DrawRectangle(140, 180, 220, 50, game->menuOption == 0 ? SKYBLUE : DARKBLUE);
    DrawText("Start Game", 165, 195, 30, WHITE);
    
    DrawRectangle(140, 250, 220, 50, game->menuOption == 1 ? SKYBLUE : DARKBLUE);
    DrawText("Leaderboard", 155, 265, 30, WHITE);
    
    DrawRectangle(140, 320, 220, 50, game->menuOption == 2 ? SKYBLUE : DARKBLUE);
    DrawText("Devs", 210, 335, 30, WHITE);
    
    DrawRectangle(140, 390, 220, 50, game->menuOption == 3 ? SKYBLUE : DARKBLUE);
    DrawText("Close", 210, 405, 30, WHITE);

    if (IsKeyPressed(KEY_ENTER)) {
        if (game->menuOption == 0) {
            initGame(game);
            game->state = GAME;
        } else if (game->menuOption == 1) {
            game->state = LEADERBOARD;
        } else if (game->menuOption == 2) {
            game->state = CREDITS;
        } else if (game->menuOption == 3) {
            CloseWindow();
        }
    }
}

void DrawLeaderboard(Game *game) {
    DrawText("Leaderboard", 90, 50, 50, WHITE);
    DrawText("Rank  Name         Score        Time", 50, 120, 20, LIGHTGRAY);
    
    for (int i = 0; i < game->leaderboard.count; i++) {
        Record *r = &game->leaderboard.records[i];
        DrawText(TextFormat("%2d", i + 1), 60, 160 + i * 35, 25, WHITE);
        DrawText(r->name, 110, 160 + i * 35, 25, WHITE);
        DrawText(TextFormat("%d", r->score), 250, 160 + i * 35, 25, WHITE);
        DrawText(TextFormat("%02d:%02d", r->minutes, r->seconds), 360, 160 + i * 35, 25, WHITE);
    }
    
    DrawText("Press ESC to go back", 120, 550, 20, LIGHTGRAY);
    if (IsKeyPressed(KEY_ESCAPE)) game->state = MENU;
}

void DrawEnterName(Game *game) {
    DrawText("New Record!", 110, 100, 48, YELLOW);
    DrawText(TextFormat("Score: %d", game->score), 170, 180, 30, WHITE);
    DrawText("Insert your name:", 120, 250, 30, WHITE);
    
    DrawRectangle(100, 300, 300, 50, DARKGRAY);
    DrawText(game->playerName, 120, 315, 30, WHITE);
    
    DrawText("Press ENTER to confirm", 130, 400, 20, LIGHTGRAY);
    
    int key = GetCharPressed();
    while (key > 0) {
        if ((key >= 32) && (key <= 125) && (game->nameLength < NAME_LENGTH - 1)) {
            game->playerName[game->nameLength] = (char)key;
            game->playerName[game->nameLength + 1] = '\0';
            game->nameLength++;
        }
        key = GetCharPressed();
    }
    
    if (IsKeyPressed(KEY_BACKSPACE) && game->nameLength > 0) {
        game->nameLength--;
        game->playerName[game->nameLength] = '\0';
    }
    
    if (IsKeyPressed(KEY_ENTER) && game->nameLength > 0) {
        int minutes = (int)(game->finalTime / 60);
        int seconds = (int)game->finalTime % 60;
        addRecord(&game->leaderboard, game->playerName, game->score, minutes, seconds);
        game->state = LEADERBOARD;
    }
}

void DrawGameOver(Game *game) {
    if (IsKeyPressed(KEY_UP)) game->menuOption = (game->menuOption - 1 + 3) % 3;
    if (IsKeyPressed(KEY_DOWN)) game->menuOption = (game->menuOption + 1) % 3;

    int minutes = (int)(game->finalTime / 60);
    int seconds = (int)game->finalTime % 60;

    DrawText("Game Over!", 130, 100, 48, RED);
    DrawText(TextFormat("Score: %d", game->score), 170, 170, 30, WHITE);
    DrawText(TextFormat("Time: %02d:%02d", minutes, seconds), 170, 210, 30, WHITE);

    DrawRectangle(100, 280, 300, 50, game->menuOption == 0 ? SKYBLUE : DARKBLUE);
    DrawText("Try again", 190, 294, 28, WHITE);
    
    DrawRectangle(100, 350, 300, 50, game->menuOption == 1 ? SKYBLUE : DARKBLUE);
    DrawText("Menu", 215, 364, 32, WHITE);
    
    DrawRectangle(100, 420, 300, 50, game->menuOption == 2 ? SKYBLUE : DARKBLUE);
    DrawText("Close", 210, 434, 32, WHITE);

    if (IsKeyPressed(KEY_ENTER)) {
        if (game->menuOption == 0) {
            initGame(game);
            game->state = GAME;
        } else if (game->menuOption == 1) {
            game->menuOption = 0;
            game->state = MENU;
        } else if (game->menuOption == 2) {
            CloseWindow();
        }
    }
}

void DrawCredits(Game *game) {
    DrawText("Developers", 100, 100, 50, WHITE);
    DrawText("Arthur Davila", 120, 180, 30, WHITE);
    DrawText("Nathália Carvalho", 120, 230, 30, WHITE);
    DrawText("Maria Eduarda", 120, 280, 30, WHITE);
    DrawText("Pressione ESC to go back", 120, 370, 20, LIGHTGRAY);
    if (IsKeyPressed(KEY_ESCAPE)) game->state = MENU;
}
