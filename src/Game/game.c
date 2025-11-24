#include "game.h"
#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int linesClearedToLevelUp = 5;  

double getDropSpeed(int level) {
    switch(level) {
        case 1: 
            return 0.8;   
        case 2: 
            return 0.4;  
        case 3: 
            return 0.2;  
        default: 
            return 0.2; 
    }
}

const char* getLevelName(int level) {
    switch(level) {
        case 1: 
            return "Facil";
        case 2: 
            return "Medio";
        case 3: 
            return "Dificil";
        default: 
            return "MAX";
    }
}

void updateLevel(Game *game) {
    int newLevel = (game->linesCleared / linesClearedToLevelUp) + 1;
    
    if (newLevel > 3) {
        newLevel = 3;
    }
    
    if (newLevel > game->level) {
        game->level = newLevel;
    }
}

void updateScore(Game *game, int rowsCleared, int softDropLines) {
    int points = 0;
    switch (rowsCleared) {
        case 1: 
            points = 100; 
            break;
        case 2: 
            points = 300; 
            break;
        case 3:
            points = 500; 
            break;
        case 4: 
            points = 800; 
            break;
        default: 
            points = 0; 
            break;
    }
    
    points *= game->level;
    
    points += softDropLines * 1;
    game->score += points;
    
    game->linesCleared += rowsCleared;
    updateLevel(game);
}

void initGame(Game *game) {
    game->gameOver = false;
    game->state = MENU;
    game->score = 0;
    game->menuOption = 0;
    game->startTime = 0;
    game->finalTime = 0;
    game->nameLength = 0;
    game->level = 1;        
    game->linesCleared = 0;
    strcpy(game->playerName, "Player");
    
    srand(time(NULL));    
    inicializarMatriz(&game->grid);
    game->nextBlocks = getBlocks();
    game->currentBlock = getRandomBlock(&game->nextBlocks);
    moveBlock(3, 0, &game->currentBlock);
    game->nextBlock = getRandomBlock(&game->nextBlocks);
    int rowsCleared = clearFullRows(&game->grid);
    updateScore(game, rowsCleared, 1);
    
    loadLeaderboard(&game->leaderboard);
}

void DrawHUD(Game *game) {
    double elapsedTime = GetTime() - game->startTime;
    int minutes = (int)(elapsedTime / 60);
    int seconds = (int)elapsedTime % 60;
    
    DrawText("Next", 360, 15, 38, WHITE);
    DrawRectangleRounded((Rectangle){320, 55, 170, 180}, 0.3, 6, (Color){100, 20, 30, 128});
    DrawBlockInPanel(game->nextBlock, 320, 55, 170, 180);
    
    DrawText("Time", 360, 255, 38, WHITE);
    DrawRectangleRounded((Rectangle){320, 295, 170, 60}, 0.3, 6, (Color){100, 20, 30, 128});
    DrawText(TextFormat("%02d:%02d", minutes, seconds), 360, 310, 35, WHITE);
    
    DrawText("Score", 350, 375, 38, WHITE);
    DrawRectangleRounded((Rectangle){320, 415, 170, 60}, 0.3, 6, (Color){100, 20, 30, 128});
    DrawText(TextFormat("%d", game->score), 395, 430, 40, WHITE);
    
    DrawText("Level", 350, 495, 38, WHITE);
    DrawRectangleRounded((Rectangle){320, 535, 170, 60}, 0.3, 6, (Color){100, 20, 30, 128});
    DrawText(TextFormat("%d - %s", game->level, getLevelName(game->level)), 345, 550, 30, WHITE);
}

void DrawGame(Game *game) {
    Desenhar(&game->grid);
    Draw(game->currentBlock);
    DrawHUD(game);
}

BlockNode* create_node(Block block) {
    BlockNode *node = malloc(sizeof(BlockNode));
    if (node == NULL) {
        return NULL;
    }

    node->block = block; 
    node->next = NULL;
    return node;
}

BlockNode* getBlocks(void) {
    
    BlockNode *head = NULL, *aux = NULL;

    Block all[7] = {
        createBlockI(), createBlockJ(), createBlockL(),
        createBlockO(), createBlockS(), createBlockT(), createBlockZ()
    };

    for (int i = 0; i < 7; i++) {
        BlockNode *n = create_node(all[i]);
        if (!head) head = n;
        else aux->next = n;
        aux = n;

   
    }
    return head;
}

Block getRandomBlock(BlockNode **head) {
    // Se a lista estiver vazia (a bag acabou), a preenche novamente
    if (*head == NULL) {
        *head = getBlocks();
    }

    int size = 0;
    BlockNode *aux = *head, *prev = NULL;
    while (aux) { size++; aux = aux->next; }

   
    int idx = rand() % size;
    aux = *head;

    for (int i = 0; i < idx; i++) {
        prev = aux;
        // printf("ID do bloco: %d\n", aux->block.id);
        aux = aux->next;
    }

    // Remove o nó da lista
    if (prev) prev->next = aux->next;
    else *head = aux->next;

    // Copia o bloco escolhido (a nova cópia será o currentBlock/nextBlock)
    Block chosen = aux->block; 

    free(aux);
    return chosen;
}

void lockBlockToGrid(Game *game) {
    Block *block = &game->currentBlock;
    for (int i = 0; i < 4; i++) {
        int x = block->pos[rotatioState][i].x;
        int y = block->pos[rotatioState][i].y;
        if (y >= 0 && y < LINHAS && x >= 0 && x < COLUNAS) {
            game->grid.matriz[y][x] = block->id;
        }
    }
    
    game->currentBlock = game->nextBlock;
    
    if(blockFits(game, 3, 0) == false) {
        game->gameOver = true;
        game->finalTime = GetTime() - game->startTime;
        
        if (isHighScore(&game->leaderboard, game->score)) {
            game->state = ENTER_NAME;
            game->nameLength = 0;
            strcpy(game->playerName, "");
        } else {
            game->state = GAMEOVER;
        }
        return;
    }
    
    moveBlock(3, 0, &game->currentBlock);
    game->nextBlock = getRandomBlock(&game->nextBlocks);
    int rowsCleared = clearFullRows(&game->grid);
    updateScore(game, rowsCleared, 0);
}

bool blockFits(Game *game,int posX, int posY)
{
    Block *block = &game->currentBlock;
    for (int i = 0; i < 4; i++) {
        int x = block->pos[rotatioState][i].x + posX;
        int y = block->pos[rotatioState][i].y + posY;
        if (!isCellEmpty(x, y, &game->grid)) {
            return false;
        }
    }
    return true;    
}
void moveBlockLeft(Game *game) {
    if(game->gameOver != true){
    if (outSide(&game->currentBlock,-1,0)!= true  && blockFits(game,-1,0)== true) {
    moveBlock(-1, 0, &game->currentBlock);
    }   
}
}

void moveBlockRight(Game *game) {
    if(game->gameOver != true){
    
    
    if (outSide(&game->currentBlock,1,0)!= true && blockFits(game,1,0)== true) {
    moveBlock(1, 0, &game->currentBlock);
    }
}
    
}


void moveBlockDown(Game *game) {
    if(game->gameOver != true){
    if (outSide(&game->currentBlock,0,1)!= true && blockFits(game,0,1)== true) {
    moveBlock(0, 1, &game->currentBlock);
    }
    else{ 
        lockBlockToGrid(game);
     }
    }
}



void rotateBlock(Game *game) {
    if(game->gameOver != true){
    rotate(&game->currentBlock);

    if (outSide(&game->currentBlock,0,0)== true || blockFits(game,0,0)== false) {
        undoRotate(&game->currentBlock);

    }
}
    
}
void handleInput(Game *game) {
    if (game->state != GAME) return;
    
    if(game->gameOver == true && IsKeyPressed(KEY_ENTER)) {
        initGame(game);
        return;
    }
    if (IsKeyPressed(KEY_RIGHT)) {
        moveBlockRight(game);
    }
    if (IsKeyPressed(KEY_LEFT)) {
        moveBlockLeft(game);
    }
    if (IsKeyDown(KEY_DOWN)) {
        updateScore(game,0,1);
        moveBlockDown(game);
    
    }
    if (IsKeyPressed(KEY_UP))
    {

        rotateBlock(game);
    
    }
    
}
