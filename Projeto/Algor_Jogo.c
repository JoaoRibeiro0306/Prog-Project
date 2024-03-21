#include "Palavras.h"

void algoritmo(char board[16][16], char* input_column, char* orientation, int* input_line, int play_nr, char word[0][16], char **dictionary[16], int indexes[16], int mode, int *best_play, int MAX_SIZE)
{
    int positions=1, position_nr=1, score_aux1=0, score_aux2=0, max_score=0, max_word_score=0, positions_checked=0, word_nr=0, word_size=0, best_word_column=0;
    char best_word[16]={};

    word_size = MAX_SIZE;

    if(play_nr==0){
        *input_line=(MAX_SIZE+1)/2;
        *orientation='H';
        for(word_size=MAX_SIZE; word_size>=2; word_size--){
            for(word_nr=0; word_nr < indexes[word_size]; word_nr++){
                strncpy(word[0], dictionary[word_size][word_nr], word_size+1);
                word[0][ strcspn( word[0], "\n" ) ] = '\0';
                if((word_size<=MAX_SIZE) && ((word_size)>=((MAX_SIZE+1)/2))){
                    positions=(MAX_SIZE-word_size)+1;
                }
                else{
                    positions=word_size;
                    position_nr=(((MAX_SIZE+1)/2)-word_size)+1;
                    *input_column=position_nr;
                }
                if(positions==1){
                    *input_column=position_nr;
                    max_word_score=score_counter(board, word, *input_line, *input_column, *orientation, MAX_SIZE);
                }
                else{
                    do{
                        *input_column=position_nr;
                        score_aux1=score_counter(board, word, *input_line, *input_column, *orientation, MAX_SIZE);
                        *input_column=*input_column+1;
                        score_aux2=score_counter(board, word, *input_line, *input_column, *orientation, MAX_SIZE);
                        if(score_aux1>= score_aux2){
                            positions_checked=positions_checked+2;
                        }
                        else{
                            position_nr=position_nr+1;
                            positions_checked=positions_checked+2;
                        }
                    }
                    while(positions_checked<positions);
                    positions_checked=0;
                    *input_column=position_nr;
                    position_nr=1;
                    max_word_score=score_counter(board, word, *input_line, *input_column, *orientation, MAX_SIZE);
                }
                //Primeira palavra
                if(word_nr==0 && (word_size==MAX_SIZE)){
                    max_score=max_word_score;
                    memset(best_word, 0, sizeof(best_word));
                    strncpy(best_word, word, word_size+1);
                    best_word[ strcspn( best_word, "\n" ) ] = '\0';
                    best_word_column=*input_column;
                }
                else{
                    if(max_score<max_word_score){
                        max_score=max_word_score;
                        memset(best_word, 0, sizeof(best_word));
                        strncpy(best_word, word, word_size+1);
                        best_word[ strcspn( best_word, "\n" ) ] = '\0';
                        best_word_column=*input_column;
                    }
                }
                memset(word, 0, sizeof(word[0]));
            }
        }
        strncpy(word[0],best_word, sizeof(best_word)+1);
        word[0][ strcspn( word, "\n" ) ] = '\0';
        *input_column=best_word_column;
    }
    return;
}
