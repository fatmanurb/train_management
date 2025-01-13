CC = gcc
CFLAGS = -Wall -g
SRC = src/main.c src/train.c src/wagon.c src/material.c src/file_ops.c src/utils.c
INC = -Iinclude
OUT = train_management

all:
	$(CC) $(CFLAGS) $(SRC) $(INC) -o $(OUT)

clean:
	rm -f $(OUT)
