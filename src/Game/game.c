#include "game.h"
#include <stdlib.h>
#include <time.h> // Para seed rand
#include <stdio.h> // Para fprintf (bom para debug)

// --- Funções Auxiliares de Gerenciamento de Memória ---

// Libera toda a memória dinâmica alocada DENTRO de uma struct Block.
void destroyBlock(Block block) {
    for (int i = 0; i < 4; i++) {
        // Verifica se o ponteiro foi alocado antes de liberar
        if (block.pos[i] != NULL) {
            free(block.pos[i]);
            block.pos[i] = NULL;
        }
    }
}

// --- Funções de Gerenciamento de Jogo ---

void initGame(Game *game) {
    srand(time(NULL)); // Inicializa a semente randômica
    
    // A função 'inicializarMatriz' está definida em grid.c
    inicializarMatriz(&game->grid);
    
    // Inicializa a lista de blocos disponíveis e pega os dois primeiros
    game->nextBlocks = getBlocks();
    game->currentBlock = getRandomBlock(&game->nextBlocks);
    game->nextBlock = getRandomBlock(&game->nextBlocks);
}

void DrawGame(Game *game) {
    DrawGameGrid(&game->grid);
    // DrawBlock espera o bloco atual (a movimentação é gerenciada via gridRow/gridCol na struct)
    DrawBlock(game->currentBlock); 
    // TODO: Adicionar desenho do nextBlock
}

// --- Funções de Lista de Blocos ---

BlockNode* create_node(Block block) {
    BlockNode *node = malloc(sizeof(BlockNode));
    if (node == NULL) {
        fprintf(stderr, "Erro de alocação de BlockNode\n");
        return NULL;
    }
    // A struct Block é copiada por valor.
    node->block = block; 
    node->next = NULL;
    return node;
}

BlockNode* getBlocks(void) {
    BlockNode *head = NULL, *aux = NULL;
    
    // Chamadas às funções de criação de blocos.
    // O array local 'all' armazena as structs Block (que contêm ponteiros alocados via malloc em blocks.c)
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
    if (*head == NULL) *head = getBlocks();

    int size = 0;
    BlockNode *aux = *head, *prev = NULL;
    while (aux) { size++; aux = aux->next; }

    if (size == 0) { // Erro de segurança, embora getBlocks deva evitar isso.
        fprintf(stderr, "Erro: Lista de blocos vazia.\n");
        exit(EXIT_FAILURE);
    }
    
    int idx = rand() % size;
    aux = *head;

    // Percorre até o índice
    for (int i = 0; i < idx; i++) {
        prev = aux;
        aux = aux->next;
    }

    // Remove o nó da lista
    if (prev) prev->next = aux->next;
    else *head = aux->next;

    // Copia o bloco escolhido (a nova cópia será o currentBlock/nextBlock)
    Block chosen = aux->block; 
    
    // CRÍTICO: O bloco que estava no nó ('aux->block') ALOCOU memória.
    // Essa memória deve ser liberada ANTES de liberar o nó.
    destroyBlock(aux->block);

    free(aux); // Libera o nó em si
    return chosen;
}