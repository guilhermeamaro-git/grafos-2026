#include <stdio.h>
#include <stdlib.h>
#include "dijkstra.h"

int main() {
    int num_vertices = 6;
    GrafoListaPonderado *g = criar_grafo(num_vertices);

    // Grafo de exemplo (direcionado e ponderado com pesos não-negativos)
    adicionar_aresta(g, 0, 1, 4);
    adicionar_aresta(g, 0, 2, 2);
    adicionar_aresta(g, 1, 2, 1);
    adicionar_aresta(g, 1, 3, 5);
    adicionar_aresta(g, 2, 3, 8);
    adicionar_aresta(g, 2, 4, 10);
    adicionar_aresta(g, 3, 4, 2);
    adicionar_aresta(g, 3, 5, 6);
    adicionar_aresta(g, 4, 5, 3);

    int origem = 0;
    int dist[num_vertices];
    int pred[num_vertices];

    printf("=== Executando Algoritmo de Dijkstra (Origem: %d) ===\n\n", origem);
    dijkstra(g, origem, dist, pred);

    for (int i = 0; i < num_vertices; i++) {
        if (dist[i] == INF) {
            printf("Vertice %d: Inalcancavel\n", i);
        } else {
            printf("Vertice %d: Distancia Minima = %d | ", i, dist[i]);
            reconstruir_caminho(origem, i, pred);
        }
    }

    liberar_grafo(g);
    return 0;
}