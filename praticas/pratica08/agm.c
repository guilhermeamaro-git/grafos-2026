#include "agm.h"

// =======================================================
// GERENCIAMENTO DO GRAFO
// =======================================================

GrafoListaPonderado* criar_grafo(int num_vertices) {
    GrafoListaPonderado *g = (GrafoListaPonderado*) malloc(sizeof(GrafoListaPonderado));
    g->num_vertices = num_vertices;
    g->listas = (ArestaAdj**) malloc(num_vertices * sizeof(ArestaAdj*));
    for (int i = 0; i < num_vertices; i++) {
        g->listas[i] = NULL;
    }
    return g;
}

void adicionar_aresta(GrafoListaPonderado *g, int u, int v, int peso) {
    // Adiciona u -> v
    ArestaAdj *nova1 = (ArestaAdj*) malloc(sizeof(ArestaAdj));
    nova1->destino = v;
    nova1->peso = peso;
    nova1->proximo = g->listas[u];
    g->listas[u] = nova1;

    // Como o grafo é não-direcionado para AGM, adiciona v -> u também
    ArestaAdj *nova2 = (ArestaAdj*) malloc(sizeof(ArestaAdj));
    nova2->destino = u;
    nova2->peso = peso;
    nova2->proximo = g->listas[v];
    g->listas[v] = nova2;
}

void liberar_grafo(GrafoListaPonderado *g) {
    if (!g) return;
    for (int i = 0; i < g->num_vertices; i++) {
        ArestaAdj *atual = g->listas[i];
        while (atual != NULL) {
            ArestaAdj *temp = atual;
            atual = atual->proximo;
            free(temp);
        }
    }
    free(g->listas);
    free(g);
}

// =======================================================
// DSU (UNION-FIND) COM COMPRESSÃO DE CAMINHO E UNIÃO POR RANK
// =======================================================

DSU* criar_dsu(int n) {
    DSU *d = (DSU*) malloc(sizeof(DSU));
    d->n = n;
    d->pai = (int*) malloc(n * sizeof(int));
    d->rank = (int*) calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) {
        d->pai[i] = i;
    }
    return d;
}

int find(DSU *d, int x) {
    if (d->pai[x] != x) {
        d->pai[x] = find(d, d->pai[x]); // Compressão de caminho
    }
    return d->pai[x];
}

bool unir(DSU *d, int x, int y) {
    int raizX = find(d, x);
    int raizY = find(d, y);

    if (raizX == raizY) return false; // Já estão no mesmo conjunto

    // União por rank
    if (d->rank[raizX] < d->rank[raizY]) {
        d->pai[raizX] = raizY;
    } else if (d->rank[raizX] > d->rank[raizY]) {
        d->pai[raizY] = raizX;
    } else {
        d->pai[raizY] = raizX;
        d->rank[raizX]++;
    }
    return true;
}

void liberar_dsu(DSU *d) {
    if (!d) return;
    free(d->pai);
    free(d->rank);
    free(d);
}

// =======================================================
// MIN-HEAP COM MAPEAMENTO (PARA O ALGORITMO DE PRIM)
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

void trocar_nos_heap(MinHeap *heap, int i, int j) {
    heap->posicao[heap->dados[i].vertice] = j;
    heap->posicao[heap->dados[j].vertice] = i;

    NoHeap temp = heap->dados[i];
    heap->dados[i] = heap->dados[j];
    heap->dados[j] = temp;
}

void heapify_para_cima(MinHeap *heap, int idx) {
    while (idx > 0 && heap->dados[idx].chave < heap->dados[(idx - 1) / 2].chave) {
        trocar_nos_heap(heap, idx, (idx - 1) / 2);
        idx = (idx - 1) / 2;
    }
}

void heapify_para_baixo(MinHeap *heap, int idx) {
    int menor = idx;
    int esq = 2 * idx + 1;
    int dir = 2 * idx + 2;

    if (esq < heap->tamanho && heap->dados[esq].chave < heap->dados[menor].chave)
        menor = esq;
    if (dir < heap->tamanho && heap->dados[dir].chave < heap->dados[menor].chave)
        menor = dir;

    if (menor != idx) {
        trocar_nos_heap(heap, idx, menor);
        heapify_para_baixo(heap, menor);
    }
}

void inserir_min_heap(MinHeap *heap, int vertice, int chave) {
    int i = heap->tamanho;
    heap->dados[i].vertice = vertice;
    heap->dados[i].chave = chave;
    heap->posicao[vertice] = i;
    heap->tamanho++;
    heapify_para_cima(heap, i);
}

NoHeap extrair_minimo(MinHeap *heap) {
    NoHeap raiz = heap->dados[0];
    NoHeap ultimo = heap->dados[heap->tamanho - 1];

    heap->dados[0] = ultimo;
    heap->posicao[raiz.vertice] = -1;
    heap->posicao[ultimo.vertice] = 0;

    heap->tamanho--;
    heapify_para_baixo(heap, 0);

    return raiz;
}

void diminuir_chave(MinHeap *heap, int vertice, int nova_chave) {
    int i = heap->posicao[vertice];
    if (i == -1 || heap->dados[i].chave <= nova_chave) return;

    heap->dados[i].chave = nova_chave;
    heapify_para_cima(heap, i);
}

bool esta_no_heap(MinHeap *heap, int vertice) {
    return heap->posicao[vertice] != -1;
}

bool esta_vazio(MinHeap *heap) {
    return heap->tamanho == 0;
}

void liberar_min_heap(MinHeap *heap) {
    if (!heap) return;
    free(heap->dados);
    free(heap->posicao);
    free(heap);
}

// =======================================================
// ALGORITMO DE KRUSKAL
// =======================================================

// Função de comparação para ordenar as arestas por peso (usada no qsort)
int comparar_arestas(const void *a, const void *b) {
    Aresta *aresta1 = (Aresta*) a;
    Aresta *aresta2 = (Aresta*) b;
    return aresta1->peso - aresta2->peso;
}

void kruskal(GrafoListaPonderado *g, Aresta *arestas, int num_arestas) {
    // Ordena as arestas em O(E log E)
    qsort(arestas, num_arestas, sizeof(Aresta), comparar_arestas);

    DSU *dsu = criar_dsu(g->num_vertices);
    int custo_total = 0;

    printf("=== Árvore Geradora Mínima (Kruskal) ===\n");
    for (int i = 0; i < num_arestas; i++) {
        int u = arestas[i].u;
        int v = arestas[i].v;
        int peso = arestas[i].peso;

        // Se u e v pertencem a componentes diferentes, adiciona na AGM
        if (unir(dsu, u, v)) {
            printf("Aresta (%d, %d) com peso %d\n", u, v, peso);
            custo_total += peso;
        }
    }
    printf("Custo Total da AGM (Kruskal): %d\n\n", custo_total);

    liberar_dsu(dsu);
}

// =======================================================
// ALGORITMO DE PRIM
// =======================================================

void prim(GrafoListaPonderado *g, int origem) {
    int V = g->num_vertices;
    int *chave = (int*) malloc(V * sizeof(int));
    int *pai = (int*) malloc(V * sizeof(int));
    MinHeap *heap = criar_min_heap(V);

    for (int v = 0; v < V; v++) {
        chave[v] = INF;
        pai[v] = -1;
        inserir_min_heap(heap, v, chave[v]);
    }

    chave[origem] = 0;
    diminuir_chave(heap, origem, 0);

    while (!esta_vazio(heap)) {
        NoHeap min_no = extrair_minimo(heap);
        int u = min_no.vertice;

        ArestaAdj *adj = g->listas[u];
        while (adj != NULL) {
            int v = adj->destino;
            int peso = adj->peso;

            if (esta_no_heap(heap, v) && peso < chave[v]) {
                chave[v] = peso;
                pai[v] = u;
                diminuir_chave(heap, v, peso);
            }
            adj = adj->proximo;
        }
    }

    int custo_total = 0;
    printf("=== Árvore Geradora Mínima (Prim) ===\n");
    for (int i = 1; i < V; i++) {
        if (pai[i] != -1) {
            printf("Aresta (%d, %d) com peso %d\n", pai[i], i, chave[i]);
            custo_total += chave[i];
        }
    }
    printf("Custo Total da AGM (Prim): %d\n\n", custo_total);

    free(chave);
    free(pai);
    liberar_min_heap(heap);
}