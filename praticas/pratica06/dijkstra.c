#include "dijkstra.h"

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
// IMPLEMENTAÇÃO DO MIN-HEAP COM MAPEAMENTO
// =======================================================

MinHeap* criar_min_heap(int capacidade) {
    MinHeap *heap = (MinHeap*) malloc(sizeof(MinHeap));
    heap->capacidade = capacidade;
    heap->tamanho = 0;
    heap->dados = (NoHeap*) malloc(capacidade * sizeof(NoHeap));
    heap->posicao = (int*) malloc(capacidade * sizeof(int));
    
    for (int i = 0; i < capacidade; i++) {
        heap->posicao[i] = -1;
    }
    return heap;
}

void trocar_nos(MinHeap *heap, int i, int j) {
    // Atualiza os índices no array de mapeamento 'posicao'
    heap->posicao[heap->dados[i].vertice] = j;
    heap->posicao[heap->dados[j].vertice] = i;

    // Troca os elementos no heap
    NoHeap temp = heap->dados[i];
    heap->dados[i] = heap->dados[j];
    heap->dados[j] = temp;
}

void heapify_para_cima(MinHeap *heap, int idx) {
    while (idx > 0 && heap->dados[idx].distancia < heap->dados[(idx - 1) / 2].distancia) {
        trocar_nos(heap, idx, (idx - 1) / 2);
        idx = (idx - 1) / 2;
    }
}

void heapify_para_baixo(MinHeap *heap, int idx) {
    int menor = idx;
    int esq = 2 * idx + 1;
    int dir = 2 * idx + 2;

    if (esq < heap->tamanho && heap->dados[esq].distancia < heap->dados[menor].distancia) {
        menor = esq;
    }
    if (dir < heap->tamanho && heap->dados[dir].distancia < heap->dados[menor].distancia) {
        menor = dir;
    }

    if (menor != idx) {
        trocar_nos(heap, idx, menor);
        heapify_para_baixo(heap, menor);
    }
}

void inserir_min_heap(MinHeap *heap, int vertice, int distancia) {
    if (heap->tamanho == heap->capacidade) return;

    int i = heap->tamanho;
    heap->dados[i].vertice = vertice;
    heap->dados[i].distancia = distancia;
    heap->posicao[vertice] = i;
    heap->tamanho++;

    heapify_para_cima(heap, i);
}

NoHeap extrair_minimo(MinHeap *heap) {
    NoHeap raiz = heap->dados[0];
    NoHeap ultimo = heap->dados[heap->tamanho - 1];

    heap->dados[0] = ultimo;
    heap->posicao[raiz.vertice] = -1; // Marcado como fora do heap
    heap->posicao[ultimo.vertice] = 0;
    
    heap->tamanho--;
    heapify_para_baixo(heap, 0);

    return raiz;
}

void diminuir_chave(MinHeap *heap, int vertice, int nova_distancia) {
    int i = heap->posicao[vertice];
    if (i == -1) return; // Vértice não está no heap

    heap->dados[i].distancia = nova_distancia;
    heapify_para_cima(heap, i);
}

bool esta_vazio(MinHeap *heap) {
    return heap->tamanho == 0;
}

bool esta_no_heap(MinHeap *heap, int vertice) {
    return heap->posicao[vertice] != -1;
}

void liberar_min_heap(MinHeap *heap) {
    if (!heap) return;
    free(heap->dados);
    free(heap->posicao);
    free(heap);
}

// =======================================================
// ALGORITMO DE DIJKSTRA E RECONSTRUÇÃO
// =======================================================

void dijkstra(GrafoListaPonderado *g, int origem, int *dist, int *pred) {
    int V = g->num_vertices;
    MinHeap *heap = criar_min_heap(V);

    for (int v = 0; v < V; v++) {
        dist[v] = INF;
        pred[v] = -1;
        inserir_min_heap(heap, v, dist[v]);
    }

    // Distância da origem para si mesma é 0
    dist[origem] = 0;
    diminuir_chave(heap, origem, 0);

    while (!esta_vazio(heap)) {
        NoHeap min_no = extrair_minimo(heap);
        int u = min_no.vertice;

        // Se a menor distância for infinita, os vértices restantes são inalcançáveis
        if (dist[u] == INF) break;

        Aresta *adj = g->listas[u];
        while (adj != NULL) {
            int v = adj->destino;
            int peso = adj->peso;

            // Relaxamento da aresta (u, v)
            if (esta_no_heap(heap, v) && dist[u] != INF && dist[u] + peso < dist[v]) {
                dist[v] = dist[u] + peso;
                pred[v] = u;
                diminuir_chave(heap, v, dist[v]);
            }
            adj = adj->proximo;
        }
    }

    liberar_min_heap(heap);
}

void reconstruir_caminho(int origem, int destino, int *pred) {
    if (destino == origem) {
        printf("%d", origem);
        return;
    }
    if (pred[destino] == -1) {
        printf("Nao existe caminho entre %d e %d.\n", origem, destino);
        return;
    }

    // Pilha auxiliar simples para inverter a ordem dos antecessores
    int caminho[1000];
    int tam = 0;
    int atual = destino;

    while (atual != -1) {
        caminho[tam++] = atual;
        atual = pred[atual];
    }

    printf("Caminho mínimo: ");
    for (int i = tam - 1; i >= 0; i--) {
        printf("%d%s", caminho[i], (i > 0) ? " -> " : "\n");
    }
}