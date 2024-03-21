#include "palavras.h"

/*******************************************************************************
* Nome da funcao: algoritmo
*
* Return: end -> Esta variavel sera util para se entender quando e que o algoritmo
* ja determinou todas as melhores jogadas possiveis.
*
* Descricao: Esta funcao vai conjuntamente com a funcao word_input determinar
* a linha, coluna, orientacao e palavra que representam a melhor
* jogada possivel.
*******************************************************************************/
int algoritmo(char board[16][16], char* input_column, char* orientation, int* input_line, int play_nr, char word[0][16], char **dictionary[16], int indexes[16], int mode, int *best_play, int MAX_SIZE, int *global_score)
{
    int positions=1, current_input_line=1, current_input_column=1, position_nr=1, score_aux1=0, score_aux2=0, max_score=0, max_word_score=0, positions_checked=0, word_nr=0,
    word_size=MAX_SIZE, best_word_column=0, best_word_line=0, end=0;
    int incrementation_aux=1, position_nr_aux=0;
    char best_word[16]={}, best_word_orientation;

    //Algoritmo que determina a melhor jogada para a primeira jogada
    if(play_nr==0){
        *input_line=(MAX_SIZE+1)/2;
        *orientation='H';
        for(word_size=MAX_SIZE; word_size>=2; word_size--){
            for(word_nr=0; word_nr < indexes[word_size]; word_nr++){
                strncpy(word[0], dictionary[word_size][word_nr], word_size+1);
                word[0][ strcspn( word[0], "\n" ) ] = '\0';
                if((word_size<=MAX_SIZE) && ((word_size)>=((MAX_SIZE+1)/2))){ //Para palavras com tamanhos no invervalo de (MAX_SIZE+1)/2 até MAX_SIZE
                    positions=(MAX_SIZE-word_size)+1; // Determinacao do numero de posicoes diferentes maximo que palavras neste intervalo de tamanhos pode ter
                }
                else{ //Palavras com tamanhos entre 2 e (MAX_SIZE+1)/2, exclusive
                    positions=word_size; // Determinacao do numero de posicoes diferentes maximo que palavras neste intervalo de tamanhos pode ter
                    position_nr=(((MAX_SIZE+1)/2)-word_size)+1; //Determinacao do numero da primeira posicao, que para este tipo de palavras é diferente de 1 e varia com o tamanho
                    *input_column=position_nr;
                }
                if(positions==1){ //Nas palavras com apenas uma posicao possivel o valor de score dessa posicao sera o maximo
                    *input_column=position_nr;
                    max_word_score=score_counter(board, word, *input_line, *input_column, *orientation, MAX_SIZE);
                }
                else{ // Nas palavras com mais do que uma posicao possivel, é necessario determinar qual das posicoes tem o melhor score
                    do{
                        *input_column=position_nr;
                        score_aux1=score_counter(board, word, *input_line, *input_column, *orientation, MAX_SIZE);
                        *input_column=*input_column+1;
                        score_aux2=score_counter(board, word, *input_line, *input_column, *orientation, MAX_SIZE);
                        if(score_aux1>= score_aux2){
                            positions_checked=positions_checked+1;
                        }
                        else{
                            position_nr=position_nr+1;
                            positions_checked=positions_checked+1;
                        }
                    }
                    while(positions_checked<=positions);
                    positions_checked=0;
                    *input_column=position_nr;
                    position_nr=1;
                    max_word_score=score_counter(board, word, *input_line, *input_column, *orientation, MAX_SIZE);
                }
                //Primeira palavra (o score maximo para uma jogada que se determinou ate agora sera o da primeira palavra valida)
                if(word_nr==0 && (word_size==MAX_SIZE)){
                    max_score=max_word_score;
                    memset(best_word, 0, sizeof(best_word));
                    strncpy(best_word, word[0], word_size+1);
                    best_word[ strcspn( best_word, "\n" ) ] = '\0';
                    best_word_column=*input_column;
                }
                else{ // Atualizacao do score maximo com o novo melhor score encontrado, e sao guardadas as informacoes dessa jogada
                    if(max_score<max_word_score){
                        max_score=max_word_score;
                        memset(best_word, 0, sizeof(best_word));
                        strncpy(best_word, word[0], word_size+1);
                        best_word[ strcspn( best_word, "\n" ) ] = '\0';
                        best_word_column=*input_column;
                    }
                }
                memset(word, 0, sizeof(word[0]));
            }
        }
        strncpy(word[0],best_word, sizeof(best_word)+1);
        word[0][ strcspn( word[0], "\n" ) ] = '\0';
        *input_column=best_word_column;
        *best_play=1;
    }
    //Algoritmo que determina a melhor jogada para as jogada subsquentes a primeira jogada
    else{
        for(int orientation_aux=0; orientation_aux<2; orientation_aux++){
            if(orientation_aux==0){
                *orientation='V';
            }
            else{
                *orientation='H';
            }
            for(current_input_line=1; current_input_line<=MAX_SIZE; current_input_line++){
                for(current_input_column=1; current_input_column<=MAX_SIZE; current_input_column++){
                    if(board[current_input_line][current_input_column]>='a' &&  board[current_input_line][current_input_column]<='z'){
                        for(word_size=MAX_SIZE; word_size>=2; word_size--){
                            word_nr=0;
                            next_word:
                            *input_line=current_input_line;
                            *input_column=current_input_column;
                            for(; word_nr< indexes[word_size]; word_nr++){
                                strncpy(word[0], dictionary[word_size][word_nr], word_size+1);
                                word[0][ strcspn( word[0], "\n" ) ] = '\0';

                                if((word_size<=MAX_SIZE) && ((word_size)>=((MAX_SIZE+1)/2))){
                                    positions=(MAX_SIZE-word_size)+1;
                                    position_nr=1;
                                }
                                else{
                                    positions=word_size;
                                    if(*orientation=='H'){
                                        position_nr=(current_input_column-word_size)+1;
                                    }
                                    else{
                                        position_nr=(current_input_line-word_size)+1;
                                    }
                                }
                                if(positions==1){
                                    if(*orientation=='H'){
                                        position_nr=1;
                                        *input_column=position_nr;
                                    }
                                    if(*orientation=='V'){
                                        position_nr=1;
                                        *input_line=position_nr;
                                    }

                                    if(word_input(board, *input_column, *input_line, *orientation, word,&global_score, &play_nr, exit, mode, *best_play, MAX_SIZE)!=1){ //Verificacao que determina se a jogada e valida
                                        max_word_score=score_counter(board, word, *input_line, *input_column, *orientation, MAX_SIZE);
                                    }
                                    else{
                                        word_nr=word_nr+1;
                                        goto next_word; //Utilizacao do goto em alternativa ao break, uma vez que este utlimo saía do ciclo de nested for's e nao apenas do ultimo for
                                    }
                                }
                                else{ //Mini algoritmo que permite determinar a posicao com o valor de score mais alto, comparando as posicoes duas a duas e apenas "sobrevivendo" a mais forte
                                    do{
                                        if(*orientation=='H'){
                                            *input_column=position_nr;
                                        }
                                        if(*orientation=='V'){
                                            *input_line=position_nr;
                                        }

                                        if(word_input(board, *input_column, *input_line, *orientation, word,&global_score, &play_nr, exit, mode, *best_play, MAX_SIZE)!=1){
                                            score_aux1=score_counter(board, word, *input_line, *input_column, *orientation, MAX_SIZE);
                                        }
                                        else{
                                            score_aux1=0;
                                        }
                                        position_nr_aux=position_nr;
                                        position_nr=position_nr+incrementation_aux;

                                        if(*orientation=='H'){
                                            *input_column=position_nr;
                                        }
                                        if(*orientation=='V'){
                                            *input_line=position_nr;
                                        }

                                        if(word_input(board, *input_column, *input_line, *orientation, word,&global_score, &play_nr, exit, mode, *best_play, MAX_SIZE)!=1){
                                            score_aux2=score_counter(board, word, *input_line, *input_column, *orientation, MAX_SIZE);
                                        }
                                        else{
                                            score_aux2=0;
                                        }
                                        if(score_aux1>=score_aux2){
                                            position_nr=position_nr_aux;
                                            positions_checked=positions_checked+1;
                                            incrementation_aux=incrementation_aux+1;
                                        }
                                        else{
                                            positions_checked=positions_checked+1;
                                            incrementation_aux=1;
                                        }
                                    }while(positions_checked<positions);

                                    positions_checked=0;
                                    incrementation_aux=1;
                                    position_nr_aux=0;
                                    if(*orientation=='H'){
                                        *input_column=position_nr;
                                    }
                                    else{
                                        *input_line=position_nr;
                                    }
                                    if(word_input(board, *input_column, *input_line, *orientation, word,&global_score, &play_nr, exit, mode, *best_play, MAX_SIZE)!=1){
                                            max_word_score=score_counter(board, word, *input_line, *input_column, *orientation, MAX_SIZE);
                                    }
                                }

                                if(max_score!=0){
                                    if(max_score<max_word_score){
                                        max_score=max_word_score;
                                        memset(best_word, 0, sizeof(best_word));
                                        strncpy(best_word, word[0], word_size+1);
                                        best_word[ strcspn( best_word, "\n" ) ] = '\0';
                                        best_word_column=*input_column;
                                        best_word_line=*input_line;
                                        best_word_orientation=*orientation;
                                    }
                                }
                                //Primeira palavra
                                else{
                                    max_score=max_word_score;
                                    memset(best_word, 0, sizeof(best_word));
                                    strncpy(best_word, word[0], word_size+1);
                                    best_word[ strcspn( best_word, "\n" ) ] = '\0';
                                    best_word_column=*input_column;
                                    best_word_line=*input_line;
                                    best_word_orientation=*orientation;
                                }
                                memset(word, 0, sizeof(word[0]));
                            }
                        }
                    }
                }
            }
            strncpy(word[0],best_word, sizeof(best_word)+1);
            word[0][ strcspn( word[0], "\n" ) ] = '\0';
            *input_column=best_word_column;
            *input_line=best_word_line;
            *orientation=best_word_orientation;
            if(orientation_aux==0){ //Se ainda tivermos apenas visto as jogadas para a orientacao vertical, nao podemos afirmar que ja encontramos a melhor jogada
                *best_play=0;
            }
            else{ //Após verificadas todas as posicoes para a orientacao horizontal, ja se pode afirmar com seguranca que se encontrou a melhor jogada
                *best_play=1;
            }
        }
        if(max_score==0){ //Se o algoritmo nao conseguir encontrar mais nenhuma jogada valida.
            end=1;
        }
    }

return end;
}

int letters_in_hand(char word[0][16], char **letters, int word_size, int letter_nr)
{
  int word_aux, letters_aux,compare_aux=1;

  for(word_aux=0; word_aux<word_size; word_aux++){
    for(letters_aux=0; letters_aux<letter_nr; letters_aux++){
        if(word[0][word_aux] == letters[0][letters_aux]){
           compare_aux++;
           continue;
        }
    }
  }
  if(compare_aux != word_size){
    return 1;
  }

  return 0;
}
