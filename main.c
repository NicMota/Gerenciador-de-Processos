#include <stdio.h>
#include <string.h>
#define MAX_DESC 50
#define MAX_PRIOR 100


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


int prioridades[MAX_PRIOR] = {}; //vetor de marcação de quais prioridades estão sendo utilizadas

int conversor_tempo(tempo t)
{
    return t.hh*3600 + t.mm*60 + t.ss;
}

void ordenar_prior(celula tarefas[]) //hash sort
{
    celula novo_tarefas[MAX_PRIOR];
    for (int i = 0; i < MAX_PRIOR; i++)
    {
        //copiar a tarefa para o índice correspondente à sua prioridade
        novo_tarefas[tarefas[i].prior] = tarefas[i];
        //marcar que a prioridade está sendo usada no mapa
        prioridades[tarefas[i].prior] = 1;
    }
    tarefas = novo_tarefas;
}

void ordenar_tempo()
{
    //decidir qual sort usar
}

void add(celula tarefas[], celula tarefa)
{
    scanf("%d", &tarefa.prior);
    scanf("%d:%d:%d", &tarefa.chegada.hh, &tarefa.chegada.mm, &tarefa.chegada.ss);
    scanf("%s", &tarefa.desc);

    tarefas[tarefa.prior] = tarefa;
}



void exec(celula tarefas[], char opcao)
{
    switch (opcao)
    {
        case 'p':
        {
            int prioridade_max = 0;
            for(int i = 0; i<=99; i++){
                if(prioridades[i] > prioridade_max){
                    prioridade_max = prioridades[i];
                }
            }
            tarefas[prioridade_max].desc[0] = '\0';
            tarefas[prioridade_max].prior = -1;
            tarefas[prioridade_max].chegada.hh = 0;
            tarefas[prioridade_max].chegada.mm = 0;
            tarefas[prioridade_max].chegada.ss = 0;
            
            prioridades[prioridade_max] = 0;

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

void next(celula tarefas[], char opcao)
{
    switch (opcao)
    {
        case 'p':
        {
            //inserir código para mostrar processo com maior prioridade aqui
            int prioridade_max = 0;
            for(int i = 0; i<=99; i++){
                if(prioridades[i] > prioridade_max){
                    prioridade_max = prioridades[i];
                }
            }
            do{
            if(tarefas[prioridade_max].desc != NULL){
                printf("%d %d:%d:%d %s", tarefas[prioridade_max].prior, tarefas[prioridade_max].chegada.hh, tarefas[prioridade_max].chegada.mm, tarefas[prioridade_max].chegada.ss, tarefas[prioridade_max].desc);
                printf("\n\n");
                prioridade_max = NULL;
            }else{
            prioridade_max--;
            }

            }while(prioridade_max != NULL || prioridade_max >= 0);
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

void alterar_prior(celula tarefas[], int anterior, int novo)
{
    //inserir código para mudar processo com prioridade aqui
    // ex: troca de anterior=88 para novo=22...
    tarefas[novo] = tarefas[anterior];
    tarefas[anterior].desc[0] = '\0';
    tarefas[novo].prior = novo;
}

void alterar_tempo(celula tarefas[], tempo anterior, tempo novo)
{
    int tempo_anterior = conversor_tempo(anterior);
    int tempo_novo = conversor_tempo(novo);
    //inserir código para mudar processo com tempo aqui
}

void print(celula tarefas[], char opcao)
{
    switch (opcao)
    {
        case 'p':
        {
            //inserir código para imprimir processos por prioridade aqui
            for(int i = 99; i >= 0; i--){
                if(tarefas[i].desc[0] != '\0'){
                    printf("%d %d:%d:%d %s", tarefas[i].prior, tarefas[i].chegada.hh, tarefas[i].chegada.mm, tarefas[i].chegada.ss, tarefas[i].desc);
                    printf("\n\n");
                }
            }
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
    celula tarefas[MAX_PRIOR]; // vetor principal de tarefas

    char* cmd;
    scanf("%s",cmd);

    
    do{
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
    }while(strcmp(cmd, "quit") != 0);


}


