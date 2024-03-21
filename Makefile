CC = gcc #compiler
CFLAGS = -Wall -O3 -g #flags de compilação

TARGET = palavras #target file name

OBJECTS = palavras.o Board_funcs.o Board_Plays.o FileIO_funcs.o Free_mem.o Algor_Jogo.o  #objects

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET)

palavras.o: palavras.c palavras.h
	$(CC) -c palavras.c
Board_funcs.o: Board_funcs.c palavras.h
	$(CC) -c Board_funcs.c
Board_plays.o: Board_Plays.c palavras.h
	$(CC) -c Board_Plays.c
FileIO_funcs.o: FileIO_funcs.c palavras.h
	$(CC) -c FileIO_funcs.c
Free_mem.o: Free_mem.c palavras.h
	$(CC) -c Free_mem.c
Algor_jogo.o: Algor_Jogo.c palavras.h
	$(CC) -c Algor_Jogo.c	

clean:
	rm -f $(TARGET) *.o 
