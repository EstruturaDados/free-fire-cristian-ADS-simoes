#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMP 20

// 1. Definição da Struct Componente
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// Variáveis globais para métricas
int comparacoes = 0;

// --- FUNÇÕES DE UTILIDADE ---

void mostrarComponentes(Componente vetor[], int n) {
    printf("\n%-20s | %-15s | %-10s\n", "NOME", "TIPO", "PRIORIDADE");
    printf("----------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%-20s | %-15s | %-10d\n", vetor[i].nome, vetor[i].tipo, vetor[i].prioridade);
    }
}

// --- ALGORITMOS DE ORDENAÇÃO ---

// Bubble Sort: Ordena por NOME (String)
void bubbleSortNome(Componente vetor[], int n) {
    comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparacoes++;
            if (strcmp(vetor[j].nome, vetor[j + 1].nome) > 0) {
                Componente temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
            }
        }
    }
}

// Insertion Sort: Ordena por TIPO (String)
void insertionSortTipo(Componente vetor[], int n) {
    comparacoes = 0;
    for (int i = 1; i < n; i++) {
        Componente chave = vetor[i];
        int j = i - 1;
        while (j >= 0 && strcmp(vetor[j].tipo, chave.tipo) > 0) {
            comparacoes++;
            vetor[j + 1] = vetor[j];
            j--;
        }
        vetor[j + 1] = chave;
        if (j >= 0) comparacoes++; // Conta a comparação que falhou no while
    }
}

// Selection Sort: Ordena por PRIORIDADE (Int)
void selectionSortPrioridade(Componente vetor[], int n) {
    comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            comparacoes++;
            if (vetor[j].prioridade < vetor[min_idx].prioridade)
                min_idx = j;
        }
        Componente temp = vetor[min_idx];
        vetor[min_idx] = vetor[i];
        vetor[i] = temp;
    }
}

// --- BUSCA E PERFORMANCE ---

void buscaBinariaPorNome(Componente vetor[], int n, char chave[]) {
    int esq = 0, dir = n - 1;
    int compBusca = 0;
    while (esq <= dir) {
        compBusca++;
        int meio = esq + (dir - esq) / 2;
        int res = strcmp(vetor[meio].nome, chave);
        if (res == 0) {
            printf("\n✅ Componente-chave '%s' localizado! Ativando torre...\n", chave);
            printf("Métrica: %d comparações na busca binária.\n", compBusca);
            return;
        }
        if (res < 0) esq = meio + 1;
        else dir = meio - 1;
    }
    printf("\n❌ Componente '%s' não encontrado. Fuga em risco!\n", chave);
}

// Função para medir tempo (usa ponteiro de função)
void medirExecucao(void (*algoritmo)(Componente[], int), Componente vetor[], int n, char* msg) {
    clock_t t;
    t = clock();
    algoritmo(vetor, n);
    t = clock() - t;
    double tempo_ms = ((double)t) / CLOCKS_PER_SEC * 1000;
    
    printf("\n>>> %s <<<\n", msg);
    printf("Tempo: %.4f ms | Comparações: %d\n", tempo_ms, comparacoes);
    mostrarComponentes(vetor, n);
}

// --- MAIN ---

int main() {
    Componente torre[MAX_COMP];
    int total = 0, opcao;
    char busca[30];

    do {
        printf("\n=== 🚀 SISTEMA DE FUGA: TORRE DE RESGATE ===");
        printf("\n1. Cadastrar Componente\n2. Ordenar por Nome (Bubble)\n3. Ordenar por Tipo (Insertion)");
        printf("\n4. Ordenar por Prioridade (Selection)\n5. Buscar Componente-Chave (Binária)\n0. Sair\nEscolha: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                if (total < MAX_COMP) {
                    printf("Nome: "); fgets(torre[total].nome, 30, stdin);
                    torre[total].nome[strcspn(torre[total].nome, "\n")] = 0;
                    printf("Tipo: "); fgets(torre[total].tipo, 20, stdin);
                    torre[total].tipo[strcspn(torre[total].tipo, "\n")] = 0;
                    printf("Prioridade (1-10): "); scanf("%d", &torre[total].prioridade);
                    total++;
                } else printf("Limite atingido!\n");
                break;
            case 2:
                medirExecucao(bubbleSortNome, torre, total, "ORDENAÇÃO POR NOME (BUBBLE)");
                break;
            case 3:
                medirExecucao(insertionSortTipo, torre, total, "ORDENAÇÃO POR TIPO (INSERTION)");
                break;
            case 4:
                medirExecucao(selectionSortPrioridade, torre, total, "ORDENAÇÃO POR PRIORIDADE (SELECTION)");
                break;
            case 5:
                printf("Digite o nome do componente-chave: ");
                fgets(busca, 30, stdin);
                busca[strcspn(busca, "\n")] = 0;
                // A busca binária exige que esteja ordenado por nome primeiro!
                bubbleSortNome(torre, total); 
                buscaBinariaPorNome(torre, total, busca);
                break;
        }
    } while (opcao != 0);

    return 0;
}