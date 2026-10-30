#ifndef COBERTURA_H
#define COBERTURA_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// Estrutura para representação de Aresta
typedef struct {
    int u, v;
} Aresta;

// Estrutura do Grafo
typedef struct {
    int num_vertices;
    int num_arestas;
    Aresta *arestas;
    int **matriz_adj; // Matriz de adjacência para consulta rápida
} Grafo;

// Funções de gerenciamento do Grafo
Grafo* criar_grafo(int num_vertices);
void adicionar_aresta(Grafo *g, int u, int v);
void liberar_grafo(Grafo *g);
Grafo* gerar_grafo_aleatorio(int num_vertices, double probabilidade);

// Verificação e Algoritmos de Cobertura de Vértices
bool eh_cobertura(Grafo *g, const bool *coberto);

// Backtracking (Exato com Poda por Limite)
int cobertura_minima_bt(Grafo *g, bool *melhor_solucao);

// Heurística Gulosa (Maior Grau Primeiro)
int cobertura_gulosa(Grafo *g, bool *solucao_gulosa);

// Função para rodar experimentos e medir tempos
void executar_experimento(int n, double prob_aresta);

#endif // COBERTURA_H