#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "grafo_lista.h"

void criar_grafo_lista(GrafoLista *grafo_lista, int n) {
    grafo_lista->n = n;
    grafo_lista->adj = (No **)malloc(n * sizeof(No *));
    for (int i = 0; i < n; i++) {
        grafo_lista->adj[i] = NULL;
    }
}

void inserir_aresta_lista(GrafoLista *grafo_lista, int u, int v){
    No *novo_no = (No *)malloc(sizeof(No));
    novo_no->destino = v;
    novo_no->prox = grafo_lista->adj[u];
    grafo_lista->adj[u] = novo_no;

    // Para grafos não direcionados, insira a aresta no sentido oposto
    novo_no = (No *)malloc(sizeof(No));
    novo_no->destino = u;
    novo_no->prox = grafo_lista->adj[v];
    grafo_lista->adj[v] = novo_no;
}

void remover_aresta_lista(GrafoLista *grafo_lista, int u, int v){
    // Remover aresta (u, v)
    No *atual = grafo_lista->adj[u];
    No *anterior = NULL;

    while (atual != NULL) {
        if (atual->destino == v) {
            if (anterior == NULL) {
                grafo_lista->adj[u] = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }
            free(atual);
            break;
        }
        anterior = atual;
        atual = atual->prox;
    }

    // Remover aresta (v, u) para grafos não direcionados
    atual = grafo_lista->adj[v];
    anterior = NULL;

    while (atual != NULL) {
        if (atual->destino == u) {
            if (anterior == NULL) {
                grafo_lista->adj[v] = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }
            free(atual);
            break;
        }
        anterior = atual;
        atual = atual->prox;
    }
}

void grau_lista(GrafoLista *grafo_lista, int v){
    int grau = 0;
    No *atual = grafo_lista->adj[v];
    while (atual != NULL) {
        grau++;
        atual = atual->prox;
    }
    printf("Grau do vértice %d: %d\n", v, grau);
}

void sao_adjacentes_lista(GrafoLista *grafo_lista, int u, int v){
    No *atual = grafo_lista->adj[u];
    while (atual != NULL) {
        if (atual->destino == v) {
            printf("Os vértices %d e %d são adjacentes.\n", u, v);
            return;
        }
        atual = atual->prox;
    }
    printf("Os vértices %d e %d não são adjacentes.\n", u, v);
}

void liberar_grafo_lista(GrafoLista *grafo_lista){
    for (int i = 0; i < grafo_lista->n; i++) {
        No *atual = grafo_lista->adj[i];
        while (atual != NULL) {
            No *temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
    free(grafo_lista->adj);
}
