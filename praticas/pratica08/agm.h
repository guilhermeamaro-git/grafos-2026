#ifndef AGM_H
#define AGM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define INF INT_MAX

// =======================================================
// ESTRUTURAS DE DADOS
// =======================================================

// Estrutura para Disjoint Set Union (Union-Find)
typedef struct {
    int *pai;
    int *rank;
    int n;
} DSU;

// Estrutura para Aresta (utilizada em Kruskal)
typedef struct {
    int u, v, peso;
} Aresta;

// Estrutura para Lista de Adjacência (utilizada em Prim e no Grafo geral)
typedef struct ArestaAdj {
    int destino;
    int peso;
    struct ArestaAdj *proximo;
} ArestaAdj;

typedef struct {
    ArestaAdj **listas;
    int num_vertices;
} GrafoListaPonderado;

// Estrutura de Nó para o Min-Heap (utilizado em Prim)
typedef struct {
    int vertice;
    int chave;
} NoHeap;

typedef struct {
    NoHeap *dados;
    int capacidade;
    int tamanho;
    int *posicao; // Mapeia vértice -> índice no heap (para decrease_key em O(log V))
} MinHeap;

// =======================================================
// PROTÓTIPOS DAS FUNÇÕES
// =======================================================

// Funções do Grafo
GrafoListaPonderado* criar_grafo(int num_vertices);
void adicionar_aresta(GrafoListaPonderado *g, int u, int v, int peso);
void liberar_grafo(GrafoListaPonderado *g);

// Funções DSU (Union-Find)
DSU* criar_dsu(int n);
int find(DSU *d, int x);
bool unir(DSU *d, int x, int y);
void liberar_dsu(DSU *d);

// Funções do Min-Heap (para Prim)
MinHeap* criar_min_heap(int capacidade);
void inserir_min_heap(MinHeap *heap, int vertice, int chave);
NoHeap extrair_minimo(MinHeap *heap);
void diminuir_chave(MinHeap *heap, int vertice, int nova_chave);
bool esta_no_heap(MinHeap *heap, int vertice);
bool esta_vazio(MinHeap *heap);
void liberar_min_heap(MinHeap *heap);

// Algoritmos de Árvore Geradora Mínima (AGM)
void kruskal(GrafoListaPonderado *g, Aresta *arestas, int num_arestas);
void prim(GrafoListaPonderado *g, int origem);

#endif // AGM_H