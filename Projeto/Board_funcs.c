#include "Palavras.h"

//Função que cria o tabuleiro
void reset_board(char board[16][16],int line,int column, int MAX_SIZE)
{
    if((line==1 || line==MAX_SIZE) && (column==1 || column==MAX_SIZE)){ //colocação dos '$' nos cantos do tabuleiro
        board[line][column]='$';
    }
    else{
        if(((line==1 || line==MAX_SIZE) && (column==((MAX_SIZE+1)/2))) || ((column==1 || column==MAX_SIZE) && (line==((MAX_SIZE+1)/2)))){ //colocação dos '3' na primeira e ultima linha, no centro das colunas, ou na primeira e ultima coluna, no centro das linhas
           board[line][column]='3';
        }
        else{
            if((line!=1 && line!=MAX_SIZE) && (line==column || line==(MAX_SIZE-column)+1)){ //colocação dos '2' na cruz central do tabuleiro
               board[line][column]='2';
            }
            else{
                if(((line==2 || line==(MAX_SIZE-1)) && (column==(MAX_SIZE-1)/2 || column==((MAX_SIZE+1)/2)+1)) || ((column==2 || column==(MAX_SIZE-1)) && (line==(MAX_SIZE-1)/2 || line==((MAX_SIZE+1)/2)+1))){ //colocação dos '#'
                   board[line][column]='#';
                }
                else{
                   board[line][column]='.'; //colocação de pontos nos restantes locais do tabuleiro
                }
            }
        }
    }

return;
}

//função que imrpime o tabuleiro
void print_board(char board[16][16], int MAX_SIZE)
{
    int line,column;

    for(line=1;line<=MAX_SIZE;line++){ //ciclo for que percorre todas as linhas
        if((line>=10)){
            printf("%d ",line); //para propositos de centralização dos valores, se o numero das linhas for maior ou igual a 10 deixamos so 1 espaço
        }
        else{
            printf("%d  ",line);//se tiver nove ou menos digitos deixamos dois espaços
        }
        for(column=1;column<=MAX_SIZE;column++){ //este ciclo for percorre as colunas todas
            printf(" %c ",board[line][column]); //imprimimos os valores que estiverem guardados no tabuleiro quer eles sejam os valors "resetados" ou com palavras no mesmo
        }
    printf("\n"); //imprimimos um tab entre linhas do tabuleiro
     }

    printf("    "); //espaços entre as colunas do tabuleiro

    for(column=1; column<=MAX_SIZE; column++){ //este ciclo vai, no final percorrer todas as colunas novamente para poder escrever as letras por debaixo do mesmo
        printf("%c  ", 64+column);
     }
    printf("\n");

    return;
}
