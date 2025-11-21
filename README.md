# Tetris
Tetris em C utilizando a biblioteca raylib.

Comandos de execução:
cd src
gcc main.c blocks/blocks.c colors/colors.c grid/grid.c Game/game.c menu/menu.c -o Tetris.exe -I./raylib/include -I./blocks -I./colors -I./grid -I./Game -I./Menu -L./raylib/lib -lraylib -lopengl32 -lgdi32 -lwinmm -mwindows

Contribuidores
- Nathália Carvalho
- Arthur D'ávila
- Maria Eduarda