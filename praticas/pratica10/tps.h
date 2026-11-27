
#ifndef TPS_H
#define TPS_H

#include "hamiltoniano.h"

int tsp_forca_bruta(
    int custos[MAX_VERTICES][MAX_VERTICES],
    int n,
    int melhor_caminho[MAX_VERTICES + 1],
    int *custo_minimo
);

int tsp_vizinho_mais_proximo(
    int custos[MAX_VERTICES][MAX_VERTICES],
    int n,
    int caminho[MAX_VERTICES + 1],
    int *custo_total
);

int tsp_insercao(
    int custos[MAX_VERTICES][MAX_VERTICES],
    int n,
    int caminho[MAX_VERTICES + 1],
    int *custo_total
);

void grafo_para_tsp(
    int grafo[MAX_VERTICES][MAX_VERTICES],
    int custos[MAX_VERTICES][MAX_VERTICES],
    int n
);

#endif
