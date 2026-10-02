#ifndef GRAFO_MATRIZ_H
#define GRAFO_MATRIZ_H

#define LIMITE 10

// Matriz de adjacência
typedef struct {
    int num_vertices;
    int **adjacencia;
} GrafoMatriz;


void criar_grafo_matriz(GrafoMatriz *grafo, int n);
void inserir_aresta_matriz(GrafoMatriz *grafo, int u, int v);
void remover_aresta_matriz(GrafoMatriz *grafo, int u, int v);
void grau_matriz(GrafoMatriz *grafo, int v);
void sao_adjacentes_matriz(GrafoMatriz *grafo, int u, int v);
void liberar_grafo_matriz(GrafoMatriz *grafo);


#endif