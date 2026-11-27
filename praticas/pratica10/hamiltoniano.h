
#ifndef HAMILTONIANO_H
#define HAMILTONIANO_H

#define MAX_VERTICES 20

int encontrar_caminho_hamiltoniano_bt(
    int grafo[MAX_VERTICES][MAX_VERTICES],
    int n,
    int caminho[MAX_VERTICES]
);

int encontrar_ciclo_hamiltoniano_bt(
    int grafo[MAX_VERTICES][MAX_VERTICES],
    int n,
    int ciclo[MAX_VERTICES + 1]
);

#endif
