#include "game.h"
#include "raylib.h"
#include <stdlib.h>
#include <stdio.h> // Para fprintf (bom para debug)
#include <time.h>

void initGame(Game *game) {
    
    srand(time(NULL));    
    // A função 'inicializarMatriz' está definida em grid.c
    inicializarMatriz(&game->grid);
    // Inicializa a lista de blocos disponíveis e pega os dois primeiros
    game->nextBlocks = getBlocks();
    game->currentBlock = getRandomBlock(&game->nextBlocks);
    game->nextBlock = getRandomBlock(&game->nextBlocks);
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
void moveBlockLeft(Block *block) {
    if (outSide(block,-1,0)!= true) {
    moveBlock(-1, 0, block);
    }
    
    
    
}
void moveBlockRight(Block *block) {
     if (outSide(block,1,0)!= true) {
    moveBlock(1, 0, block);
    }
    
}
void moveBlockDown(Block *block) {
    if (outSide(block,0,1)!= true) {
    moveBlock(0, 1, block);
    }
}

void rotateBlock(Block *block) {
    rotate();
    
    if (outSide(block,0,0)== true) {
        undoRotate();
    
    }
    
}
void handleInput(Block *block) {
    if (IsKeyPressed(KEY_RIGHT)) {
        moveBlockRight(block);
    }
    if (IsKeyPressed(KEY_LEFT)) {
        moveBlockLeft(block);
    }
    if (IsKeyPressed(KEY_DOWN)) {
        moveBlockDown(block);
    }
    if (IsKeyPressed(KEY_UP))
    {
        rotateBlock(block);
    }
    
}
