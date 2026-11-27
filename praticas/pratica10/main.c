
#include <stdio.h>
#include <time.h>

#include "hamiltoniano.h"
#include "tps.h"

void imprimir_caminho(int caminho[], int tamanho) {

    for (int i = 0; i < tamanho; i++) {
        printf("%d", caminho[i]);

        if (i < tamanho - 1) {
            printf(" -> ");
        }
    }

    printf("\n");
}

int main() {

    int tamanhos[] = {5, 8, 10, 12};
    int quantidade = 4;

    for (int k = 0; k < quantidade; k++) {

        int n = tamanhos[k];

        int grafo[MAX_VERTICES][MAX_VERTICES] = {0};
        int custos[MAX_VERTICES][MAX_VERTICES];

        int caminho[MAX_VERTICES];
        int ciclo[MAX_VERTICES + 1];

        int melhor_caminho[MAX_VERTICES + 1];

        int custo_bruta;
        int custo_vizinho;
        int custo_insercao;

        clock_t inicio, fim;

        printf("\n====================================\n");
        printf("       EXPERIMENTO COM N = %d\n", n);
        printf("====================================\n");

        /* Criacao do grafo de teste */

        for (int i = 0; i < n; i++) {

            for (int j = 0; j < n; j++) {

                if (i != j && (i + j) % 3 != 0) {
                    grafo[i][j] = 1;
                }
            }
        }

        /* Caminho Hamiltoniano */

        inicio = clock();

        int encontrou_caminho =
            encontrar_caminho_hamiltoniano_bt(
                grafo, n, caminho
            );

        fim = clock();

        printf("\nCaminho Hamiltoniano:\n");

        if (encontrou_caminho) {
            imprimir_caminho(caminho, n);
        } else {
            printf("Nao existe caminho Hamiltoniano.\n");
        }

        printf("Tempo: %.6f segundos\n",
            (double)(fim - inicio) / CLOCKS_PER_SEC
        );

        /* Ciclo Hamiltoniano */

        inicio = clock();

        int encontrou_ciclo =
            encontrar_ciclo_hamiltoniano_bt(
                grafo, n, ciclo
            );

        fim = clock();

        printf("\nCiclo Hamiltoniano:\n");

        if (encontrou_ciclo) {
            imprimir_caminho(ciclo, n + 1);
        } else {
            printf("Nao existe ciclo Hamiltoniano.\n");
        }

        printf("Tempo: %.6f segundos\n",
            (double)(fim - inicio) / CLOCKS_PER_SEC
        );

        /* Conversao do grafo para TSP */

        grafo_para_tsp(grafo, custos, n);

        /* TSP por forca bruta */

        inicio = clock();

        tsp_forca_bruta(
            custos,
            n,
            melhor_caminho,
            &custo_bruta
        );

        fim = clock();

        printf("\nTSP - Forca Bruta:\n");

        imprimir_caminho(melhor_caminho, n + 1);

        printf("Custo: %d\n", custo_bruta);

        printf("Tempo: %.6f segundos\n",
            (double)(fim - inicio) / CLOCKS_PER_SEC
        );

        /* TSP - Vizinho Mais Proximo */

        inicio = clock();

        tsp_vizinho_mais_proximo(
            custos,
            n,
            melhor_caminho,
            &custo_vizinho
        );

        fim = clock();

        printf("\nTSP - Vizinho Mais Proximo:\n");

        imprimir_caminho(melhor_caminho, n + 1);

        printf("Custo: %d\n", custo_vizinho);

        printf("Tempo: %.6f segundos\n",
            (double)(fim - inicio) / CLOCKS_PER_SEC
        );

        /* TSP - Insercao */

        inicio = clock();

        tsp_insercao(
            custos,
            n,
            melhor_caminho,
            &custo_insercao
        );

        fim = clock();

        printf("\nTSP - Insercao:\n");

        imprimir_caminho(melhor_caminho, n + 1);

        printf("Custo: %d\n", custo_insercao);

        printf("Tempo: %.6f segundos\n",
            (double)(fim - inicio) / CLOCKS_PER_SEC
        );
    }

    return 0;
}
