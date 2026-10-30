#ifndef BELLMAN_FORD_H
#define BELLMAN_FORD_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define INF INT_MAX

// Estrutura de nó de adjacência (Grafo ponderado)
typedef struct Aresta {
    int destino;
    int peso;
    struct Aresta *proximo;
} Aresta;

typedef struct {
    Aresta **listas;
    int num_vertices;
} GrafoListaPonderado;

// Funções do Grafo
GrafoListaPonderado* criar_grafo(int num_vertices);
void adicionar_aresta(GrafoListaPonderado *g, int u, int v, int peso);
void liberar_grafo(GrafoListaPonderado *g);

// Algoritmo de Bellman-Ford e utilitários
int bellman_ford(GrafoListaPonderado *g, int origem, int *dist, int *pred, int *vertice_ciclo);
void reconstruir_caminho(int origem, int destino, int *pred);
void reconstruir_ciclo_negativo(int vertice_inicio, int *pred, int V);

#endif // BELLMAN_FORD_H