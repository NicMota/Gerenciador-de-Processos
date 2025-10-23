#include <stdio.h>
#import <string.h>
#define MAX_DESC 50


typedef struct {
    int hh;
    int mm;
    int ss;
} horario;

typedef struct {
    int prior;
    horario chegada;
    char desc[MAX_DESC];
} celula;

int main()
{

    char* cmd;scanf("%s",cmd);

    
    while(strcmp(cmd, "quit") != 0){
        //adiciona um processo(celula) a lista de processos
        if(strcmp(cmd,"add") == 0)
        {

        }

        /*executa um processo
        -p executa o processo com maior prioridade
        -t executa o processo com menor tempo
        */
        if(strcmp(cmd,"exec") == 0)
        {

        }

        /*  mostra um processo
        -p mostra em uma linha todas as informacoes do processo com maior prioridade
        -t  mostra em uma linha todas as informacoes do processo com menor tempo
        */
        if(strcmp(cmd,"next") == 0)
        {

        }
        
        /*  modifica informacoes de um processo
        -p anterior:novo altera o campo prior com valor anterior para o valor novo
        -t anterior:novo altera o campo tempo com o valor anterior para o valor novo
        */
        if(strcmp(cmd,"change") == 0)
        {

        }

        /*  imprime todos os processos a serem executados 
        -p imprime todos os processos em ordem decrescente de prioridade prioridade, onde as informacoes de cada
        processo sao impressas em uma unica linha (prior, tempo e descricao).

        -t: imprime os processos em ordem crescente de horarios, onde as informacoes de cada 
        processo sao impressas em uma unica linha (prior, tempo e descricao)
        */
        if(strcmp(cmd,"print") == 0)
        {

        }
    }


}


