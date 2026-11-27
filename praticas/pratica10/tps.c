
#include <stdio.h>
#include <limits.h>
#include "tps.h"

static int calcular_custo(
    int custos[MAX_VERTICES][MAX_VERTICES],
    int caminho[],
    int n
) {
    int total = 0;

    for (int i = 0; i < n; i++) {
        total += custos[caminho[i]][caminho[i + 1]];
    }

    return total;
}

/* ---------- TSP FORCA BRUTA ---------- */

static void permutar(
    int custos[MAX_VERTICES][MAX_VERTICES],
    int n,
    int caminho[],
    int visitado[],
    int pos,
    int *melhor_custo,
    int melhor_caminho[]
) {
    if (pos == n) {

        caminho[n] = 0;

        int custo = calcular_custo(custos, caminho, n);

        if (custo < *melhor_custo) {

            *melhor_custo = custo;

            for (int i = 0; i <= n; i++) {
                melhor_caminho[i] = caminho[i];
            }
        }

        return;
    }

    for (int v = 1; v < n; v++) {

        if (!visitado[v]) {

            caminho[pos] = v;
            visitado[v] = 1;

            permutar(
                custos,
                n,
                caminho,
                visitado,
                pos + 1,
                melhor_custo,
                melhor_caminho
            );

            visitado[v] = 0;
        }
    }
}

int tsp_forca_bruta(
    int custos[MAX_VERTICES][MAX_VERTICES],
    int n,
    int melhor_caminho[MAX_VERTICES + 1],
    int *custo_minimo
) {
    if (n <= 0 || n > MAX_VERTICES || custo_minimo == NULL) {
        return 0;
    }

    int caminho[MAX_VERTICES + 1];
    int visitado[MAX_VERTICES] = {0};

    *custo_minimo = INT_MAX;

    caminho[0] = 0;
    visitado[0] = 1;

    permutar(
        custos,
        n,
        caminho,
        visitado,
        1,
        custo_minimo,
        melhor_caminho
    );

    return 1;
}

/* ---------- VIZINHO MAIS PROXIMO ---------- */

int tsp_vizinho_mais_proximo(
    int custos[MAX_VERTICES][MAX_VERTICES],
    int n,
    int caminho[MAX_VERTICES + 1],
    int *custo_total
) {
    if (n <= 0 || n > MAX_VERTICES || custo_total == NULL) {
        return 0;
    }

    int visitado[MAX_VERTICES] = {0};

    caminho[0] = 0;
    visitado[0] = 1;

    int atual = 0;

    for (int i = 1; i < n; i++) {

        int proximo = -1;
        int menor_custo = INT_MAX;

        for (int v = 0; v < n; v++) {

            if (!visitado[v] &&
                custos[atual][v] < menor_custo) {

                menor_custo = custos[atual][v];
                proximo = v;
            }
        }

        if (proximo == -1) {
            return 0;
        }

        caminho[i] = proximo;
        visitado[proximo] = 1;

        atual = proximo;
    }

    caminho[n] = 0;

    *custo_total = calcular_custo(custos, caminho, n);

    return 1;
}

/* ---------- INSERCAO DO MAIS PROXIMO ---------- */

int tsp_insercao(
    int custos[MAX_VERTICES][MAX_VERTICES],
    int n,
    int caminho[MAX_VERTICES + 1],
    int *custo_total
) {
    if (n <= 0 || n > MAX_VERTICES || custo_total == NULL) {
        return 0;
    }

    int visitado[MAX_VERTICES] = {0};
    int tamanho = 1;

    caminho[0] = 0;
    visitado[0] = 1;

    if (n == 1) {
        caminho[1] = 0;
        *custo_total = 0;
        return 1;
    }

    int proximo = -1;
    int menor_custo = INT_MAX;

    for (int v = 1; v < n; v++) {

        if (custos[0][v] < menor_custo) {
            menor_custo = custos[0][v];
            proximo = v;
        }
    }

    caminho[1] = proximo;
    caminho[2] = 0;

    visitado[proximo] = 1;
    tamanho = 2;

    while (tamanho < n) {

        int escolhido = -1;
        menor_custo = INT_MAX;

        /* Escolhe o vertice mais proximo do ciclo */

        for (int v = 0; v < n; v++) {

            if (!visitado[v]) {

                for (int i = 0; i < tamanho; i++) {

                    if (custos[v][caminho[i]] < menor_custo) {

                        menor_custo = custos[v][caminho[i]];
                        escolhido = v;
                    }
                }
            }
        }

        if (escolhido == -1) {
            return 0;
        }

        /* Encontra a melhor posicao de insercao */

        int melhor_posicao = 0;
        int menor_aumento = INT_MAX;

        for (int i = 0; i < tamanho; i++) {

            int atual = caminho[i];
            int seguinte = caminho[i + 1];

            int aumento =
                custos[atual][escolhido] +
                custos[escolhido][seguinte] -
                custos[atual][seguinte];

            if (aumento < menor_aumento) {
                menor_aumento = aumento;
                melhor_posicao = i + 1;
            }
        }

        /* Insere o vertice no ciclo */

        for (int i = tamanho; i >= melhor_posicao; i--) {
            caminho[i] = caminho[i - 1];
        }

        caminho[melhor_posicao] = escolhido;

        visitado[escolhido] = 1;
        tamanho++;

        caminho[tamanho] = 0;
    }

    *custo_total = calcular_custo(custos, caminho, n);

    return 1;
}

/* ---------- CONVERSAO GRAFO PARA TSP ---------- */

void grafo_para_tsp(
    int grafo[MAX_VERTICES][MAX_VERTICES],
    int custos[MAX_VERTICES][MAX_VERTICES],
    int n
) {
    for (int i = 0; i < n; i++) {

        for (int j = 0; j < n; j++) {

            if (i == j) {
                custos[i][j] = 0;
            }
            else if (grafo[i][j]) {
                custos[i][j] = 1;
            }
            else {
                custos[i][j] = 2;
            }
        }
    }
}
