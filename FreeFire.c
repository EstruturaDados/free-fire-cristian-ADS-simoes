#include <stdio.h>
#include <string.h>

#define MAX_ITENS 10

typedef struct {
    char nome[50];
    char tipo[30];
    int quantidade;
} Item;

int main() {
    Item mochila[MAX_ITENS];
    int totalItens = 0;
    int opcao;

    do {
        printf("\n--- 🎒 INVENTARIO FREE FIRE (NOVATO) ---");
        printf("\n1. Adicionar Item");
        printf("\n2. Remover Item (pelo nome)");
        printf("\n3. Listar Itens");
        printf("\n0. Sair");
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer

        if (opcao == 1) {
            if (totalItens < MAX_ITENS) {
                printf("Nome: ");
                fgets(mochila[totalItens].nome, 50, stdin);
                mochila[totalItens].nome[strcspn(mochila[totalItens].nome, "\n")] = 0;

                printf("Tipo: ");
                fgets(mochila[totalItens].tipo, 30, stdin);
                mochila[totalItens].tipo[strcspn(mochila[totalItens].tipo, "\n")] = 0;

                printf("Quantidade: ");
                scanf("%d", &mochila[totalItens].quantidade);
                totalItens++;
                printf("✅ Guardado!\n");
            } else {
                printf("❌ Mochila cheia!\n");
            }
        } 
        else if (opcao == 2) {
            char busca[50];
            printf("Nome para remover: ");
            fgets(busca, 50, stdin);
            busca[strcspn(busca, "\n")] = 0;

            for (int i = 0; i < totalItens; i++) {
                if (strcmp(mochila[i].nome, busca) == 0) {
                    for (int j = i; j < totalItens - 1; j++) {
                        mochila[j] = mochila[j + 1];
                    }
                    totalItens--;
                    printf("🗑️ Removido!\n");
                    break;
                }
            }
        }
        else if (opcao == 3) {
            printf("\n--- MOCHILA ATUAL ---\n");
            for (int i = 0; i < totalItens; i++) {
                printf("%d. %s [%s] | Qtd: %d\n", i+1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            }
            if (totalItens == 0) printf("Vazia.\n");
        }
    } while (opcao != 0);

    return 0;
}