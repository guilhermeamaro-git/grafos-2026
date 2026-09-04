#include <stdio.h> 
#include <string.h>
#include "grafo_lista.h"
#include "busca_grafo.h"

int main() {
    GrafoLista* grafo = criar_grafo(5);

    adicionar_aresta(grafo, 0, 1);
    adicionar_aresta(grafo, 0, 2);
    adicionar_aresta(grafo, 1, 3);
    adicionar_aresta(grafo, 2, 3);
    adicionar_aresta(grafo, 3, 4);

    for (int i = 0; i < grafo->num_vertices; i++) {

        printf("%i: -> ", i + 1);
        No* no = grafo->lista[i];
        while (no != NULL) {
            printf("%i -> ", no->vertice + 1 );
            no = no->proximo;
        }
        printf("\n");

    }


    int visitado[10];

    // Testar DFS
    memset(visitado, 0, sizeof(visitado)); // Reset visitado array
    printf("DFS starting from vertex 1:\n");
    dfs(grafo, 0,visitado);
    printf("\n");   
    memset(visitado, 0, sizeof(visitado)); // Reset visitado array
    printf("DFS starting from vertex 2:\n");
    dfs(grafo, 1,visitado);
    printf("\n");
    memset(visitado, 0, sizeof(visitado)); // Reset visitado array
    printf("DFS starting from vertex 3:\n");
    dfs(grafo, 2,visitado   );
    printf("\n");
    memset(visitado, 0, sizeof(visitado)); // Reset visitado array
    printf("DFS starting from vertex 4:\n");
    dfs(grafo, 3,visitado);
    printf("\n");
    memset(visitado, 0, sizeof(visitado)); // Reset visitado array
    printf("DFS starting from vertex 5:\n");
    dfs(grafo, 4,visitado);
    printf("\n");
    

    return 0;
}