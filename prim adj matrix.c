#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAX 100

int graph[MAX][MAX];
int visited[MAX];
int parent[MAX];
int weight[MAX];

char letter(int v) {
    return 'A' + v;
}

int selectMinV(int vertices) {
    int min = INT_MAX, vertex = -1;
    for (int i = 0; i < vertices; i++) {
        if (!visited[i] && weight[i] < min) {
            min = weight[i];
            vertex = i;
        }
    }
    return vertex;
}

void primMatrix(int vertices) {
    for (int i = 0; i < vertices; i++) {
        weight[i] = INT_MAX;
        visited[i] = 0;
        parent[i] = -1;
    }

    weight[0] = 0;
    printf("\nStarting Node -> %c\n", letter(0));

    for (int count = 0; count < vertices - 1; count++) {
        int u = selectMinV(vertices);
        visited[u] = 1;

        printf("\nStep %d\n", count + 1);
        printf("Visited Nodes: { ");
        for (int i = 0; i < vertices; i++) {
            if (visited[i]) printf("%c ", letter(i));
        }
        printf("}\n");

        printf("Remaining Edges from Visited Nodes:\n");
        for (int i = 0; i < vertices; i++) {
            if (visited[i]) {
                for (int j = 0; j < vertices; j++) {
                    if (!visited[j] && graph[i][j] != 0) {
                        printf("%c-%c length = %d\n", letter(i), letter(j), graph[i][j]);
                    }
                }
            }
        }

        for (int v = 0; v < vertices; v++) {
            if (graph[u][v] && !visited[v] && graph[u][v] < weight[v]) {
                weight[v] = graph[u][v];
                parent[v] = u;
            }
        }
    }

    printf("\nMinimum Spanning Tree Edges:\n");
    int totalWeight = 0;
    for (int i = 1; i < vertices; i++) {
        printf("%c - %c : %d\n", letter(parent[i]), letter(i), graph[i][parent[i]]);
        totalWeight += graph[i][parent[i]];
    }
    printf("\nTotal Edge Weight of MST = %d\n", totalWeight);
}

int main() {
    int vertices, edges, w;
    char startChar, endChar;

    printf("Enter number of vertices: ");
    scanf("%d", &vertices);

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    for (int i = 0; i < vertices; i++)
        for (int j = 0; j < vertices; j++)
            graph[i][j] = 0;

    for (int i = 0; i < edges; i++) {
        printf("\nEdge %d:\n", i + 1);
        printf("Enter start vertex (A, B, C...): ");
        scanf(" %c", &startChar);
        printf("Enter end vertex (A, B, C...): ");
        scanf(" %c", &endChar);
        printf("Enter edge weight: ");
        scanf("%d", &w);

        int u = startChar - 'A';
        int v = endChar - 'A';

        graph[u][v] = w;
        graph[v][u] = w;
    }

    primMatrix(vertices);
    return 0;
}
