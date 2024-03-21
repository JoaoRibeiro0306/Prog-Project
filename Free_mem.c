#include "palavras.h"

/*******************************************************************************
* Nome da funcao: free_memory.
*
* Return: Nada.
*
* Descricao: Esta função vai simplesmente libertar toda a memória alocada
* durante todo o programa.
*******************************************************************************/
void free_memory(char **dictionary[16], int indexes[16], int MAX_SIZE, char *letter_file, char *letters)
{
    int dict_aux=2, index_aux = 0;

    for(dict_aux=2; dict_aux<MAX_SIZE+1; dict_aux++){
        for(index_aux=indexes[dict_aux]; index_aux >=0; index_aux--){
            free(dictionary[dict_aux][index_aux]); //sendo o vetor dicitonary um char ***, preciamos primeiro libertar a memória referente às palavras de cada dicionário e só depois é que podemos libertar a memória dos dicionários
        }
       free(dictionary[dict_aux]); //libertação da memória de cada dicionário
    }

    free(letters); //libertação da memória allocada na função file_letter_reader

return;
}
