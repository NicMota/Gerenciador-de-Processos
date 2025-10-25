#include <stdio.h>
#include <string.h>
#define MAX_DESC 50


typedef struct {
    int hh;
    int mm;
    int ss;
} tempo;

typedef struct {
    int prior;
    tempo chegada;
    char desc[MAX_DESC];
} celula;

void add(celula tarefa)
{
    //inserir código para adicionar processo aqui
}

void exec(char opcao)
{
    switch (opcao)
    {
        case 'p':
        {
            //inserir código para executar processo com maior prioridade aqui
            break;
        }

        case 't':
        {
            //inserir código para executar processo com menor tempo aqui
            break;
        }

        default: printf(
            "Por favor, escolha uma opção válida!\n"
            "-p: executar processo com maior prioridade\n"
            "-t: executar processo com menor tempo\n"
        );
    }
}

void next(char opcao)
{
switch (opcao)
    {
        case 'p':
        {
            //inserir código para mostrar processo com maior prioridade aqui
            break;
        }

        case 't':
        {
            //inserir código para mostrar processo com menor tempo aqui
            break;
        }

        default: printf(
            "Por favor, escolha uma opção válida!\n"
            "-p: mostrar informações do processo com maior prioridade\n"
            "-t: mostrar informações processo com menor tempo\n"
        );
    }
}

void change_prior(int anterior, int novo)
{
    //inserir código para mudar processo com prioridade aqui
}

void change_tempo(tempo anterior, tempo novo)
{
    //inserir código para mudar processo com tempo aqui
}

void print(char opcao)
{
    switch (opcao)
    {
        case 'p':
        {
            //inserir código para imprimir processos por prioridade aqui
            break;
        }

        case 't':
        {
            //inserir código para imprimir processos por tempo aqui
            break;
        }

        default: printf(
            "Por favor, escolha uma opção válida!\n"
            "-p: imprimir os processor em ordem decrescente de prioridade\n"
            "-t: imprimir os processor em ordem crescente de horários\n"
        );
    }
}

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


