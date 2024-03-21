#include "palavras.h"

int word_input(char board[16][16], char input_column, int input_line, char orientation, char word[1][16],int *global_score, int *play_nr, int exit, int mode, int best_play, int MAX_SIZE)
{

    int i=0, score, letter_reuse=0, new_letter=0, word_size=0;
    char input_line_s[3], input[50];

    if(mode==1){
    printf("Make your play:\n");
    fgets(input, sizeof(input), stdin);
    sscanf(input, "%c%2s%c %s", &input_column, &input_line_s, &orientation, word[0]);

    //No caso de ser inserido um numero de dois digitos, são necessários os seguintes reajustes:
    if(input_line_s[1]<'0' || input_line_s[1]>'9'){
        orientation=input_line_s[1]; //Reajuste
        input_line= input_line_s[0]-48; //Conversão das linhas para o respetivo numero inteiro
    }
    //Conversão das linhas para o respetivo numero inteiro
    else{
        input_line= (input_line_s[0]-48)*10 + (input_line_s[1]-48)*1;
    }
    //Introdução da palavra fim
    if(input_column=='f' && strcmp(input_line_s, "im")==0)
    {
        printf("O score final foi %d\n", *global_score);
        exit=1;
        return exit;
    }


    while((input_column<'a' && input_column >'O') || (input_column>'o') || (input_column<'A') || (orientation!= 'h' && orientation!='H' && orientation!='v' && orientation!='V') || input_line<0 || input_line >MAX_SIZE){
        printf("Invalid play try again:\n");
        //Código identico ao que esta imediatamente acima
        fgets(input, sizeof(input), stdin);
        sscanf(input, "%c%2s%c %s", &input_column, &input_line_s, &orientation, word[0]);

        if(input_line_s[1]<'0' || input_line_s[1]>'9'){
        orientation=input_line_s[1];
        input_line= input_line_s[0]-48;
        }
        else{
            input_line= (input_line_s[0]-48)*10 + (input_line_s[1]-48)*1;
        }

        if(input_column=='f' && strcmp(input_line_s, "im")==0)
        {
            printf("O score final foi %d\n", *global_score);
            exit=1;
            return exit;
        }
    }

    word_size=strlen(word[0]);

    // Conversão das colunas e orientação para maisculas
    if(input_column>='a' && input_column<='o'){
        input_column=input_column-32;
    }
    if(orientation== 'h' || orientation=='v'){
        orientation=orientation-32;
    }
    //Conversão das letras maisculas da palavra para letras minusculas
    for(int i=0; i<word_size; i++){
        if(word[0][i]>= 'A' && word[0][i]<= 'Z'){
            word[0][i]=word[0][i]+32;
        }
    }
    //Conversão das colunas para o seu numero correspondente
    input_column=input_column-64;

    //Verificação das condições para a primeira jogada
    }

    word_size=strlen(word[0]);

    if(*play_nr==0){
        if(orientation=='H' && input_line==((MAX_SIZE-1)/2)+1 && ((input_column+word_size-1)>=((MAX_SIZE+1)/2))){
            if(((word_size+(input_column))-1)>MAX_SIZE){
                if(mode==1){
                    printf("The word doesn't fit the board\n");
                }
                *play_nr=0;
                if(mode!=1){
                    exit=1;
                }
                return exit;
            }

            score = score_counter(board, word, input_line, input_column, orientation, MAX_SIZE);
            *global_score=*global_score+score;

            for(int column_aux=input_column; column_aux<word_size+input_column; column_aux++){
                if(mode==1 || (mode!=1 && best_play==1)){
                board[input_line][column_aux]=word[0][i];
                i=i+1;
                }
            }
        }
        else{
            if(mode==1){
                printf("The first play must be horizontal, in the middle line and pass through the center of the board\n");
            }
            *play_nr=0;
            if(mode!=1){
                exit=1;
            }
            return exit;
        }
    }
    //Verificação das condições para jogadas subsquentes

    if(*play_nr!=0){
        if(orientation=='H'){
            for(int column_aux=input_column;column_aux<(word_size+(input_column));column_aux++){
                //Verificar se a palavra adiciona novas letras ao tabuleiro
                if(board[input_line][column_aux]==word[0][column_aux-input_column]){
                }
                else if(board[input_line][column_aux]=='$' || board[input_line][column_aux]=='2' || board[input_line][column_aux]=='.' || board[input_line][column_aux]=='3'){
                    new_letter=1;
                }
                if(board[input_line][column_aux]==word[0][column_aux-input_column]|| board[input_line][column_aux]=='$' || board[input_line][column_aux]=='2' || board[input_line][column_aux]=='.' || board[input_line][column_aux]=='3'){
                    if((word_size+(input_column-1))<=MAX_SIZE){ // Verificar se a palavra cabe no board
                    }
                    else{
                        if(mode==1){
                            printf("The word doesn't fit the board\n");
                        }
                        if(mode!=1){
                        exit=1;
                        }
                        return exit;
                    }
                    // Verificar se a letra em analise é igual a letra que se encontra no board
                    if (board[input_line][column_aux]==word[0][column_aux-input_column]){
                        letter_reuse=1;
                    }
                }

                //No caso em que a letra é diferente da que está no board ou se tenta escrever num cardinal, a jogada é invalida
                else{
                    if(mode==1){
                        printf("Letter different from the one previously written on the board or you tried to write over a #\n");
                    }
                    if(mode != 1){
                        exit=1;
                    }
                    return exit;
                }
            }


                if(((word_size+input_column-1 < MAX_SIZE) && (board[input_line][word_size+input_column]>='a' && board[input_line][word_size+input_column]<='z')) || ((input_column!=1) && (board[input_line][input_column-1]>='a' && board[input_line][input_column-1]<='z'))){
                    if(mode==1){
                        printf("Dont overlap words\n");
                    }
                    if(mode!=1){
                        exit=1;
                    }
                return exit;
                }
            //Se a jogada se verificar valida, é calculado o score e alterado o board

            if(new_letter==1 && letter_reuse==1){
                score = score_counter(board, word, input_line, input_column, orientation, MAX_SIZE);
                *global_score=*global_score+score;

                for(int column_aux=input_column;column_aux<(word_size+(input_column));column_aux++){
                        if(mode==1 || (mode!=1 && best_play==1)){
                            board[input_line][column_aux]=word[0][column_aux-input_column];
                            i=i+1;
                        }
                }
            }
            else{
                if (mode==1){
                    printf("Invalid play, try again\n");
                }
                if(mode!=1){
                    exit=1;
                }
                return exit;
            }
        }
        // Verificação das condições para a orientação vertical, a lógica é a mesma fazendo as alterações necessárias ao vetor board e word
        if(orientation=='V'){
            for(int line_aux=input_line;line_aux<(word_size+(input_line));line_aux++){
                if(board[line_aux][(int)input_column]==word[0][line_aux-input_line]){
                }
                else if(board[line_aux][(int)input_column]=='$' || board[line_aux][(int)input_column]=='2' || board[line_aux][(int)input_column]=='.' || board[line_aux][(int)input_column]=='3'){
                    new_letter=1;
                }
                if(board[line_aux][(int)input_column]==word[0][line_aux-input_line] || board[line_aux][(int)input_column]=='$' || board[line_aux][(int)input_column]=='2' || board[line_aux][(int)input_column]=='.' || board[line_aux][(int)input_column]=='3'){
                    if((word_size+(input_line-1))<=MAX_SIZE){ // A palavra cabe no board
                    }
                    else{
                        if (mode==1){
                            printf("The word doesn't fit the board\n");
                        }
                        if(mode!=1){
                            exit=1;
                        }
                        return exit;
                    }
                    if(board[line_aux][(int)input_column]==word[0][line_aux-input_line]){
                            letter_reuse=1;
                    }
                }
                else{
                    if(mode==1){
                        printf("Letter different from the one previously written on the board or you tried to write over a #\n");
                    }
                    if(mode!=1){
                        exit=1;
                    }
                    return exit;
                }

                if(((word_size+input_line-1 < MAX_SIZE) && (board[word_size+input_line][(int)input_column]>='a' && board[word_size+input_line][(int)input_column]<='z')) || ((input_line!=1) && (board[input_line-1][(int)input_column]>='a' && board[input_line-1][(int)input_column]<='z'))){
                    if(mode==1){
                        printf("Dont overlap words\n");
                    }
                    if(mode!=1){
                        exit=1;
                    }
                return exit;
                }
            }
            if(new_letter==1 && letter_reuse==1){
                score = score_counter(board, word, input_line, input_column, orientation, MAX_SIZE);
                *global_score=*global_score+score;

                for(int line_aux=input_line;line_aux<(word_size+(input_line));line_aux++){
                        if(mode==1 || (mode!=1 && best_play==1)){
                        board[line_aux][(int)input_column]=word[0][line_aux-input_line];
                        i=i+1;
                        }
                }
            }
            else{
                if(mode==1){
                    printf("Invalid play, try again\n");
                }
                if(mode!=1){
                exit=1;
                }
                return exit;
            }
        }
    }
    //Centralização do texto que indica a jogada e a respetiva pontuação

    if(mode==1 || (mode!=1 && best_play==1)){

        print_board(board, MAX_SIZE);

        printf("%c%d%c %s %d pontos\n", input_column+64, input_line, orientation, word[0], score);

        *play_nr=*play_nr+1;
    }

return exit;
}

/*********************************************************************************
* Nome da funcao: score_counter
*
* Return: ->score. Esta função da return da pontuação calculada para uma jogada
no tabuleiro.
*
* Descricao: A função vai percorrer a palavra e vai verificar onde esta irá ser
* inserida para poder contabilizar a pontuação referente as suas letras,como
* também a pontuação referente as bonus das casas especiais.
**********************************************************************************/
int score_counter(char board[16][16], char word[0][16], int input_line, char input_column, char orientation, int MAX_SIZE)
{
    int i, point_doubler=1, score=0;

    for(i=0; i<strlen(word[0]); i++){ //ler a palavra toda
                if (orientation=='H'){ //destinção para saber se a jogada foi feita na horizontal ou na vertical
                        if(board[input_line][((int)input_column)+i]=='$'){
                        point_doubler=point_doubler*2; //se uma das letras estiver numa casa com '$' o valor do point_doubler é multiplicado por 2 para ser postriormente multiplicado ao score final
                        }
                        if(board[input_line][((int)input_column)+i]=='3'){ //pontuação referente a cada letra caso calhe numa casa com o character '3'
                            if(word[0][i]== 'A' || word[0][i]== 'E' || word[0][i]== 'I' || word[0][i]== 'L' || word[0][i]== 'N' || word[0][i]== 'O' || word[0][i]== 'R' || word[0][i]== 'S' || word[0][i]== 'T' || word[0][i]== 'U' || word[0][i]== 'a' || word[0][i]== 'e' || word[0][i]== 'i' || word[0][i]== 'l' || word[0][i]== 'n' || word[0][i]== 'o' || word[0][i]== 'r' || word[0][i]== 's' || word[0][i]== 't' || word[0][i]== 'u'){
                                score=score + (3*1);
                                continue;
                            }
                            if(word[0][i]== 'D' || word[0][i]== 'G' || word[0][i]== 'd' || word[0][i]== 'g'){
                                score=score + (3*2);
                                continue;
                            }
                            if(word[0][i]== 'B' || word[0][i]== 'C' || word[0][i]== 'M' || word[0][i]== 'P' || word[0][i]== 'b' || word[0][i]== 'c' || word[0][i]== 'm' || word[0][i]== 'p'){
                                score=score + (3*3);
                                continue;
                            }
                            if(word[0][i]== 'F' || word[0][i]== 'H' || word[0][i]== 'V' || word[0][i]== 'W' || word[0][i]== 'Y' || word[0][i]== 'f' || word[0][i]== 'h' || word[0][i]== 'v' || word[0][i]== 'w' || word[0][i]== 'y'){
                                score=score + (3*4);
                                continue;
                            }
                            if(word[0][i]== 'K' || word[0][i]== 'k'){
                                score=score + (3*5);
                                continue;
                            }
                            if(word[0][i]== 'J' || word[0][i]== 'X' || word[0][i]== 'j' || word[0][i]== 'x'){
                                score=score + (3*8);
                                continue;
                            }
                            if(word[0][i]== 'Q' || word[0][i]== 'Z' || word[0][i]== 'q' || word[0][i]== 'z'){
                                score=score + (3*10);
                                continue;
                            }
                        }
                        if(board[input_line][((int)input_column)+i]=='2'){//pontuação referente a cada letra caso calhe numa casa com o character '2'
                            if(word[0][i]== 'A' || word[0][i]== 'E' || word[0][i]== 'I' || word[0][i]== 'L' || word[0][i]== 'N' || word[0][i]== 'O' || word[0][i]== 'R' || word[0][i]== 'S' || word[0][i]== 'T' || word[0][i]== 'U' || word[0][i]== 'a' || word[0][i]== 'e' || word[0][i]== 'i' || word[0][i]== 'l' || word[0][i]== 'n' || word[0][i]== 'o' || word[0][i]== 'r' || word[0][i]== 's' || word[0][i]== 't' || word[0][i]== 'u'){
                                score=score + (2*1);
                                continue;
                            }
                            if(word[0][i]== 'D' || word[0][i]== 'G' || word[0][i]== 'd' || word[0][i]== 'g'){
                                score=score + (2*2);
                                continue;
                            }
                            if(word[0][i]== 'B' || word[0][i]== 'C' || word[0][i]== 'M' || word[0][i]== 'b' || word[0][i]== 'c' || word[0][i]== 'm' || word[0][i]== 'P' || word[0][i]== 'p'){
                                score=score + (2*3);
                                continue;
                            }
                            if(word[0][i]== 'F' || word[0][i]== 'H' || word[0][i]== 'V' || word[0][i]== 'W' || word[0][i]== 'Y' || word[0][i]== 'f' || word[0][i]== 'h' || word[0][i]== 'v' || word[0][i]== 'w' || word[0][i]== 'y'){
                                score=score + (2*4);
                                continue;
                            }
                            if(word[0][i]== 'K' || word[0][i]== 'k'){
                                score=score + (2*5);
                                continue;
                            }
                            if(word[0][i]== 'J' || word[0][i]== 'X' || word[0][i]== 'j' || word[0][i]== 'x'){
                                score=score + (2*8);
                                continue;
                            }
                            if(word[0][i]== 'Q' || word[0][i]== 'Z' || word[0][i]== 'q' || word[0][i]== 'z'){
                                score=score + (2*10);
                                continue;
                            }
                        }
                        if(board[input_line][((int)input_column)+i]=='.' || board[input_line][((int)input_column)+i]=='$' || board[input_line][((int)input_column)+i]== word[0][i]){//pontuação referente a cada letra caso calhe numa casa com o character '.' ou '$' ou numa casa que ja contenha uma letra, visto que no caso do '$' o seu multiplicador ja foi contabilizado e no caso de uma casa repetida os multiplicadores do tabuleiro ja não se aplicam
                            if(word[0][i]== 'A' || word[0][i]== 'E' || word[0][i]== 'I' || word[0][i]== 'L' || word[0][i]== 'N' || word[0][i]== 'O' || word[0][i]== 'R' || word[0][i]== 'S' || word[0][i]== 'T' || word[0][i]== 'U' || word[0][i]== 'a' || word[0][i]== 'e' || word[0][i]== 'i' || word[0][i]== 'l' || word[0][i]== 'n' || word[0][i]== 'o' || word[0][i]== 'r' || word[0][i]== 's' || word[0][i]== 't' || word[0][i]== 'u'){
                                score=score + 1;
                                continue;
                            }
                            if(word[0][i]== 'D' || word[0][i]== 'G' || word[0][i]== 'd' || word[0][i]== 'g'){
                                score=score + 2;
                                continue;
                            }
                            if(word[0][i]== 'B' || word[0][i]== 'C' || word[0][i]== 'M' || word[0][i]=='P' || word[0][i]== 'b' || word[0][i]== 'c' || word[0][i]== 'm' || word[0][i]=='p'){
                                score=score + 3;
                                continue;
                            }
                            if(word[0][i]== 'F' || word[0][i]== 'H' || word[0][i]== 'V' || word[0][i]== 'W' || word[0][i]== 'Y' || word[0][i]== 'f' || word[0][i]== 'h' || word[0][i]== 'v' || word[0][i]== 'w' || word[0][i]== 'y'){
                                score=score + 4;
                                continue;
                            }
                            if(word[0][i]== 'K' || word[0][i]== 'k'){
                                score=score + 5;
                                continue;
                            }
                            if(word[0][i]== 'J' || word[0][i]== 'X' || word[0][i]== 'j' || word[0][i]== 'x'){
                                score=score + 8;
                                continue;
                            }
                            if(word[0][i]== 'Q' || word[0][i]== 'Z' || word[0][i]== 'q' || word[0][i]== 'z'){
                                score=score + 10;
                                continue;
                            }
                        }
                }
            if(orientation== 'V'){ //o mesmo vai ser replicado para as jogadas na vertical
                    if(board[input_line+i][(int)input_column]=='$'){
                        point_doubler=point_doubler*2;
                        }
                        if(board[input_line+i][(int)input_column]=='3'){
                            if(word[0][i]== 'A' || word[0][i]== 'E' || word[0][i]== 'I' || word[0][i]== 'L' || word[0][i]== 'N' || word[0][i]== 'O' || word[0][i]== 'R' || word[0][i]== 'S' || word[0][i]== 'T' || word[0][i]== 'U' || word[0][i]== 'a' || word[0][i]== 'e' || word[0][i]== 'i' || word[0][i]== 'l' || word[0][i]== 'n' || word[0][i]== 'o' || word[0][i]== 'r' || word[0][i]== 's' || word[0][i]== 't' || word[0][i]== 'u'){
                                score=score + (3*1);
                                continue;
                            }
                            if(word[0][i]== 'D' || word[0][i]== 'G' || word[0][i]== 'd' || word[0][i]== 'g'){
                                score=score + (3*2);
                                continue;
                            }
                            if(word[0][i]== 'B' || word[0][i]== 'C' || word[0][i]== 'M' || word[0][i]== 'P' || word[0][i]== 'b' || word[0][i]== 'c' || word[0][i]== 'm' || word[0][i]== 'p'){
                                score=score + (3*3);
                                continue;
                            }
                            if(word[0][i]== 'F' || word[0][i]== 'H' || word[0][i]== 'V' || word[0][i]== 'W' || word[0][i]== 'Y' || word[0][i]== 'f' || word[0][i]== 'h' || word[0][i]== 'v' || word[0][i]== 'w' || word[0][i]== 'y'){
                                score=score + (3*4);
                                continue;
                            }
                            if(word[0][i]== 'K' || word[0][i]== 'k'){
                                score=score + (3*5);
                                continue;
                            }
                            if(word[0][i]== 'J' || word[0][i]== 'X' || word[0][i]== 'j' || word[0][i]== 'x'){
                                score=score + (3*8);
                                continue;
                            }
                            if(word[0][i]== 'Q' || word[0][i]== 'Z' || word[0][i]== 'q' || word[0][i]== 'z'){
                                score=score + (3*10);
                                continue;
                            }
                        }
                        if(board[input_line+i][(int)input_column]=='2'){
                            if(word[0][i]== 'A' || word[0][i]== 'E' || word[0][i]== 'I' || word[0][i]== 'L' || word[0][i]== 'N' || word[0][i]== 'O' || word[0][i]== 'R' || word[0][i]== 'S' || word[0][i]== 'T' || word[0][i]== 'U' || word[0][i]== 'a' || word[0][i]== 'e' || word[0][i]== 'i' || word[0][i]== 'l' || word[0][i]== 'n' || word[0][i]== 'o' || word[0][i]== 'r' || word[0][i]== 's' || word[0][i]== 't' || word[0][i]== 'u'){
                                score=score + 2*1;
                                continue;
                            }
                            if(word[0][i]== 'D' || word[0][i]== 'G' || word[0][i]== 'd' || word[0][i]== 'g'){
                                score=score + 2*2;
                                continue;
                            }
                            if(word[0][i]== 'B' || word[0][i]== 'C' || word[0][i]== 'M' || word[0][i]== 'b' || word[0][i]== 'c' || word[0][i]== 'm'){
                                score=score + 2*3;
                                continue;
                            }
                            if(word[0][i]== 'F' || word[0][i]== 'H' || word[0][i]== 'V' || word[0][i]== 'W' || word[0][i]== 'Y' || word[0][i]== 'f' || word[0][i]== 'h' || word[0][i]== 'v' || word[0][i]== 'w' || word[0][i]== 'y'){
                                score=score + 2*4;
                                continue;
                            }
                            if(word[0][i]== 'K' || word[0][i]== 'k'){
                                score=score + 2*5;
                                continue;
                            }
                            if(word[0][i]== 'J' || word[0][i]== 'X' || word[0][i]== 'j' || word[0][i]== 'x'){
                                score=score + 2*8;
                                continue;
                            }
                            if(word[0][i]== 'Q' || word[0][i]== 'Z' || word[0][i]== 'q' || word[0][i]== 'z'){
                                score=score + 2*10;
                                continue;
                            }
                        }
                        if(board[input_line+i][(int)input_column]=='.' || board[input_line+i][(int)input_column]=='$' || board[input_line+i][(int)input_column]== word[0][i]){
                            if(word[0][i]== 'A' || word[0][i]== 'E' || word[0][i]== 'I' || word[0][i]== 'L' || word[0][i]== 'N' || word[0][i]== 'O' || word[0][i]== 'R' || word[0][i]== 'S' || word[0][i]== 'T' || word[0][i]== 'U' || word[0][i]== 'a' || word[0][i]== 'e' || word[0][i]== 'i' || word[0][i]== 'l' || word[0][i]== 'n' || word[0][i]== 'o' || word[0][i]== 'r' || word[0][i]== 's' || word[0][i]== 't' || word[0][i]== 'u'){
                                score=score + 1;
                                continue;
                            }
                            if(word[0][i]== 'D' || word[0][i]== 'G' || word[0][i]== 'd' || word[0][i]== 'g'){
                                score=score + 2;
                                continue;
                            }
                            if(word[0][i]== 'B' || word[0][i]== 'C' || word[0][i]== 'M' || word[0][i]=='P' || word[0][i]== 'b' || word[0][i]== 'c' || word[0][i]== 'm' || word[0][i]=='p'){
                                score=score + 3;
                                continue;
                            }
                            if(word[0][i]== 'F' || word[0][i]== 'H' || word[0][i]== 'V' || word[0][i]== 'W' || word[0][i]== 'Y' || word[0][i]== 'f' || word[0][i]== 'h' || word[0][i]== 'v' || word[0][i]== 'w' || word[0][i]== 'y'){
                                score=score + 4;
                                continue;
                            }
                            if(word[0][i]== 'K' || word[0][i]== 'k'){
                                score=score + 5;
                                continue;
                            }
                            if(word[0][i]== 'J' || word[0][i]== 'X' || word[0][i]== 'j' || word[0][i]== 'x'){
                                score=score + 8;
                                continue;
                            }
                            if(word[0][i]== 'Q' || word[0][i]== 'Z' || word[0][i]== 'q' || word[0][i]== 'z'){
                                score=score + 10;
                                continue;
                            }
                        }
                }
    }
    score=score*point_doubler; //por fim multiplicamos o score pelo multiplicador referente as casas '$' e damos reset ao valor do point_doubler
    point_doubler=1;

return score;
}
