CC = gcc
CFLAGS = -Wall -g
TARGET = bshell

all: 	$(TARGET)

$(TARGET): main.c
	$(CC) $(CFLAGS) -o $(TARGET) main.c

clean:
	$(RM) $(TARGET)
