#include "cobertura.h"

// =======================================================
// GERENCIAMENTO DO GRAFO
// =======================================================

Grafo* criar_grafo(int num_vertices) {
    Grafo *g = (Grafo*) malloc(sizeof(Grafo));
    g->num_vertices = num_vertices;
    g->num_arestas = 0;
    g->arestas = NULL;

    g->matriz_adj = (int**) malloc(num_vertices * sizeof(int*));
    for (int i = 0; i < num_vertices; i++) {
        g->matriz_adj[i] = (int*) calloc(num_vertices, sizeof(int));
    }
    return g;
}

void adicionar_aresta(Grafo *g, int u, int v) {
    if (u == v || g->matriz_adj[u][v] == 1) return;

    g->matriz_adj[u][v] = 1;
    g->matriz_adj[v][u] = 1;

    g->num_arestas++;
    g->arestas = (Aresta*) realloc(g->arestas, g->num_arestas * sizeof(Aresta));
    g->arestas[g->num_arestas - 1].u = u;
    g->arestas[g->num_arestas - 1].v = v;
}

void liberar_grafo(Grafo *g) {
    if (!g) return;
    for (int i = 0; i < g->num_vertices; i++) {
        free(g->matriz_adj[i]);
    }
    free(g->matriz_adj);
    free(g->arestas);
    free(g);
}

Grafo* gerar_grafo_aleatorio(int num_vertices, double probabilidade) {
    Grafo *g = criar_grafo(num_vertices);
    for (int i = 0; i < num_vertices; i++) {
        for (int j = i + 1; j < num_vertices; j++) {
            double r = (double) rand() / RAND_MAX;
            if (r < probabilidade) {
                adicionar_aresta(g, i, j);
            }
        }
    }
    return g;
}

// =======================================================
// VERIFICAÇÃO DE COBERTURA
// =======================================================

bool eh_cobertura(Grafo *g, const bool *coberto) {
    for (int i = 0; i < g->num_arestas; i++) {
        int u = g->arestas[i].u;
        int v = g->arestas[i].v;
        if (!coberto[u] && !coberto[v]) {
            return false; // Existe pelo menos uma aresta não incidente a nenhum vértice escolhido
        }
    }
    return true;
}

// =======================================================
// FORÇA BRUTA COM BACKTRACKING E PODA POR LIMITE
// =======================================================

static void bt_recursivo(Grafo *g, int vertice_atual, bool *sol_atual, int tam_atual,
                         bool *melhor_sol, int *min_tam) {
    // Poda por limite: se o tamanho atual já for maior ou igual ao melhor encontrado, aborta este ramo
    if (tam_atual >= *min_tam) return;

    // Caso base: consideramos todos os vértices
    if (vertice_atual == g->num_vertices) {
        if (eh_cobertura(g, sol_atual)) {
            *min_tam = tam_atual;
            for (int i = 0; i < g->num_vertices; i++) {
                melhor_sol[i] = sol_atual[i];
            }
        }
        return;
    }

    // Ramo 1: Inclui o vértice atual na cobertura
    sol_atual[vertice_atual] = true;
    bt_recursivo(g, vertice_atual + 1, sol_atual, tam_atual + 1, melhor_sol, min_tam);

    // Ramo 2: Não inclui o vértice atual na cobertura
    sol_atual[vertice_atual] = false;
    bt_recursivo(g, vertice_atual + 1, sol_atual, tam_atual, melhor_sol, min_tam);
}

int cobertura_minima_bt(Grafo *g, bool *melhor_solucao) {
    bool *sol_atual = (bool*) calloc(g->num_vertices, sizeof(bool));
    int min_tam = g->num_vertices + 1;

    for (int i = 0; i < g->num_vertices; i++) {
        melhor_solucao[i] = false;
    }

    bt_recursivo(g, 0, sol_atual, 0, melhor_solucao, &min_tam);

    free(sol_atual);
    return (min_tam <= g->num_vertices) ? min_tam : 0;
}

// =======================================================
// HEURÍSTICA GULOSA (MAIOR GRAU PRIMEIRA)
// =======================================================

int cobertura_gulosa(Grafo *g, bool *solucao_gulosa) {
    int V = g->num_vertices;
    int E = g->num_arestas;

    // Cópia local das arestas não cobertas
    bool *aresta_coberta = (bool*) calloc(E, sizeof(bool));
    int arestas_restantes = E;

    for (int i = 0; i < V; i++) {
        solucao_gulosa[i] = false;
    }

    int tam_cobertura = 0;

    while (arestas_restantes > 0) {
        // Encontra o vértice de maior grau dinâmico (contando apenas arestas não cobertas)
        int max_grau = -1;
        int melhor_v = -1;

        for (int v = 0; v < V; v++) {
            if (solucao_gulosa[v]) continue;

            int grau_atual = 0;
            for (int e = 0; e < E; e++) {
                if (!aresta_coberta[e]) {
                    if (g->arestas[e].u == v || g->arestas[e].v == v) {
                        grau_atual++;
                    }
                }
            }

            if (grau_atual > max_grau) {
                max_grau = grau_atual;
                melhor_v = v;
            }
        }

        // Se nenhum vértice com arestas restantes for encontrado, encerra
        if (melhor_v == -1 || max_grau == 0) break;

        // Seleciona o melhor vértice
        solucao_gulosa[melhor_v] = true;
        tam_cobertura++;

        // Marca todas as arestas incidentes como cobertas
        for (int e = 0; e < E; e++) {
            if (!aresta_coberta[e]) {
                if (g->arestas[e].u == melhor_v || g->arestas[e].v == melhor_v) {
                    aresta_coberta[e] = true;
                    arestas_restantes--;
                }
            }
        }
    }

    free(aresta_coberta);
    return tam_cobertura;
}

// =======================================================
// EXPERIMENTOS E MEDIÇÃO DE TEMPO
// =======================================================

void executar_experimento(int n, double prob_aresta) {
    Grafo *g = gerar_grafo_aleatorio(n, prob_aresta);

    bool *sol_bt = (bool*) malloc(n * sizeof(bool));
    bool *sol_gulosa = (bool*) malloc(n * sizeof(bool));

    // Medição do Backtracking
    clock_t inicio_bt = clock();
    int tam_bt = cobertura_minima_bt(g, sol_bt);
    clock_t fim_bt = clock();
    double tempo_bt = (double)(fim_bt - inicio_bt) / CLOCKS_PER_SEC;

    // Medição da Heurística Gulosa
    clock_t inicio_g = clock();
    int tam_gulosa = cobertura_gulosa(g, sol_gulosa);
    clock_t fim_g = clock();
    double tempo_gulosa = (double)(fim_g - inicio_g) / CLOCKS_PER_SEC;

    printf("| %2d | %7d | %8d (%s) | %10.6f s | %8d (%s) | %10.6f s |\n",
           n, g->num_arestas,
           tam_bt, eh_cobertura(g, sol_bt) ? "OK" : "ERRO", tempo_bt,
           tam_gulosa, eh_cobertura(g, sol_gulosa) ? "OK" : "ERRO", tempo_gulosa);

    free(sol_bt);
    free(sol_gulosa);
    liberar_grafo(g);
}