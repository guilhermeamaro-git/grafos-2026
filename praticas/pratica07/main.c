#include <stdio.h>
#include <stdlib.h>
#include "bellman_ford.h"

void testar_grafo_sem_ciclo_negativo() {
    printf("=== TESTE 1: Grafo com Arestas Negativas (Sem Ciclo Negativo) ===\n");
    int V = 5;
    GrafoListaPonderado *g = criar_grafo(V);

    adicionar_aresta(g, 0, 1, -1);
    adicionar_aresta(g, 0, 2, 4);
    adicionar_aresta(g, 1, 2, 3);
    adicionar_aresta(g, 1, 3, 2);
    adicionar_aresta(g, 1, 4, 2);
    adicionar_aresta(g, 3, 2, 5);
    adicionar_aresta(g, 3, 1, 1);
    adicionar_aresta(g, 4, 3, -3);

    int origem = 0;
    int dist[V];
    int pred[V];
    int vertice_ciclo;

    int status = bellman_ford(g, origem, dist, pred, &vertice_ciclo);

    if (status == 1) {
        printf("✅ Nenhum ciclo de custo negativo foi encontrado.\n");
        for (int i = 0; i < V; i++) {
            printf("Vértice %d: Distância = %d | Caminho: ", i, dist[i]);
            reconstruir_caminho(origem, i, pred);
            printf("\n");
        }
    } else {
        printf("❌ Ciclo negativo detectado inesperadamente!\n");
    }

    liberar_grafo(g);
    printf("\n");
}

void testar_grafo_com_ciclo_negativo() {
    printf("=== TESTE 2: Grafo com Ciclo Negativo ===\n");
    int V = 4;
    GrafoListaPonderado *g = criar_grafo(V);

    adicionar_aresta(g, 0, 1, 1);
    adicionar_aresta(g, 1, 2, -2);
    adicionar_aresta(g, 2, 3, -1);
    adicionar_aresta(g, 3, 1, -1); // Ciclo: 1 -> 2 -> 3 -> 1 com custo (-2 -1 -1) = -4

    int origem = 0;
    int dist[V];
    int pred[V];
    int vertice_ciclo;

    int status = bellman_ford(g, origem, dist, pred, &vertice_ciclo);

    if (status == 0) {
        printf("⚠️ Ciclo de custo negativo detectado com sucesso!\n");
        reconstruir_ciclo_negativo(vertice_ciclo, pred, V);
    } else {
        printf("❌ O algoritmo não detectou o ciclo negativo!\n");
    }

    liberar_grafo(g);
    printf("\n");
}

int main() {
    testar_grafo_sem_ciclo_negativo();
    testar_grafo_com_ciclo_negativo();
    return 0;
}