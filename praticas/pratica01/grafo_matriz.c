#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "grafo_matriz.h"

void criar_grafo_matriz(GrafoMatriz *grafo, int n) {
    grafo->num_vertices = n;
    grafo->adjacencia = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        grafo->adjacencia[i] = (int *)malloc(n * sizeof(int));
        memset(grafo->adjacencia[i], 0, n * sizeof(int));
    }
}

void inserir_aresta_matriz(GrafoMatriz *grafo, int u, int v){
    grafo->adjacencia[u][v] = 1;
    grafo->adjacencia[v][u] = 1; // Para grafos não direcionados
}

void remover_aresta_matriz(GrafoMatriz *grafo, int u, int v){
    grafo->adjacencia[u][v] = 0;
    grafo->adjacencia[v][u] = 0; // Para grafos não direcionados
}

void grau_matriz(GrafoMatriz *grafo, int v){
    int grau = 0;
    for (int i = 0; i < grafo->num_vertices; i++) {
        if (grafo->adjacencia[v][i] == 1) {
            grau++;
        }
    }
    printf("Grau do vértice %d: %d\n", v, grau);
}

void sao_adjacentes_matriz(GrafoMatriz *grafo, int u, int v){
    if (grafo->adjacencia[u][v] == 1) {
        printf("Os vértices %d e %d são adjacentes.\n", u, v);
    } else {
        printf("Os vértices %d e %d não são adjacentes.\n", u, v);
    }
}

void liberar_grafo_matriz(GrafoMatriz *grafo) {
    for (int i = 0; i < grafo->num_vertices; i++) {
        free(grafo->adjacencia[i]);
    }
    free(grafo->adjacencia);
}





