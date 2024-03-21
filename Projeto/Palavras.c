#include "Palavras.h"

int main(int argc, char *argv[])
{
    int MAX_SIZE = 9,letter_nr=10,mode=2, max_plays=0,option=0, printfile=0;
    char *letter_file = "letras.txt",*log_file = NULL, *dict_name = "/usr/share/dict/words", *final_board = NULL;

    while((option = getopt(argc, argv, "h t: d: l: m: n: i: j: o: r:")) != -1) //O getopt vai nos permitir parametrizar o programa atribunido argumentos a variáveis
    {
        switch(option)
        {
            case 'h':
                puts("=============================================================================================================================================================");
                puts("==AJUDA==   -t: A opção -t indica a dimensão do tabuleiro no formato linhaxcoluna -r: define ficheiro para registo de todas as jogadas possíveis.   ==AJUDA==");
                puts("==AJUDA==   -d: nome do ficheiro de dicionário a utilizar.                                                                                          ==AJUDA==");
                puts("==AJUDA==   -l: nome do ficheiro com letras a usar nas jogadas.                                                                                     ==AJUDA==");
                puts("==AJUDA==   -m: número de letras que um jogador pode ter na sua mão para jogar (5-20).                                                              ==AJUDA==");
                puts("==AJUDA==   -n: número de jogadas máximo a realizar.                                                                                                ==AJUDA==");
                puts("==AJUDA==   -i: define ficheiro com o tabuleiro a usar em alternativa a jogar num tabuleiro vazio.                                                  ==AJUDA==");
                puts("==AJUDA==   -j: define o modo de jogo, de 1 a 4.                                                                                                    ==AJUDA==");
                puts("==AJUDA==   -o: define ficheiro onde escrever o tabuleiro final.                                                                                    ==AJUDA==");
                puts("==AJUDA==   -r: define ficheiro para registo de todas as jogadas possíveis.                                                                         ==AJUDA==");
                puts("==AJUDA==   Desative o modo -h para conseguir inicializar o jogo.                                                                                   ==AJUDA==");
                puts("=============================================================================================================================================================");
                return 0;
            case 't':
                MAX_SIZE = atoi(optarg); // a função atoi, permite converter um char para um int
                break;
            case 'd':
                dict_name = optarg;
                break;
            case 'l':
                letter_file =optarg;
                break;
            case 'm':
                letter_nr= atoi(optarg);
                break;
            case 'n':
                max_plays= atoi(optarg);
                break;
            case 'i':
                break;
            case 'j':
                mode = atoi(optarg);
                break;
            case 'o':
                final_board= optarg;
                printfile=1;
                break;
            case 'r':
                log_file = optarg;
                break;
            case '?':
                printf("unknown option: %c\n", optopt); //em caso do utilizador introduzir um argumento que não se encontra presente no case switch, o programa avisa que esse argumento não existe e finaliza-se
                return 0;
        }
    }

    //Variaveis gerais
    int line, column, input_line=0,global_score=0, play_nr=0, exit=0;
    char board[16][16]={}, word[1][16]={}, orientation=0, input_column=0,*letters = NULL;
    //Variaveis relcionadas ao dicionario
    char **dictionary[16]={0}; // esta variável vai representar um vetor de dicionários, sendo que cada dicionário apenas contem palavras do mesmo tamanho para que seja possível organizar o dicionário por tamanho de palavra
    int indexes[16]={0}; //este vetor de inteiros vai conter o indice de cada dicionário para que possamos inserir cada palavra no seu lugar correto ao preencher os dicionários e saber quantas palavras tem cada um dos mesmos no final

    if(mode!=1){
        import_dictionary(dictionary, indexes, dict_name, MAX_SIZE);
    }

    if(mode==3 || mode==4){
        file_letter_reader(letter_file, letter_nr, letters);
    }

    //Criação inicial do tabuleiro com todas as casas especiais
    for(line=1;line<=MAX_SIZE;line++){
        for(column=1;column<=MAX_SIZE;column++){
            reset_board(board,line,column, MAX_SIZE);
        }
    }
    line=1;
    column=1;



    if(mode==1){
        print_board(board, MAX_SIZE);//no modo 1, começamos por inserir o tabuleiro no stdout para se iniciar o jogo
        while(play_nr<=max_plays && exit==0){ //fazemos este loop para o numero de jogadas inserido ou até ser escrito fim
            exit = word_input(board, input_column, input_line, orientation, word,&global_score, &play_nr, exit, mode, MAX_SIZE);
            print_board(board, MAX_SIZE);
            printf("\n");
        }
    }

    if (mode==2){
        algoritmo(board, &input_column, &orientation, &input_line, &play_nr, word, dictionary, indexes, global_score, &mode, MAX_SIZE);
        exit = word_input(board, input_column, input_line, orientation, &word[0],&global_score, &play_nr, exit, mode, MAX_SIZE);
        print_board(board, MAX_SIZE);
    }

    free_memory(dictionary, indexes, MAX_SIZE, &letter_file, letters);

    return 0;
}
