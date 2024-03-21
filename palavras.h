#ifndef PALAVRA_H_INCLUDED
#define PALAVRA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <getopt.h>


/* Funções ralacionadas ao tabuleiro e modo de jogo 1 */

void reset_board(char [16][16], int, int, int );
void print_board(char [16][16], int );

/* Funções referentes as jogadas basicas do jogo */

int word_input(char [16][16], char , int , char , char [1][16],int *, int *, int , int , int, int );
int score_counter(char [16][16], char [0][16], int, char, char, int );

/*Funções de abertura de ficheiro para leitura ou escrita */

void import_dictionary(char **[16], int [16], char *, int );
void final_print_board(char [16][16], char *, int, int );
void file_letter_reader(char *, char **);
void import_board(char *, int , char [16][16]);

/* Função do algoritmo das jogadas */

int algoritmo(char [16][16], char * , char * , int * , int , char [0][16], char **[16], int [16], int , int *, int, int *);
int letters_in_hand(char [0][16], char **, int , int );

/* Libertação da memória alocada */

void free_memory(char **[16], int [16], int, char *, char *);

#endif

