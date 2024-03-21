#include "Palavras.h"

#define alloc_size 11000

void import_dictionary(char **dictionary[16], int indexes[16], char *dict_name, int MAX_SIZE)
{
    FILE *fp_eng = fopen(dict_name,"r"); //abertura do ficheiro do dicionário com o nome introduzido no argumento -d
    int buffer_aux=0, word_size=0,word_aux=0;
    size_t len = 0;
    ssize_t read;
    bool found_invalid_char;
    char *buffer = NULL;

    for(buffer_aux=2; buffer_aux<MAX_SIZE+1; buffer_aux++){
        dictionary[buffer_aux] = ((char**)calloc(alloc_size, sizeof(char*))); //alocação inicial dos dicionários (apenas com palavras do tamanho MAX_SIZE para não alocar dicionários que não podem ser usados
    }

    while ((read = getline(&buffer, &len, fp_eng)) != -1) //Obtenção de uma linha que é copiada para um buffer
    {
        for(word_aux=0; word_aux<read; word_aux++){
            if(buffer[word_aux]=='/' || buffer[word_aux] == '\n' || buffer[word_aux] == ' ' || buffer[word_aux] == '\t'){ //verificaçao da palavra para apenas copiar a palavra e mais nada que esteja à frente
              buffer[word_aux]='\0'; //quando encontrar um destes caracteres, este é substituido por \0
              break; //este break vai servir para acabar o ciclo for e não analisar nada que esteja à frente
            }
        }
        word_size=word_aux;
        found_invalid_char = false;
        for (int i = 0; i < word_size; i++) { //aqui vamos percorrer a palavra toda
            if ((buffer[i] < 'a' || buffer[i] > 'z') ) { //se encontrarmos um char que não seja uma letra minuscula a palavra já nâo é valida
                found_invalid_char = true;
                break;
            }
        }
        if (!found_invalid_char && word_size <= MAX_SIZE && word_size >= 2) { //neste if só podem entrar palavras que passaram o ciclo for anterior inteiro sem tornar o found_invalid_char = true
            dictionary[word_size][indexes[word_size]] = ((char*)calloc(word_size+1, sizeof(char))); //alocação dinâmica apenas para a palavra que vai ser inserida
            strncpy(dictionary[word_size][indexes[word_size]],buffer,word_size+1); //copiar a string do buffer para o dicionário
            indexes[word_size]+=1;
        }
    }
    fclose(fp_eng);

    free(buffer); //é necessário no final libertar a memória do buffer, visto que o getline aloca automáticamente a memória para o mesmo

return;
}

//função igual a print_board mas com a utilização de fprintf para escrever o tabuleiro num ficheiro
void final_print_board(char board[16][16], char *final_board, int MAX_SIZE)
{
    FILE *fp= fopen(final_board,"w"); // abertura do ficheiro de nome inserido no argumento -o para escrita
    int line,column;

    for(line=1;line<=MAX_SIZE;line++){
        if((line>=10)){
            fprintf(fp,"%d ",line);
        }
        else{
            fprintf(fp,"%d  ",line);
        }
        for(column=1;column<=MAX_SIZE;column++){
            fprintf(fp," %c ",board[line][column]);
        }
    fprintf(fp,"\n");
     }

    fprintf(fp,"    ");

    for(column=1; column<=MAX_SIZE; column++){
        fprintf(fp,"%c  ", 64+column);
     }
    fprintf(fp,"\n");

    fclose(fp);

    return;
}

//função que lê o ficheiro das letras referente ao modos de jogo 3 e 4
void file_letter_reader(char *letter_file, int letter_nr, char *letters)
{
   FILE *fp= fopen(letter_file, "r"); //abertura do ficheiro com o nome inserido no argumento -l para leitura

   letters = malloc(letter_nr * sizeof(char)); //alocação de memória para o vetor que contem as letras

   for(int j=0;j<letter_nr;j++){
     fread(&letters[j], 1, sizeof(char), fp); //copia de cada letra do ficheiro para o vetor
   }

   fclose(fp);

   return;
}
