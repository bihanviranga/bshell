CC = gcc

CFLAGS = -Wall -g -Iinclude

TARGET = bshell

SRC = src/main.c \
      src/builtin/builtin.c \
      src/builtin/cd.c \
      src/builtin/help.c \
      src/builtin/exit.c \
      src/builtin/reconfigure.c

OBJ = $(SRC:.c=.o)

all: 	$(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

clean:
	$(RM) $(TARGET)
fclean: clean
	$(RM) $(OBJ)
