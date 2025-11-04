// colors/colors.c (Corrigido)

#include <stdlib.h>
#include <raylib.h>
#include "colors.h"

// Definição das cores (extern no .h)
const Color darkGrey = (Color){26, 31, 50, 255};
const Color green = (Color){47, 230, 23, 255};
const Color red = (Color){238, 18, 18, 255};
const Color orange = (Color){226, 116, 17, 255};
const Color yellow = (Color){237, 234, 4, 255};
const Color purple = (Color){166, 0, 247, 255};
const Color cyan = (Color){21, 204, 209, 255};
const Color blue = (Color){13, 64, 216, 255};

// Retorna o ponteiro para o array estático de cores para evitar vazamento
Color *getCellColors() {
    // Array estático que existe durante toda a execução do programa
    static Color allColors[8]; 
    static int isInitialized = 0;

    if (!isInitialized) {
        // Inicializa o array de cores (índice 0 = Cor da célula vazia)
        allColors[0] = darkGrey; 
        allColors[1] = green; 
        allColors[2] = red; 
        allColors[3] = orange; 
        allColors[4] = yellow; 
        allColors[5] = purple; 
        allColors[6] = cyan; 
        allColors[7] = blue; 

        isInitialized = 1;
    }

    return allColors;
}

// REMOVIDAS as funções createColorVector, pushColor, getColor e destroyColorVector
// para eliminar a referência ao tipo ColorVector.