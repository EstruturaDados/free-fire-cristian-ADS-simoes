#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// 1. Definição das Structs
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// Variáveis Globais para o Vetor e Contadores
Item vetorMochila[100];
int totalVetor = 0;
int comparacoesBusca = 0;

// --- FUNÇÕES DA LISTA ENCADEADA ---

No* inserirLista(No* inicio) {
    No* novo = (No*)malloc(sizeof(No));
    printf("Nome do item: ");
    fgets(novo->dados.nome, 30, stdin);
    novo->dados.nome[strcspn(novo->dados.nome, "\n")] = 0;
    
    printf("Tipo: ");
    fgets(novo->dados.tipo, 20, stdin);
    novo->dados.tipo[strcspn(novo->dados.tipo, "\n")] = 0;
    
    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);
    getchar();

    novo->proximo = inicio;
    printf("✅ Item adicionado na Lista Encadeada!\n");
    return novo;
}

void listarLista(No* inicio) {
    printf("\n--- 🎒 MOCHILA (LISTA ENCADEADA) ---\n");
    No* atual = inicio;
    while (atual != NULL) {
        printf("Item: %-15s | Tipo: %-10s | Qtd: %d\n", atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
        atual = atual->proximo;
    }
}

void buscarSequencialLista(No* inicio, char* nome) {
    comparacoesBusca = 0;
    No* atual = inicio;
    while (atual != NULL) {
        comparacoesBusca++;
        if (strcmp(atual->dados.nome, nome) == 0) {
            printf("🔍 Item encontrado na Lista! Comparações: %d\n", comparacoesBusca);
            return;
        }
        atual = atual->proximo;
    }
    printf("❌ Item não encontrado na Lista. Comparações: %d\n", comparacoesBusca);
}

// --- FUNÇÕES DO VETOR ---

void inserirVetor() {
    if (totalVetor >= 100) {
        printf("Mochila cheia!\n");
        return;
    }
    printf("Nome do item: ");
    fgets(vetorMochila[totalVetor].nome, 30, stdin);
    vetorMochila[totalVetor].nome[strcspn(vetorMochila[totalVetor].nome, "\n")] = 0;
    
    printf("Tipo: ");
    fgets(vetorMochila[totalVetor].tipo, 20, stdin);
    vetorMochila[totalVetor].tipo[strcspn(vetorMochila[totalVetor].tipo, "\n")] = 0;
    
    printf("Quantidade: ");
    scanf("%d", &vetorMochila[totalVetor].quantidade);
    getchar();
    
    totalVetor++;
    printf("✅ Item adicionado no Vetor!\n");
}

void ordenarVetor() {
    // Bubble Sort
    for (int i = 0; i < totalVetor - 1; i++) {
        for (int j = 0; j < totalVetor - i - 1; j++) {
            if (strcmp(vetorMochila[j].nome, vetorMochila[j + 1].nome) > 0) {
                Item temp = vetorMochila[j];
                vetorMochila[j] = vetorMochila[j + 1];
                vetorMochila[j + 1] = temp;
            }
        }
    }
    printf("🗂️ Vetor ordenado por nome com sucesso!\n");
}

void buscaBinariaVetor(char* nome) {
    comparacoesBusca = 0;
    int inicio = 0, fim = totalVetor - 1;
    while (inicio <= fim) {
        comparacoesBusca++;
        int meio = (inicio + fim) / 2;
        int res = strcmp(vetorMochila[meio].nome, nome);
        if (res == 0) {
            printf("⚡ Busca Binária: Item encontrado! Comparações: %d\n", comparacoesBusca);
            return;
        } else if (res < 0) inicio = meio + 1;
        else fim = meio - 1;
    }
    printf("❌ Busca Binária: Não encontrado. Comparações: %d\n", comparacoesBusca);
}

int main() {
    No* minhaLista = NULL;
    int opcao, estrutura;
    char buscaNome[30];

    do {
        printf("\n==================================\n");
        printf("   DESAFIO ILHA: AVENTUREIRO\n");
        printf("==================================\n");
        printf("1. Gerenciar Vetor (Sequencial)\n");
        printf("2. Gerenciar Lista (Dinâmica)\n");
        printf("3. Comparar Buscas (Sequencial x Binária)\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                printf("\n1. Inserir | 2. Listar | 3. Ordenar: ");
                scanf("%d", &estrutura); getchar();
                if (estrutura == 1) inserirVetor();
                else if (estrutura == 2) {
                    for(int i=0; i<totalVetor; i++) printf("%s\n", vetorMochila[i].nome);
                }
                else if (estrutura == 3) ordenarVetor();
                break;

            case 2:
                printf("\n1. Inserir | 2. Listar: ");
                scanf("%d", &estrutura); getchar();
                if (estrutura == 1) minhaLista = inserirLista(minhaLista);
                else if (estrutura == 2) listarLista(minhaLista);
                break;

            case 3:
                printf("Digite o nome para buscar: ");
                fgets(buscaNome, 30, stdin);
                buscaNome[strcspn(buscaNome, "\n")] = 0;
                
                printf("\n--- RESULTADO DA COMPETIÇÃO ---\n");
                buscarSequencialLista(minhaLista, buscaNome);
                buscaBinariaVetor(buscaNome);
                break;
        }
    } while (opcao != 0);

    return 0;
}