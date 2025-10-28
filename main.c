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

int qtd; //quantidade atual de tarefas
int prioridades[MAX_PRIOR] = {0}; //vetor de marcação de quais prioridades estão sendo utilizadas
int flag = 1; // 1 - a lista está ordenada por prioridade (com hashing); 0 - a lista está ordenada por tempo


int conversor_tempo(tempo t)
{
    return t.hh*3600 + t.mm*60 + t.ss;
}

// Função de Busca Binária para encontrar uma tarefa pelo tempo (convertido)
// Retorna o índice se encontrar, ou -1 se não encontrar
int binary_search_tempo(celula tarefas[], long long tempo_segundos, int ini, int fim)
{
    if (fim < ini) {
        return -1; // Não encontrado
    }
    
    int meio = ini + (fim - ini) / 2;
    long long tempo_meio = conversor_tempo(tarefas[meio].chegada);

    if (tempo_meio == tempo_segundos) {
        return meio; // Encontrado
    }
    
    if (tempo_meio > tempo_segundos) {
        return binary_search_tempo(tarefas, tempo_segundos, ini, meio - 1); // Busca na metade esquerda
    }
    
    return binary_search_tempo(tarefas, tempo_segundos, meio + 1, fim); // Busca na metade direita
}


void hash_prior(celula tarefas[]) //hashing
{
    if (flag) return;
    celula novo_tarefas[MAX_PRIOR] = {0};

    //copiar a tarefa para o índice correspondente à sua prioridade
    // ***** CORREÇÃO: Loop deve ir até 'qtd', não 'MAX_PRIOR' *****
    for (int i = 0; i < qtd; i++) {
        if (tarefas[i].prior > 0 && tarefas[i].prior < MAX_PRIOR)
            novo_tarefas[tarefas[i].prior] = tarefas[i];
    }
    //copiar o vetor novo para o antigo
    for (int i = 0; i < MAX_PRIOR; i++) {
        tarefas[i] = novo_tarefas[i];
    }

    flag = 1;
    return;
}

void compactar(celula tarefas[])
{
    qtd = 0;
    for (int i = 0; i < MAX_PRIOR; i++) {
        if (prioridades[i])
            tarefas[qtd++] = tarefas[i];
    }
    return;
}

void particao(celula vet[], int esq, int dir, int *i, int *j)
{
    *i = esq; *j = dir;
    celula pivo = vet[(*i + *j) / 2];
    celula aux;
    do {
        while (conversor_tempo(vet[*i].chegada) < conversor_tempo(pivo.chegada)) (*i)++;
        while (conversor_tempo(vet[*j].chegada) > conversor_tempo(pivo.chegada)) (*j)--;
        // ***** CORREÇÃO: Deve ser <= e incrementar/decrementar i/j *****
        if (*i <= *j) {
            aux = vet[*i];
            vet[*i] = vet[*j];
            vet[*j] = aux;
            (*i)++;
            (*j)--;
        }
    } while (*i <= *j);     // ***** CORREÇÃO: Condição deve ser <= *****
}
}

void quicksort(celula compactado[], int ini, int fim) //quicksort precisa receber tarefas COMPACTADAS
{
    if (ini >= fim) return; // Condição de parada
    int i, j;
    particao(compactado, ini, fim, &i, &j);
    if (ini < j)
        quicksort(compactado, ini, j);
    if (i < fim)
        quicksort(compactado, i, fim);

    return;
}

void ordenar_tempo(celula tarefas[])
{
    if (!flag) return;
    
    compactar(tarefas);
    quicksort(tarefas, 0, qtd-1);

    flag = 0;
    return;
}

void add(celula tarefas[])
{
    if (qtd >= 99) {printf("Limite de tarefas atingido!\n"); return;}
    celula tarefa;
    do {
        scanf("%d", &tarefa.prior);
        if (prioridades[tarefa.prior])
            printf("Essa prioridade já está sendo usada! As pioridades das tarefas devem ser únicas.\nPor favor, insira outro índice de prioridade: ");
        else {
            prioridades[tarefa.prior] = 1;
            break;
        }
    } while (prioridades[tarefa.prior]);
    scanf("%d:%d:%d", &tarefa.chegada.hh, &tarefa.chegada.mm, &tarefa.chegada.ss);
    scanf("%s", tarefa.desc);

    if (flag) //se está ordenada por prioridade
        tarefas[tarefa.prior] = tarefa;
    else //se está ordenada por tempo
        tarefas[qtd] = tarefa;
        flag = 1; // A ordenação por tempo agora é inválida!
    qtd++;
    return;
}

void exec(celula tarefas[], char opcao)
{
    if (qtd == 0) return; //não há tarefas para executar
    switch (opcao)
    {
        case 'p':
        {
            hash_prior(tarefas);
            //achar o valor de maior prioridade
            int prioridade_max = 99;
            while (!prioridades[prioridade_max]) prioridade_max--;

            prioridades[prioridade_max] = 0; //torna a tarefa invisível
            // limpa a célula
            tarefas[prioridade_max].desc[0] = '\0'; 
            tarefas[prioridade_max].prior = 0;
            qtd--;
            break;
        }

        case 't':
        {
            // Garante que estamos no modo tempo
            ordenar_tempo(tarefas); 
            
            // A tarefa com menor tempo está no índice 0
            if (qtd == 0) return; // Checagem extra caso compactar/ordenar esvazie
            
            int prioridade_removida = tarefas[0].prior;
            prioridades[prioridade_removida] = 0; // Libera a prioridade

            // Move todos os elementos uma posição para a esquerda
            for (int i = 0; i < qtd - 1; i++) {
                tarefas[i] = tarefas[i+1];
            }

            // Limpa a última posição
            tarefas[qtd-1].prior = 0;
            tarefas[qtd-1].desc[0] = '\0';
            
            qtd--; // Reduz a contagem
            break;
        }

        default: { printf(
            "Por favor, escolha uma opção válida!\n"
            "-p: executar processo com maior prioridade\n"
            "-t: executar processo com menor tempo\n"
        ); return; }
    }
    return;
}

void next(celula tarefas[], char opcao)
{
    switch (opcao)
    {
        case 'p':
        {
            //mostrar processo com maior prioridade aqui
            int prioridade_max = 99;
            while (!prioridades[prioridade_max]) prioridade_max--;
            if (prioridade_max > 0) {
                hash_prior(tarefas);
                printf("%02d %02d:%02d:%02d %s\n\n", tarefas[prioridade_max].prior, tarefas[prioridade_max].chegada.hh, tarefas[prioridade_max].chegada.mm, tarefas[prioridade_max].chegada.ss, tarefas[prioridade_max].desc);
            }
            break;
        }

        case 't':
        {
            ordenar_tempo(tarefas);
            if (qtd > 0) {
                printf("%02d %02d:%02d:%02d %s\n\n", tarefas[0].prior, tarefas[0].chegada.hh, tarefas[0].chegada.mm, tarefas[0].chegada.ss, tarefas[0].desc);
            }
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
    hash_prior(tarefas); //garantir que está ordenado por prioridade
    tarefas[novo] = tarefas[anterior];
    tarefas[anterior].desc[0] = '\0'; //limpa a célula
    tarefas[anterior].prior = 0;
    tarefas[novo].prior = novo;

    prioridades[anterior] = 0;
    prioridades[novo] = 1;
}

void alterar_tempo(celula tarefas[], tempo anterior, tempo novo)
{
    // 1. Garantir que a lista está ordenada por tempo para a busca binária
    ordenar_tempo(tarefas);

    // 2. Converter o tempo 'anterior' para segundos para buscar
    long long tempo_antigo_seg = conversor_tempo(anterior);

    // 3. Usar busca binária para encontrar o índice da tarefa
    int indice = binary_search_tempo(tarefas, tempo_antigo_seg, 0, qtd - 1);

    if (indice != -1) {
        // 4. Encontrou a tarefa, agora atualiza o tempo
        tarefas[indice].chegada = novo;

        // 5. A alteração pode ter quebrado a ordenação.
        // Forçamos a re-ordenar na proxima chamada de tempo.
        flag = 1; // Invalida a ordenação por tempo (seta para modo prioridade)
                 // A proxima chamada a ordenar_tempo() vai refazer o quicksort.
    } else {
        // printf("Erro: Tarefa com tempo %02d:%02d:%02d não encontrada.\n", anterior.hh, anterior.mm, anterior.ss);
    }
}

void print(celula tarefas[], char opcao)
{
    switch (opcao)
    {
        case 'p':
        {
            //inserir código para imprimir processos por prioridade aqui
            hash_prior(tarefas);
            for(int i = 99; i >= 1; i--){
                if(prioridades[i])
                    printf("%02d %02d:%02d:%02d %s\n", tarefas[i].prior, tarefas[i].chegada.hh, tarefas[i].chegada.mm, tarefas[i].chegada.ss, tarefas[i].desc);
                printf("\n");
            }
            break;
        }

        case 't':
        {
            ordenar_tempo(tarefas);
            for(int i = 0; i < qtd; i++){
                printf("%02d %02d:%02d:%02d %s\n", tarefas[i].prior, tarefas[i].chegada.hh, tarefas[i].chegada.mm, tarefas[i].chegada.ss, tarefas[i].desc);
            }
            printf("\n"); [cite_start]// Linha em branco no final, como pedido [cite: 56]
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
    celula tarefas[MAX_PRIOR] = {}; // vetor principal de tarefas
    qtd = 0;
    
    char cmd[20];
    do{
        scanf("%s",cmd);
        //adiciona um processo(celula) a lista de processos
        if(strcmp(cmd,"add") == 0)
        {
            add(tarefas);
        }

        /*executa um processo
        -p executa o processo com maior prioridade
        -t executa o processo com menor tempo
        */
        if(strcmp(cmd,"exec") == 0)
        {
            char opc;
            scanf(" -%c", &opc);
            exec(tarefas, opc);
        }

        /*  mostra um processo
        -p mostra em uma linha todas as informacoes do processo com maior prioridade
        -t  mostra em uma linha todas as informacoes do processo com menor tempo
        */
        if(strcmp(cmd,"next") == 0)
        {
            char opc;
            scanf(" -%c", &opc);
            next(tarefas, opc);
        }
        
        /*  modifica informacoes de um processo
        -p anterior:novo altera o campo prior com valor anterior para o valor novo
        -t anterior:novo altera o campo tempo com o valor anterior para o valor novo
        */
        if(strcmp(cmd,"change") == 0)
        {
            char opc;
            scanf(" -%c", &opc);

            switch (opc)
            {
                case 'p': 
                {
                    int anterior, novo;
                    scanf(" %d|%d", &anterior, &novo);
                    alterar_prior(tarefas, anterior, novo);
                    break;
                }
               case 't':
                  {
                      tempo anterior, novo;
                      // Formato de leitura: hh:mm:ss|hh:mm:ss
                      scanf(" %d:%d:%d|%d:%d:%d", 
                            &anterior.hh, &anterior.mm, &anterior.ss,
                            &novo.hh, &novo.mm, &novo.ss);
                      alterar_tempo(tarefas, anterior, novo);
                      break;
                  }
                default: printf(
                "Por favor, escolha uma opção válida!\n"
                "-p: imprimir os processor em ordem decrescente de prioridade\n"
                "-t: imprimir os processor em ordem crescente de horários\n"
                );
            }
        }

        /*  imprime todos os processos a serem executados 
        -p imprime todos os processos em ordem decrescente de prioridade prioridade, onde as informacoes de cada
        processo sao impressas em uma unica linha (prior, tempo e descricao).

        -t: imprime os processos em ordem crescente de horarios, onde as informacoes de cada 
        processo sao impressas em uma unica linha (prior, tempo e descricao)
        */
        if(strcmp(cmd,"print") == 0)
        {
            char opc;
            scanf(" -%c", &opc);
            print(tarefas, opc);
        }
    } while(strcmp(cmd, "quit") != 0);

    return 0;
}
