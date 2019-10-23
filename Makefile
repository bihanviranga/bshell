CC = gcc
CFLAGS = -g -Wall
TARGET = bshell
RM = rm
RMFLAGS = -f

all: $(TARGET)

$(TARGET): main.o builtins.o 
		$(CC) $(CFLAGS) -o $(TARGET) main.o builtins.o

main.o: main.c builtins.h
	$(CC) -c main.c 

builtins.o: builtins.h builtins.c
	$(CC) -c builtins.c 

clean:
	$(RM) $(RMFLAGS) $(TARGET) *.o

