#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cobertura.h"

int main() {
    // Inicializa a semente aleatória
    srand(42);

    printf("========================================================================================\n");
    printf("                     EXPERIMENTO: COBERTURA DE VÉRTICES (NP-COMPLETO)                   \n");
    printf("========================================================================================\n");
    printf("|  N | Arestas | Tam BT (Exato) | Tempo BT (s)  | Tam Gulosa | Tempo Guloso (s) |\n");
    printf("----------------------------------------------------------------------------------------\n");

    int tamanhos[] = {5, 8, 10, 12, 15};
    int num_testes = sizeof(tamanhos) / sizeof(tamanhos[0]);
    double densidade_aresta = 0.5; // Probabilidade de 50% de existência de aresta

    for (int i = 0; i < num_testes; i++) {
        executar_experimento(tamanhos[i], densidade_aresta);
    }

    printf("========================================================================================\n");

    return 0;
}