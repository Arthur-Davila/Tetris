#include "game.h"
#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void updateScore(Game *game, int rowsCleared,int softDropLines) {
    int points = 0;
    switch (rowsCleared) {
        case 1: points = 100; break;
        case 2: points = 300; break;
        case 3: points = 500; break;
        case 4: points = 800; break;
        default: points = 0; break;
    }
    points += softDropLines * 1;
    game->score += points;
}

void initGame(Game *game) {
    game->gameOver = false;
    game->state = MENU;
    game->score = 0;
    game->menuOption = 0;
    srand(time(NULL));    
    // A função 'inicializarMatriz' está definida em grid.c
    inicializarMatriz(&game->grid);
    // Inicializa a lista de blocos disponíveis e pega os dois primeiros
    game->nextBlocks = getBlocks();
    game->currentBlock = getRandomBlock(&game->nextBlocks);
    moveBlock(3, 0, &game->currentBlock); // Posiciona o bloco inicial no topo central
    game->nextBlock = getRandomBlock(&game->nextBlocks);
    game->score = 0;
    int rowsCleared = clearFullRows(&game->grid);
    updateScore(game, rowsCleared,1);

}

void DrawGame(Game *game) {
    Desenhar(&game->grid); // Debug: Verifica a posição do bloco atual
    Draw(game->currentBlock); 
    // TODO: Adicionar desenho do nextBlock
}

// --- Funções de Lista de Blocos ---

BlockNode* create_node(Block block) {
    BlockNode *node = malloc(sizeof(BlockNode));
    if (node == NULL) {
        return NULL;
    }
    // A struct Block é copiada por valor.
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

    // Percorre até o índice
    for (int i = 0; i < idx; i++) {
        prev = aux;/* 
        printf("ID do bloco: %d\n", aux->block.id); */
        aux = aux->next;
    }

    // Remove o nó da lista
    if (prev) prev->next = aux->next;
    else *head = aux->next;

    // Copia o bloco escolhido (a nova cópia será o currentBlock/nextBlock)
    Block chosen = aux->block; 
    
   

    free(aux); // Libera o nó em si
    return chosen;
}

void lockBlockToGrid(Game *game) {
    Block *block = &game->currentBlock;
    for (int i = 0; i < 4; i++) {
        int x = block->pos[rotatioState][i].x ;
        int y = block->pos[rotatioState][i].y ;
        if (y >= 0 && y < LINHAS && x >= 0 && x < COLUNAS) {
            game->grid.matriz[y][x] = block->id; // +1 para evitar o 0 (vazio)
        }
    }
    // Atualiza o bloco atual e o próximo
    game->currentBlock = game->nextBlock;
    if(blockFits(game,3,0)== false){
        game->gameOver = true;
    }
    moveBlock(3, 0, &game->currentBlock); // Posiciona o novo bloco atual no topo central
    game->nextBlock = getRandomBlock(&game->nextBlocks); 
    int rowsCleared = clearFullRows(&game->grid);
    updateScore(game, rowsCleared,0);
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
