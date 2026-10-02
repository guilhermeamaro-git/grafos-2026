#include <stdio.h>
#include "grafo_matriz.h"

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
    inserir_arco_matriz(&grafo, 0, 1);
    inserir_arco_matriz(&grafo, 1, 2);
    inserir_arco_matriz(&grafo, 2, 0);

    printf("Matriz de Adjencencia\n");
    exibir_matriz(&grafo);

    ----------------------------------------

    GrafoLista grafo_lista;
    int numero_vertices = 8;
    criar_grafo_lista(&grafo_lista, numero_vertices);

    return 0;
}