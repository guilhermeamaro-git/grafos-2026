#include <stdio.h>
#include <stdlib.h>
#include "grafo_lista.h"
#include "busca_largura.h"
#include "busca_profundidade.h"

int main(void) {
    int n = 7;
    GrafoLista *g = criar_grafo(n);

    // Componente 1: triangulo 0-1-2-0 -> tem ciclo (impar => nao bipartido)
    adicionar_aresta(g, 0, 1);
    adicionar_aresta(g, 1, 2);
    adicionar_aresta(g, 2, 0);

    // Componente 2: caminho 3-4-5 -> sem ciclo, bipartido
    adicionar_aresta(g, 3, 4);
    adicionar_aresta(g, 4, 5);

    // Componente 3: vertice isolado 6 (sem arestas)

    // ---- BFS a partir do vertice 0 ----
    int *dist = (int *) malloc(sizeof(int) * n);
    int *pred = (int *) malloc(sizeof(int) * n);
    bfs(g, 0, dist, pred);

    printf("== BFS a partir do vertice 0 ==\n");
    for (int i = 0; i < n; i++) {
        printf("Vertice %d: dist = %d, pred = %d\n", i, dist[i], pred[i]);
    }

    // ---- DFS recursiva a partir do vertice 0 ----
    int *visitado = (int *) calloc(n, sizeof(int));
    int *pred_dfs = (int *) malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) pred_dfs[i] = -1;

    printf("\n== DFS recursiva a partir do vertice 0 ==\n");
    dfs_recursiva(g, 0, visitado, pred_dfs);
    for (int i = 0; i < n; i++) {
        if (visitado[i]) {
            printf("Vertice %d: visitado, pred = %d\n", i, pred_dfs[i]);
        }
    }

    // ---- Componentes conexos ----
    int componentes = contar_componentes(g);
    printf("\n== Componentes conexos ==\n");
    printf("Numero de componentes: %d\n", componentes);

    // ---- Deteccao de ciclo ----
    int ciclo = tem_ciclo(g);
    printf("\n== Deteccao de ciclo ==\n");
    printf("O grafo possui ciclo? %s\n", ciclo ? "Sim" : "Nao");

    // ---- Verificacao de biparticao ----
    int bipartido = eh_bipartido(g);
    printf("\n== Verificacao de biparticao ==\n");
    printf("O grafo eh bipartido? %s\n", bipartido ? "Sim" : "Nao");

    free(dist);
    free(pred);
    free(visitado);
    free(pred_dfs);

    // Observacao: grafo_lista.h/.c nao fornece uma funcao de destruicao do
    // grafo (nao ha "destruir_grafo"), entao os nos alocados em
    // adicionar_aresta nao sao liberados aqui.

    return 0;
}