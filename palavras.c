#include "palavras.h"

/********************************************************************************************************/
/* Programa: Palavras                                                                                    */
/*                                                                                                       */
/* Descrição: Este programa implementa uma versão particular de um jogo de palavras                      */
/*cruzadas onde se contemplam 4 modos de jogo com diferentes regras.                                     */
/*                                                                                                       */
/* Ficheiros:                                                                                            */
/*    (1) Palavras.c: função main() principal                                                            */
/*    (2) Board_Plays.c: funções para as jogadas no quadro                                               */
/*    (3) FileIO_funcs.c: leitura e escrita de/para ficheiros                                            */
/*    (4) Free_mem.c: Libertação de memória                                                              */
/*    (5) Board_funcs.c: Funcoes exclusivamente relacionadas com o quadro                                */
/*    (6) Algor_jogo.c: Funcao com algoritmo para os modos 2,3 e 4 e funcao para a restricao de letras   */
/*    (7) Palavras.h: Header com protótipos de todas as funcoes utilizadas no programa                   */
/*                                                                                                       */
/* Autoria:                                                                                              */
/*    João Ribeiro (nº:102715)                                                                           */
/*    Tiago Teixeira (nº:102638)                                                                         */
/*                                                                                                       */
/*********************************************************************************************************/

int main(int argc, char*argv[])
{
    int MAX_SIZE = 9,mode=2, max_plays=-1,option=0, columns=0, infinite_plays = 0;
    char *letter_file = "letras.txt", *dict_name = "/usr/share/dict/words", *final_board = NULL, *start_board = NULL;

    while((option = getopt(argc, argv, "h t: d: l: m: n: i: j: o: r: ")) != -1) //O getopt vai nos permitir parametrizar o programa atribunido argumentos a variáveis
    {
        switch(option)
        {
            case 'h':
                puts("=============================================================================================================================================================");
                puts("==AJUDA==   -t: A opção -t indica a dimensão do tabuleiro no formato linhaxcoluna -r: define ficheiro para registo de todas as jogadas possíveis.   ==AJUDA==");
                puts("==AJUDA==   -d: nome do ficheiro de dicionário a utilizar.                                                                                          ==AJUDA==");
                puts("==AJUDA==   -l: nome do ficheiro com letras a usar nas jogadas.                                                                                     ==AJUDA==");
                puts("==AJUDA==   -m: número de letras que um jogador pode ter na sua mão para jogar (5-20).  (Não implementado)                                          ==AJUDA==");
                puts("==AJUDA==   -n: número de jogadas máximo a realizar.                                                                                                ==AJUDA==");
                puts("==AJUDA==   -i: define ficheiro com o tabuleiro a usar em alternativa a jogar num tabuleiro vazio.                                                  ==AJUDA==");
                puts("==AJUDA==   -j: define o modo de jogo, de 1 a 4.                                                                                                    ==AJUDA==");
                puts("==AJUDA==   -o: define ficheiro onde escrever o tabuleiro final.                                                                                    ==AJUDA==");
                puts("==AJUDA==   -r: define ficheiro para registo de todas as jogadas possíveis. (Não implementado)                                                      ==AJUDA==");
                puts("==AJUDA==   Desative o modo -h para conseguir inicializar o jogo.                                                                                   ==AJUDA==");
                puts("=============================================================================================================================================================");
                return 0;
            case 't':
                sscanf(optarg,"%d%*c%d", &MAX_SIZE, &columns);
                if(MAX_SIZE != columns){
                    puts("O tabuleiro deve ser quadrado");
                    return EXIT_FAILURE;
                }
                break;
            case 'd':
                dict_name = optarg;
                break;
            case 'l':
                letter_file = optarg;
                break;
            case 'm':
                puts("Função -m não implementada\n");
                break;
            case 'n':
                max_plays = atoi(optarg);// a função atoi, permite converter um char para um int
                break;
            case 'i':
                start_board = optarg;
                break;
            case 'j':
                mode = atoi(optarg);
                if(mode==4){
                    puts("Modo de jogo não implementado\n");
                    return EXIT_FAILURE;
                }
                break;
            case 'o':
                final_board = optarg;
                break;
            case 'r':
                puts("Função -r não implementada\n");
                break;
            case '?':
                printf("Função desconhecida: %c\n", optopt); //em caso do utilizador introduzir um argumento que não se encontra presente no case switch, o programa avisa que esse argumento não existe e finaliza-se
                return 0;
        }
    }

    //Variaveis gerais
    int line, column, input_line=1,global_score=0, play_nr=0, exit=0, best_play=0, end=0, play_aux = 0;
    char board[16][16]={}, word[1][16]={}, orientation=0, input_column=1, print_stdout=0;
    //Variaveis relcionadas ao dicionario
    char  **dictionary[16]={0}, **letters = NULL;
    int indexes[16]={0};

    if(max_plays==-1){ //Condições para caso de omissão, ou não, de argumentos
        infinite_plays=1;
    }
    if(start_board!=NULL){
        play_nr=1;
    }
    if(final_board==NULL){
        print_stdout=1;
    }

    import_dictionary(dictionary, indexes, dict_name, MAX_SIZE);

    if(mode==3 || mode==4){
        file_letter_reader(letter_file, &letters);
    }

    if(play_nr==0){
        for(line=1;line<=MAX_SIZE;line++){
            for(column=1;column<=MAX_SIZE;column++){
                reset_board(board,line,column, MAX_SIZE);
            }
        }
        line=1;
        column=1;
    }
    else{
        import_board(start_board, MAX_SIZE, board);
    }

    if(mode==1){
        print_board(board, MAX_SIZE);
        while(play_nr>=0 && exit==0){
            exit = word_input(board, input_column, input_line, orientation, word,&global_score, &play_nr, exit, mode, best_play, MAX_SIZE);
            print_board(board, MAX_SIZE);
            printf("\n");
        }
    }

    if(mode!=1){
       if(infinite_plays != 1){
          for(play_aux=0; (play_aux<max_plays); play_aux++){
              end=algoritmo(board, &input_column, &orientation, &input_line, play_nr, word, dictionary, indexes, mode, &best_play, MAX_SIZE, &global_score);
              if(end==1){
                break;
              }
              if(end!=1){
                word_input(board, input_column, input_line, orientation, word,&global_score, &play_nr, exit, mode, best_play, MAX_SIZE);
              }
              best_play=0;
              memset(word, 0, sizeof(word));
          }
       }
       else{
           while(end!=1){
                end=algoritmo(board, &input_column, &orientation, &input_line, play_nr, word, dictionary, indexes, mode, &best_play, MAX_SIZE, &global_score);
                if(end!=1){
                    word_input(board, input_column, input_line, orientation, word,&global_score, &play_nr, exit, mode, best_play, MAX_SIZE);
                }
                best_play=0;
                memset(word, 0, sizeof(word));
           }
       }
    }

    printf("A sua pontuação final é :%d\n", global_score);

    if(print_stdout==0){
        final_print_board(board, final_board, MAX_SIZE, global_score);
    }
    else{
        printf("\n\n");
        print_board(board, MAX_SIZE);
        printf("A sua pontuação final foi de %d\n", global_score);
    }

    free_memory(dictionary, indexes, MAX_SIZE, letter_file, letters);

return 0;
}
