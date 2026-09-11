#ifndef BUSCA_LARGURA_H
#define BUSCA_LARGURA_H

#include "grafo_lista.h"

// Fila (FIFO) para BFS, implementada como buffer circular
typedef struct {
    int *dados;
    int capacidade, inicio, fim, tamanho;
} Fila;

Fila *criar_fila(int capacidade);
int fila_vazia(Fila *f);
void enfileirar(Fila *f, int valor);
int desenfileirar(Fila *f);
void destruir_fila(Fila *f);


void bfs(GrafoLista *g, int origem, int *dist, int *pred);


int eh_bipartido(GrafoLista *g);

#endif // BUSCA_LARGURA_H