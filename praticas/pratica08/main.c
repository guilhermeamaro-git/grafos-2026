#include <stdio.h>
#include <stdlib.h>
#include "agm.h"

int main() {
    int V = 5;
    GrafoListaPonderado *g = criar_grafo(V);

    // Definindo as arestas do grafo de exemplo
    // Arestas estruturadas para Kruskal e Prim
    Aresta arestas[] = {
        {0, 1, 2},
        {0, 3, 6},
        {1, 2, 3},
        {1, 3, 8},
        {1, 4, 5},
        {2, 4, 7},
        {3, 4, 9}
    };
    int num_arestas = sizeof(arestas) / sizeof(arestas[0]);

    // Preenchendo o grafo ponderado
    for (int i = 0; i < num_arestas; i++) {
        adicionar_aresta(g, arestas[i].u, arestas[i].v, arestas[i].peso);
    }

    // Executa Kruskal
    kruskal(g, arestas, num_arestas);

    // Executa Prim
    prim(g, 0);

    liberar_grafo(g);
    return 0;
}