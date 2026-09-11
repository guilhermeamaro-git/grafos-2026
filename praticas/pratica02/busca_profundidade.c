#include <stdio.h>
#include <stdlib.h>
#include "busca_profundidade.h"

Pilha *criar_pilha(int capacidade) {
    Pilha *p = (Pilha *) malloc(sizeof(Pilha));
    p->dados = (int *) malloc(sizeof(int) * capacidade);
    p->capacidade = capacidade;
    p->topo = -1;
    return p;
}

int pilha_vazia(Pilha *p) {
    return p->topo == -1;
}

void empilhar(Pilha *p, int valor) {
    if (p->topo == p->capacidade - 1) {
        fprintf(stderr, "Erro: pilha cheia\n");
        exit(1);
    }
    p->topo++;
    p->dados[p->topo] = valor;
}

int desempilhar(Pilha *p) {
    if (pilha_vazia(p)) {
        fprintf(stderr, "Erro: pilha vazia\n");
        exit(1);
    }
    int valor = p->dados[p->topo];
    p->topo--;
    return valor;
}

void destruir_pilha(Pilha *p) {
    free(p->dados);
    free(p);
}

void dfs_recursiva(GrafoLista *g, int u, int *visitado, int *pred) {
    visitado[u] = 1;

    No *no = g->lista[u];
    while (no != NULL) {
        int v = no->vertice;
        if (!visitado[v]) {
            if (pred != NULL) pred[v] = u;
            dfs_recursiva(g, v, visitado, pred);
        }
        no = no->proximo;
    }
}

int contar_componentes(GrafoLista *g) {
    int n = g->num_vertices;
    int *visitado = (int *) calloc(n, sizeof(int));
    int componentes = 0;

    for (int i = 0; i < n; i++) {
        if (!visitado[i]) {
            componentes++;
            dfs_recursiva(g, i, visitado, NULL);
        }
    }

    free(visitado);
    return componentes;
}

int tem_ciclo(GrafoLista *g) {
    int n = g->num_vertices;
    int *visitado = (int *) calloc(n, sizeof(int));
    int ciclo = 0;

    for (int i = 0; i < n && !ciclo; i++) {
        if (visitado[i]) continue;

        // duas pilhas paralelas: uma guarda o vertice, outra guarda o pai
        // dele na arvore de busca (-1 para a raiz do componente)
        Pilha *pilha_v = criar_pilha(n);
        Pilha *pilha_pai = criar_pilha(n);

        visitado[i] = 1;
        empilhar(pilha_v, i);
        empilhar(pilha_pai, -1);

        while (!pilha_vazia(pilha_v) && !ciclo) {
            int u = desempilhar(pilha_v);
            int pai = desempilhar(pilha_pai);

            No *no = g->lista[u];
            while (no != NULL) {
                int v = no->vertice;
                if (!visitado[v]) {
                    visitado[v] = 1;
                    empilhar(pilha_v, v);
                    empilhar(pilha_pai, u);
                } else if (v != pai) {
                    // vizinho ja visitado que nao e o pai -> existe ciclo
                    ciclo = 1;
                    break;
                }
                no = no->proximo;
            }
        }

        destruir_pilha(pilha_v);
        destruir_pilha(pilha_pai);
    }

    free(visitado);
    return ciclo;
}