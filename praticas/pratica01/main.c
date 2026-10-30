#include <stdio.h>
#include "grafo_matriz.h"
#include "grafo_lista.h"

int main() {
   
    GrafoMatriz grafo;
    int numero_vertices = 8;
    criar_grafo_matriz(&grafo, numero_vertices);

    inserir_aresta_matriz(&grafo, 0, 1);
    inserir_aresta_matriz(&grafo, 0, 2);
    inserir_aresta_matriz(&grafo, 0, 3);
    inserir_aresta_matriz(&grafo, 1, 4);
    inserir_aresta_matriz(&grafo, 1, 5);
    inserir_aresta_matriz(&grafo, 2, 3);
    inserir_aresta_matriz(&grafo, 2, 6);
    inserir_aresta_matriz(&grafo, 3, 6);
    inserir_aresta_matriz(&grafo, 7, 4);
    inserir_aresta_matriz(&grafo, 7, 5);
    inserir_aresta_matriz(&grafo, 7, 6);

    criar_grafo_matriz(&grafo, 3);
    remover_aresta_matriz(&grafo, 0, 1);
    grau_matriz(&grafo, 0);
    sao_adjacentes_matriz(&grafo, 0, 1);

    printf("Matriz de Adjencencia\n");
    liberar_grafo_matriz(&grafo);


    GrafoLista grafo_lista;
    criar_grafo_lista(&grafo_lista, numero_vertices);

    inserir_aresta_lista(&grafo_lista, 0, 1);
    inserir_aresta_lista(&grafo_lista, 0, 2);
    inserir_aresta_lista(&grafo_lista, 0, 3);
    inserir_aresta_lista(&grafo_lista, 1, 4);
    inserir_aresta_lista(&grafo_lista, 1, 5);
    inserir_aresta_lista(&grafo_lista, 2, 3);
    inserir_aresta_lista(&grafo_lista, 2, 6);
    inserir_aresta_lista(&grafo_lista, 3, 6);
    inserir_aresta_lista(&grafo_lista, 7, 4);
    inserir_aresta_lista(&grafo_lista, 7, 5);
    inserir_aresta_lista(&grafo_lista, 7, 6);

    criar_grafo_lista(&grafo_lista, 3);
    remover_aresta_lista(&grafo_lista, 0, 1);
    grau_lista(&grafo_lista, 0);
    sao_adjacentes_lista(&grafo_lista, 0, 1);

    printf("Lista de Adjacência\n");
    liberar_grafo_lista(&grafo_lista);

    return 0;
}