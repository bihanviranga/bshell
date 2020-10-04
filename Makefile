# Recursive wildcard function taken from https://stackoverflow.com/a/18258352

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

CC = gcc

CFLAGS = -Wall -g -Iinclude

TARGET = bshell

SRC = $(call rwildcard,src,*.c)

OBJ = $(SRC:.c=.o)

all: 	$(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

clean:
	$(RM) $(TARGET)
fclean: clean
	$(RM) $(OBJ)
