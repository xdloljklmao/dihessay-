#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define MAX 100

int graph[MAX][MAX];
int distance[MAX];
bool visited[MAX];
int parent[MAX];

int getMinVertex(int vertices) {
    int min = INT_MAX, minIndex = -1;
    for (int i = 0; i < vertices; i++) {
        if (!visited[i] && distance[i] < min) {
            min = distance[i];
            minIndex = i;
        }
    }
    return minIndex;
}

void dijkstra(int vertices, int start) {
    for (int i = 0; i < vertices; i++) {
        distance[i] = INT_MAX;
        visited[i] = false;
        parent[i] = -1;
    }

    distance[start] = 0;

    for (int i = 0; i < vertices - 1; i++) {
        int u = getMinVertex(vertices);
        if (u == -1) break;
        visited[u] = true;

        for (int v = 0; v < vertices; v++) {
            if (graph[u][v] != 0 && !visited[v] && distance[u] + graph[u][v] < distance[v]) {
                distance[v] = distance[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }
}

void printPath(int dest) {
    if (parent[dest] == -1) {
        printf("%c ", 'A' + dest);
        return;
    }
    printPath(parent[dest]);
    printf("-> %c ", 'A' + dest);
}

int main() {
    int vertices, edges, weight;
    char startChar, endChar;
    int start, end;

    printf("Enter number of vertices: ");
    scanf("%d", &vertices);

    for (int i = 0; i < vertices; i++)
        for (int j = 0; j < vertices; j++)
            graph[i][j] = 0;

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    for (int i = 0; i < edges; i++) {
        printf("\nEdge %d:\n", i + 1);
        printf("Start vertex (A, B, ...): ");
        scanf(" %c", &startChar);
        printf("End vertex (A, B, ...): ");
        scanf(" %c", &endChar);
        printf("Edge weight: ");
        scanf("%d", &weight);

        int u = startChar - 'A';
        int v = endChar - 'A';

        graph[u][v] = weight;
        graph[v][u] = weight; 
    }

    printf("\nEnter start node (A, B, ...): ");
    scanf(" %c", &startChar);
    printf("Enter end node (A, B, ...): ");
    scanf(" %c", &endChar);

    start = startChar - 'A';
    end = endChar - 'A';

    dijkstra(vertices, start);

    if (distance[end] == INT_MAX) {
        printf("No path found from %c to %c.\n", startChar, endChar);
    } else {
        printf("\nShortest distance from %c to %c = %d\n", startChar, endChar, distance[end]);
        printf("Path: ");
        printPath(end);
        printf("\n");
    }

    return 0;
}
