#include "menu.h"
#include <raylib.h>

void DrawMenu(Game *game) {
    if (IsKeyPressed(KEY_UP)) game->menuOption = (game->menuOption - 1 + 4) % 4;
    if (IsKeyPressed(KEY_DOWN)) game->menuOption = (game->menuOption + 1) % 4;

    DrawText("TETRIS", 130, 80, 64, WHITE);
    
    DrawRectangle(140, 180, 220, 50, game->menuOption == 0 ? LIGHTGRAY : BLUE);
    DrawText("Iniciar Jogo", 160, 195, 30, WHITE);
    
    DrawRectangle(140, 250, 220, 50, game->menuOption == 1 ? LIGHTGRAY : BLUE);
    DrawText("Leaderboard", 160, 265, 30, WHITE);
    
    DrawRectangle(140, 320, 220, 50, game->menuOption == 2 ? LIGHTGRAY : BLUE);
    DrawText("Créditos", 180, 335, 30, WHITE);
    
    DrawRectangle(140, 390, 220, 50, game->menuOption == 3 ? LIGHTGRAY : BLUE);
    DrawText("Sair", 220, 405, 30, WHITE);

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
    
    DrawText("Pressione ESC para voltar", 120, 550, 20, LIGHTGRAY);
    if (IsKeyPressed(KEY_ESCAPE)) game->state = MENU;
}

void DrawEnterName(Game *game) {
    DrawText("Novo Recorde!", 90, 100, 48, YELLOW);  // centralizei
    DrawText(TextFormat("Score: %d", game->score), 170, 180, 30, WHITE);
    DrawText("Digite seu nome:", 140, 250, 30, WHITE);
    
    DrawRectangle(100, 300, 300, 50, DARKGRAY);
    DrawText(game->playerName, 120, 315, 30, WHITE);
    
    DrawText("Pressione ENTER para confirmar", 100, 400, 20, LIGHTGRAY);
    
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

    int sw = GetScreenWidth();
    int sh = GetScreenHeight();
    int minutes = (int)(game->finalTime / 60);
    int seconds = (int)game->finalTime % 60;

    DrawRectangle(0, 0, sw, sh, Fade(BLACK, 0.5f));

    const char *title = "GAME OVER";
    int titleSize = 64;
    int titleW = MeasureText(title, titleSize);
    DrawText(title, sw / 2 - titleW / 2, sh / 2 - 120, titleSize, MAROON);

    char info[64];
    sprintf(info, "Score: %d    Time: %02d:%02d", game->score, minutes, seconds);
    int infoW = MeasureText(info, 20);
    DrawText(info, sw / 2 - infoW / 2, sh / 2 - 50, 20, LIGHTGRAY);

    const char *labels[3] = {"Tentar Novamente", "Menu", "Sair"};
    const int btnW = 240, btnH = 48;
    int bx = sw / 2 - btnW / 2;
    int by = sh / 2 - 10;

    for (int i = 0; i < 3; i++) {
        Rectangle b = { (float)bx, (float)(by + i * (btnH + 12)), (float)btnW, (float)btnH };
        Color bg = (game->menuOption == i) ? LIGHTGRAY : DARKGRAY;
        DrawRectangleRec(b, bg);
        int lw = MeasureText(labels[i], 20);
        DrawText(labels[i], bx + (btnW - lw) / 2, (int)(b.y + (btnH - 20) / 2), 20, WHITE);
    }

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
    DrawText("Créditos", 150, 100, 50, WHITE);
    DrawText("Arthur Davila", 170, 180, 30, WHITE);
    DrawText("Nathália Carvalho", 170, 230, 30, WHITE);
    DrawText("Maria Eduarda", 170, 280, 30, WHITE);
    DrawText("Pressione ESC para voltar", 120, 370, 20, LIGHTGRAY);
    if (IsKeyPressed(KEY_ESCAPE)) game->state = MENU;
}
