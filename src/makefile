CC = gcc
CFLAGS = -Iblocks -Icolors -Igrid -IGame -Imenu -Ileaderboard
LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

SRC = main.c \
      blocks/blocks.c \
      colors/colors.c \
      grid/grid.c \
      Game/game.c \
      menu/menu.c \
      leaderboard/leaderboard.c

OBJ = $(SRC:.c=.o)

tetris: $(OBJ)
	$(CC) $(OBJ) -o tetris $(LIBS)

clean:
	rm -f $(OBJ) tetris

