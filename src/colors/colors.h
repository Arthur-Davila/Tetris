#ifndef COLORS_H
#define COLORS_H

#include <raylib.h>

extern const Color darkGrey;
extern const Color green;
extern const Color red;
extern const Color orange;
extern const Color yellow;
extern const Color purple;
extern const Color cyan;
extern const Color blue;

Color *getCellColors(); // Agora retorna o ponteiro para o array estático de 8 cores.

#endif