#include "blocks.h"
#include <stdlib.h>
#include <stdio.h>


int cellsize = 30;
int rotatioState = 0;

Block createBlockL(void) {
    Block l;
    l.id = 1;

    Color* colors = getCellColors();
    l.color = colors[l.id];

    for (int i = 0; i < 4; i++) {
        l.pos[i] = malloc(4 * sizeof(Pos));
    }

    l.pos[0][0] = (Pos){0, 2};
    l.pos[0][1] = (Pos){1, 0};
    l.pos[0][2] = (Pos){1, 1};
    l.pos[0][3] = (Pos){1, 2};

    l.pos[1][0] = (Pos){0, 1};
    l.pos[1][1] = (Pos){1, 1};
    l.pos[1][2] = (Pos){2, 1};
    l.pos[1][3] = (Pos){2, 2};

    l.pos[2][0] = (Pos){1, 0};
    l.pos[2][1] = (Pos){1, 1};
    l.pos[2][2] = (Pos){1, 2};
    l.pos[2][3] = (Pos){2, 0};

    l.pos[3][0] = (Pos){0, 0};
    l.pos[3][1] = (Pos){0, 1};
    l.pos[3][2] = (Pos){1, 1};
    l.pos[3][3] = (Pos){2, 1};

    return l;
}

Block createBlockT(void) {
    Block t;
    t.id = 2;

    Color* colors = getCellColors();
    t.color = colors[t.id];

    for (int i = 0; i < 4; i++) {
        t.pos[i] = malloc(4 * sizeof(Pos));
    }

    t.pos[3][0] = (Pos){0, 1};
    t.pos[3][1] = (Pos){1, 0};
    t.pos[3][2] = (Pos){1, 1};
    t.pos[3][3] = (Pos){1, 2};

    t.pos[1][0] = (Pos){0, 1};
    t.pos[1][1] = (Pos){1, 1};
    t.pos[1][2] = (Pos){1, 2};
    t.pos[1][3] = (Pos){2, 1};

    t.pos[2][0] = (Pos){1, 0};
    t.pos[2][1] = (Pos){1, 1};
    t.pos[2][2] = (Pos){1, 2};
    t.pos[2][3] = (Pos){2, 1};

    t.pos[0][0] = (Pos){0, 1};
    t.pos[0][1] = (Pos){1, 0};
    t.pos[0][2] = (Pos){1, 1};
    t.pos[0][3] = (Pos){2, 1};

    return t;
}
Block createBlockZ(void) {
    Block z;
    z.id = 3;

    Color* colors = getCellColors();
    z.color = colors[z.id];

    for (int i = 0; i < 4; i++) {
        z.pos[i] = malloc(4 * sizeof(Pos));
    }

    z.pos[0][0] = (Pos){0, 0};
    z.pos[0][1] = (Pos){0, 1};
    z.pos[0][2] = (Pos){1, 1};
    z.pos[0][3] = (Pos){1, 2};

    z.pos[1][0] = (Pos){0, 2};
    z.pos[1][1] = (Pos){1, 1};
    z.pos[1][2] = (Pos){1, 2};
    z.pos[1][3] = (Pos){2, 1};

    z.pos[2][0] = (Pos){1, 0};
    z.pos[2][1] = (Pos){1, 1};
    z.pos[2][2] = (Pos){2, 1};
    z.pos[2][3] = (Pos){2, 2};

    z.pos[3][0] = (Pos){0, 1};
    z.pos[3][1] = (Pos){1, 0};
    z.pos[3][2] = (Pos){1, 1};
    z.pos[3][3] = (Pos){2, 0};

    return z;
}
Block createBlockJ(void) {
    Block j;
    j.id = 4;

    Color* colors = getCellColors();
    j.color = colors[j.id];

    for (int i = 0; i < 4; i++) {
        j.pos[i] = malloc(4 * sizeof(Pos));
    }

    j.pos[0][0] = (Pos){0, 0};
    j.pos[0][1] = (Pos){1, 0};
    j.pos[0][2] = (Pos){1, 1};
    j.pos[0][3] = (Pos){1, 2};

    j.pos[1][0] = (Pos){0, 1};
    j.pos[1][1] = (Pos){0, 2};
    j.pos[1][2] = (Pos){1, 1};
    j.pos[1][3] = (Pos){2, 1};

    j.pos[2][0] = (Pos){1, 0};
    j.pos[2][1] = (Pos){1, 1};
    j.pos[2][2] = (Pos){1, 2};
    j.pos[2][3] = (Pos){2, 2};

    j.pos[3][0] = (Pos){0, 1};
    j.pos[3][1] = (Pos){1, 1};
    j.pos[3][2] = (Pos){2, 0};
    j.pos[3][3] = (Pos){2, 1};

    return j;
}
Block createBlockI(void) {
    Block i;
    i.id = 5;

    Color* colors = getCellColors();
    i.color = colors[i.id];

    for (int r = 0; r < 4; r++) {
        i.pos[r] = malloc(4 * sizeof(Pos));
    }

    i.pos[0][0] = (Pos){0, 1};
    i.pos[0][1] = (Pos){1, 1};
    i.pos[0][2] = (Pos){2, 1};
    i.pos[0][3] = (Pos){3, 1};

    i.pos[1][0] = (Pos){2, 0};
    i.pos[1][1] = (Pos){2, 1};
    i.pos[1][2] = (Pos){2, 2};
    i.pos[1][3] = (Pos){2, 3};

    i.pos[2][0] = (Pos){0, 2};
    i.pos[2][1] = (Pos){1, 2};
    i.pos[2][2] = (Pos){2, 2};
    i.pos[2][3] = (Pos){3, 2};

    i.pos[3][0] = (Pos){1, 0};
    i.pos[3][1] = (Pos){1, 1};
    i.pos[3][2] = (Pos){1, 2};
    i.pos[3][3] = (Pos){1, 3};

    return i;
}
Block createBlockO(void) {
    Block o;
    o.id = 6;

    Color* colors = getCellColors();
    o.color = colors[o.id];

    for (int i = 0; i < 4; i++) {
        o.pos[i] = malloc(4 * sizeof(Pos));
    }

    o.pos[0][0] = (Pos){0, 0};
    o.pos[0][1] = (Pos){0, 1};
    o.pos[0][2] = (Pos){1, 0};
    o.pos[0][3] = (Pos){1, 1};

    o.pos[1][0] = (Pos){0, 0};
    o.pos[1][1] = (Pos){0, 1};
    o.pos[1][2] = (Pos){1, 0};
    o.pos[1][3] = (Pos){1, 1};

    o.pos[2][0] = (Pos){0, 0};
    o.pos[2][1] = (Pos){0, 1};
    o.pos[2][2] = (Pos){1, 0};
    o.pos[2][3] = (Pos){1, 1};

    o.pos[3][0] = (Pos){0, 0};
    o.pos[3][1] = (Pos){0, 1};
    o.pos[3][2] = (Pos){1, 0};
    o.pos[3][3] = (Pos){1, 1};

    return o;
}
Block createBlockS(void) {
    Block s;
    s.id = 7;

    Color* colors = getCellColors();
    s.color = colors[s.id];

    for (int i = 0; i < 4; i++) {
        s.pos[i] = malloc(4 * sizeof(Pos));
    }

    s.pos[0][0] = (Pos){0, 1};
    s.pos[0][1] = (Pos){0, 2};
    s.pos[0][2] = (Pos){1, 0};
    s.pos[0][3] = (Pos){1, 1};

    s.pos[1][0] = (Pos){0, 1};
    s.pos[1][1] = (Pos){1, 1};
    s.pos[1][2] = (Pos){1, 2};
    s.pos[1][3] = (Pos){2, 2};

    s.pos[2][0] = (Pos){1, 1};
    s.pos[2][1] = (Pos){1, 2};
    s.pos[2][2] = (Pos){2, 0};
    s.pos[2][3] = (Pos){2, 1};

    s.pos[3][0] = (Pos){0, 0};
    s.pos[3][1] = (Pos){1, 0};
    s.pos[3][2] = (Pos){1, 1};
    s.pos[3][3] = (Pos){2, 1};

    return s;
}
void rotate(Block *block) {
    block->offsetCol = 0;
    block->offsetRow = 0;
    rotatioState = (rotatioState + 1) % 4;
}

void undoRotate(Block *block) {
    rotatioState = (rotatioState + 3) % 4;
}

void moveBlock(int col, int row, Block *block) {
    block->offsetCol = col;
    block->offsetRow = row;
    for (int r = 0; r < 4; r++){
        for (int i = 0; i < 4; i++){
            block->pos[r][i].x += block->offsetCol;
            block->pos[r][i].y += block->offsetRow;
        }
    }
    
}

void Draw(Block block) {
    for (int i = 0; i < 4; i++) {
        DrawRectangle(
            block.pos[rotatioState][i].x * (cellsize)+11,
            block.pos[rotatioState][i].y * (cellsize )+11,
            cellsize - 1,
            cellsize - 1,
            block.color
        );
    }
}

void DrawBlockInPanel(Block block, int panelX, int panelY, int panelWidth, int panelHeight) {
    int centerX = panelX + panelWidth / 2;
    int centerY = panelY + panelHeight / 2;
    
    int offsetX = centerX - (cellsize * 2); 
    int offsetY = centerY - (cellsize * 2);
    
    switch (block.id) {
        case 1: // L
            offsetX += cellsize / 2;
            offsetY += cellsize / 2;
            break;
        case 2: // T
            offsetX += cellsize / 2;
            offsetY += cellsize / 2;
            break;
        case 3: // Z
            offsetX += cellsize / 2;
            offsetY += cellsize / 2;
            break;
        case 4: // J
            offsetX += cellsize / 2;
            offsetY += cellsize / 2;
            break;
        case 5: // I
            offsetX += cellsize / 2;
            offsetY += cellsize;
            break;
        case 6: // O
            offsetX += cellsize;
            offsetY += cellsize;
            break;
        case 7: // S
            offsetX += cellsize / 2;
            offsetY += cellsize / 2;
            break;
    }
    
    for (int i = 0; i < 4; i++) {
        DrawRectangle(
            block.pos[0][i].x * cellsize + offsetX,
            block.pos[0][i].y * cellsize + offsetY,
            cellsize - 1,
            cellsize - 1,
            block.color
        );
    }
}
