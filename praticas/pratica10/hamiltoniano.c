
#include "hamiltoniano.h"

int verificar_caminho(
    int grafo[MAX_VERTICES][MAX_VERTICES],
    int n,
    int caminho[MAX_VERTICES],
    int visitado[MAX_VERTICES],
    int pos
) {
    if (pos == n) {
        return 1;
    }

    int ultimo = caminho[pos - 1];

    for (int v = 0; v < n; v++) {

        if (grafo[ultimo][v] && !visitado[v]) {

            caminho[pos] = v;
            visitado[v] = 1;

            if (verificar_caminho(
                    grafo, n, caminho, visitado, pos + 1)) {
                return 1;
            }

            visitado[v] = 0;
        }
    }

    return 0;
}

int encontrar_caminho_hamiltoniano_bt(
    int grafo[MAX_VERTICES][MAX_VERTICES],
    int n,
    int caminho[MAX_VERTICES]
) {
    if (n <= 0 || n > MAX_VERTICES) {
        return 0;
    }

    int visitado[MAX_VERTICES] = {0};

    for (int inicio = 0; inicio < n; inicio++) {

        for (int i = 0; i < n; i++) {
            visitado[i] = 0;
        }

        caminho[0] = inicio;
        visitado[inicio] = 1;

        if (verificar_caminho(
                grafo, n, caminho, visitado, 1)) {
            return 1;
        }
    }

    return 0;
}

int verificar_ciclo(
    int grafo[MAX_VERTICES][MAX_VERTICES],
    int n,
    int ciclo[MAX_VERTICES],
    int visitado[MAX_VERTICES],
    int pos
) {
    if (pos == n) {
        return grafo[ciclo[n - 1]][ciclo[0]];
    }

    int ultimo = ciclo[pos - 1];

    for (int v = 1; v < n; v++) {

        if (grafo[ultimo][v] && !visitado[v]) {

            ciclo[pos] = v;
            visitado[v] = 1;

            if (verificar_ciclo(
                    grafo, n, ciclo, visitado, pos + 1)) {
                return 1;
            }

            visitado[v] = 0;
        }
    }

    return 0;
}

int encontrar_ciclo_hamiltoniano_bt(
    int grafo[MAX_VERTICES][MAX_VERTICES],
    int n,
    int ciclo[MAX_VERTICES + 1]
) {
    if (n <= 0 || n > MAX_VERTICES) {
        return 0;
    }

    int visitado[MAX_VERTICES] = {0};

    ciclo[0] = 0;
    visitado[0] = 1;

    if (verificar_ciclo(
            grafo, n, ciclo, visitado, 1)) {

        ciclo[n] = ciclo[0];
        return 1;
    }

    return 0;
}
