CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Icolors -Iblocks -Igrid -IGame
LDFLAGS = -lraylib -lm -lpthread -ldl -lGL -lrt -lX11

SRC = main.c colors/colors.c blocks/blocks.c grid/grid.c Game/game.c
OBJ = $(SRC:.c=.o)
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)
