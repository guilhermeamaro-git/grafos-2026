#include <stdio.h>
#include <stdlib.h>
#include "busca_largura.h"

Fila *criar_fila(int capacidade) {
    Fila *f = (Fila *) malloc(sizeof(Fila));
    f->dados = (int *) malloc(sizeof(int) * capacidade);
    f->capacidade = capacidade;
    f->inicio = 0;
    f->fim = 0;
    f->tamanho = 0;
    return f;
}

int fila_vazia(Fila *f) {
    return f->tamanho == 0;
}

void enfileirar(Fila *f, int valor) {
    if (f->tamanho == f->capacidade) {
        fprintf(stderr, "Erro: fila cheia\n");
        exit(1);
    }
    f->dados[f->fim] = valor;
    f->fim = (f->fim + 1) % f->capacidade;
    f->tamanho++;
}

int desenfileirar(Fila *f) {
    if (fila_vazia(f)) {
        fprintf(stderr, "Erro: fila vazia\n");
        exit(1);
    }
    int valor = f->dados[f->inicio];
    f->inicio = (f->inicio + 1) % f->capacidade;
    f->tamanho--;
    return valor;
}

void destruir_fila(Fila *f) {
    free(f->dados);
    free(f);
}

void bfs(GrafoLista *g, int origem, int *dist, int *pred) {
    int n = g->num_vertices;

    for (int i = 0; i < n; i++) {
        dist[i] = -1;
        pred[i] = -1;
    }

    // capacidade n e suficiente: cada vertice entra na fila no maximo 1 vez
    Fila *f = criar_fila(n);

    dist[origem] = 0;
    enfileirar(f, origem);

    while (!fila_vazia(f)) {
        int u = desenfileirar(f);

        No *no = g->lista[u];
        while (no != NULL) {
            int v = no->vertice;
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                pred[v] = u;
                enfileirar(f, v);
            }
            no = no->proximo;
        }
    }

    destruir_fila(f);
}

int eh_bipartido(GrafoLista *g) {
    int n = g->num_vertices;
    int *cor = (int *) malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) cor[i] = -1;

    int bipartido = 1;

    // percorre todos os componentes, ja que o grafo pode ser desconexo
    for (int s = 0; s < n && bipartido; s++) {
        if (cor[s] != -1) continue;

        cor[s] = 0;
        Fila *f = criar_fila(n);
        enfileirar(f, s);

        while (!fila_vazia(f) && bipartido) {
            int u = desenfileirar(f);

            No *no = g->lista[u];
            while (no != NULL) {
                int v = no->vertice;
                if (cor[v] == -1) {
                    cor[v] = 1 - cor[u];
                    enfileirar(f, v);
                } else if (cor[v] == cor[u]) {
                    bipartido = 0;
                    break;
                }
                no = no->proximo;
            }
        }

        destruir_fila(f);
    }

    free(cor);
    return bipartido;
}

