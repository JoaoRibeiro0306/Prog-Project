#include "palavras.h"

#define alloc_size 11000

/*********************************************************************************
* Nome da funcao: import_dictionary
*
* Return: Nada
*
* Descricao: Esta funcao vai ser importante para importar os diferentes dicionários
tendo em conta as palavras que não são válidas, eliminando-as do mesmo, e tendo também
em conta a formatação predefinida neste mesmo dicionário. A função vai também alocar,
dinamicamente memória para guardar este vetor com todas as palavras.
  A variavel dictionary encontra-se na forma char***, pois esta representa varios
dicionários, cada um com apenas palavras do mesmo tamanho.
**********************************************************************************/
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

/*********************************************************************************
* Nome da funcao: final_print_board
*
* Return: Nada
*
* Descricao: Esta funcao vai ser identica à função print_board, previamente
* comentada com a pequena diferença que este tabuleiro é copiado para um ficheiro
* .txt, logo será necessário utilizar fprint e abrir um ficheiro no modo de escrita
**********************************************************************************/
void final_print_board(char board[16][16], char *final_board, int MAX_SIZE, int global_score)
{
    FILE *fp= fopen(final_board,"w+"); // abertura do ficheiro de nome inserido no argumento -o para escrita
    int line,column;

    for(line=1;line<=MAX_SIZE;line++){
        if((line>=10)){
            fprintf(fp,"%d",line);
        }
        else{
            fprintf(fp,"%d ",line);
        }
        for(column=1;column<=MAX_SIZE;column++){
            fprintf(fp," %c",board[line][column]);
        }
    fprintf(fp,"\n");
     }

    fprintf(fp,"   ");

    for(column=1; column<=MAX_SIZE; column++){
        fprintf(fp,"%c ", 64+column);
     }
    fprintf(fp,"\n");

    fprintf(fp,"A sua pontuação final foi de %d\n", global_score);

    fclose(fp);

    return;
}

/*********************************************************************************
* Nome da funcao: file_letter_reader
*
* Return: Nada
*
* Descricao: Esta funcao vai importar o ficheiro com as letras utilizadas no modo 3,
* alocando, dinamicamente, a memória para criar um vetor com essas mesmas letras.
**********************************************************************************/
void file_letter_reader(char *letter_file, char **letters)
{
   FILE *fp= fopen(letter_file, "r"); //abertura do ficheiro com o nome inserido no argumento -l para leitura
   long int file_size = 0;

   fseek(fp, 0, SEEK_END); //O ponteiro de ficheiro vai percorrer o mesmo até ao final para obter o numero total de letras permitindo a alocação exata de memória
   file_size = ftell(fp);
   rewind(fp);

   *letters = calloc((file_size+1),1);

   fread(*letters, 1, file_size, fp);

   fclose(fp);

   return;
}

void import_board(char *start_board, int MAX_SIZE, char board[16][16])
{
    FILE *fp=fopen(start_board,"r");
    int column_aux=0, line_aux=0;

    for(line_aux=1; line_aux<MAX_SIZE+1; line_aux++){
      fscanf(fp,"%*d");
      for(column_aux=1; column_aux<MAX_SIZE+1; column_aux++){
        fscanf(fp," %c", &board[line_aux][column_aux]);
      }
    }
}

