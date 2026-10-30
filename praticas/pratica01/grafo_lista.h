#ifndef GRAFO_LISTA_H
#define GRAFO_LISTA_H

#define LIMITE 10

// Lista de adjacência
typedef struct No {
    int destino;
    struct No *prox;
} No;

typedef struct {
    int n;
    No **adj;
} GrafoLista;

void criar_grafo_lista(GrafoLista *grafo_lista, int n);
void inserir_aresta_lista(GrafoLista *grafo_lista, int u, int v);
void remover_aresta_lista(GrafoLista *grafo_lista, int u, int v);
void grau_lista(GrafoLista *grafo_lista, int v);
void sao_adjacentes_lista(GrafoLista *grafo_lista, int u, int v);
void liberar_grafo_lista(GrafoLista *grafo_lista);


#endif