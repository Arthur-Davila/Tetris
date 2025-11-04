#ifndef COLORS_H
#define COLORS_H

#include <raylib.h>

// Cores para os blocos e a grade
extern const Color darkGrey;
extern const Color green;
extern const Color red;
extern const Color orange;
extern const Color yellow;
extern const Color purple;
extern const Color cyan;
extern const Color blue;

// Funções do módulo
Color *getCellColors(); // Agora retorna o ponteiro para o array estático de 8 cores.

#endif