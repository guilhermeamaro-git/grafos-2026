#ifndef DIJKSTRA_H
#define DIJKSTRA_H

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

// Estruturas do Min-Heap
typedef struct {
    int vertice;
    int distancia;
} NoHeap;

typedef struct {
    NoHeap *dados;
    int capacidade;
    int tamanho;
    int *posicao; // Mapeia vertice -> índice no heap (essencial para decrease_key)
} MinHeap;

// Funções do Grafo
GrafoListaPonderado* criar_grafo(int num_vertices);
void adicionar_aresta(GrafoListaPonderado *g, int u, int v, int peso);
void liberar_grafo(GrafoListaPonderado *g);

// Funções do Min-Heap
MinHeap* criar_min_heap(int capacidade);
void trocar_nos(MinHeap *heap, int i, int j);
void heapify_para_cima(MinHeap *heap, int idx);
void heapify_para_baixo(MinHeap *heap, int idx);
void inserir_min_heap(MinHeap *heap, int vertice, int distancia);
NoHeap extrair_minimo(MinHeap *heap);
void diminuir_chave(MinHeap *heap, int vertice, int nova_distancia);
bool esta_vazio(MinHeap *heap);
bool esta_no_heap(MinHeap *heap, int vertice);
void liberar_min_heap(MinHeap *heap);

// Algoritmo de Dijkstra e utilitários
void dijkstra(GrafoListaPonderado *g, int origem, int *dist, int *pred);
void reconstruir_caminho(int origem, int destino, int *pred);

#endif // DIJKSTRA_H