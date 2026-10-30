#include "bellman_ford.h"

// =======================================================
// GERENCIAMENTO DO GRAFO
// =======================================================

GrafoListaPonderado* criar_grafo(int num_vertices) {
    GrafoListaPonderado *g = (GrafoListaPonderado*) malloc(sizeof(GrafoListaPonderado));
    g->num_vertices = num_vertices;
    g->listas = (Aresta**) malloc(num_vertices * sizeof(Aresta*));
    for (int i = 0; i < num_vertices; i++) {
        g->listas[i] = NULL;
    }
    return g;
}

void adicionar_aresta(GrafoListaPonderado *g, int u, int v, int peso) {
    Aresta *nova = (Aresta*) malloc(sizeof(Aresta));
    nova->destino = v;
    nova->peso = peso;
    nova->proximo = g->listas[u];
    g->listas[u] = nova;
}

void liberar_grafo(GrafoListaPonderado *g) {
    if (!g) return;
    for (int i = 0; i < g->num_vertices; i++) {
        Aresta *atual = g->listas[i];
        while (atual != NULL) {
            Aresta *temp = atual;
            atual = atual->proximo;
            free(temp);
        }
    }
    free(g->listas);
    free(g);
}

// =======================================================
// ALGORITMO DE BELLMAN-FORD
// =======================================================

/**
 * Retorna 1 se não houver ciclos de custo negativo atingíveis.
 * Retorna 0 se um ciclo negativo for detectado (armazenando um vértice do ciclo em *vertice_ciclo).
 */
int bellman_ford(GrafoListaPonderado *g, int origem, int *dist, int *pred, int *vertice_ciclo) {
    int V = g->num_vertices;

    // Passo 1: Inicialização
    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        pred[i] = -1;
    }
    dist[origem] = 0;

    // Passo 2: Relaxamento de todas as arestas V - 1 vezes
    for (int i = 1; i <= V - 1; i++) {
        bool mudou = false;
        for (int u = 0; u < V; u++) {
            if (dist[u] == INF) continue;

            Aresta *adj = g->listas[u];
            while (adj != NULL) {
                int v = adj->destino;
                int peso = adj->peso;

                if (dist[u] + peso < dist[v]) {
                    dist[v] = dist[u] + peso;
                    pred[v] = u;
                    mudou = true;
                }
                adj = adj->proximo;
            }
        }
        // Otimização: se nenhuma distância mudou nesta iteração, encerra antecipadamente
        if (!mudou) break;
    }

    // Passo 3: Verificação da N-ésima iteração para detectar ciclo negativo
    for (int u = 0; u < V; u++) {
        if (dist[u] == INF) continue;

        Aresta *adj = g->listas[u];
        while (adj != NULL) {
            int v = adj->destino;
            int peso = adj->peso;

            if (dist[u] + peso < dist[v]) {
                if (vertice_ciclo != NULL) {
                    *vertice_ciclo = v;
                }
                return 0; // Detectou ciclo negativo
            }
            adj = adj->proximo;
        }
    }

    if (vertice_ciclo != NULL) {
        *vertice_ciclo = -1;
    }
    return 1; // Sucesso (sem ciclos negativos)
}

// =======================================================
// RECONSTRUÇÃO DE CAMINHO E CICLO
// =======================================================

void reconstruir_caminho(int origem, int destino, int *pred) {
    if (destino == origem) {
        printf("%d", origem);
        return;
    }
    if (pred[destino] == -1) {
        printf("Sem caminho");
        return;
    }

    int caminho[1000];
    int tam = 0;
    int atual = destino;

    while (atual != -1) {
        caminho[tam++] = atual;
        atual = pred[atual];
    }

    for (int i = tam - 1; i >= 0; i--) {
        printf("%d%s", caminho[i], (i > 0) ? " -> " : "");
    }
}

/**
 * Para garantir que entramos no ciclo, retrocedemos V vezes pelo vetor pred.
 * Em seguida, rastreamos o ciclo até retornar ao mesmo vértice inicial.
 */
void reconstruir_ciclo_negativo(int vertice_inicio, int *pred, int V) {
    int v = vertice_inicio;

    // Retrocede V vezes para garantir que esteja dentro do ciclo
    for (int i = 0; i < V; i++) {
        if (pred[v] != -1) {
            v = pred[v];
        }
    }

    // Armazena a sequência do ciclo
    int ciclo[1000];
    int tam = 0;
    int atual = v;

    do {
        ciclo[tam++] = atual;
        atual = pred[atual];
    } while (atual != v && atual != -1 && tam < V + 1);

    ciclo[tam++] = v; // Fecha o ciclo visualmente

    printf("Ciclo negativo detectado: ");
    for (int i = tam - 1; i >= 0; i--) {
        printf("%d%s", ciclo[i], (i > 0) ? " -> " : "\n");
    }
}