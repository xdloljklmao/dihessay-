#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>

#define MAX 100

int graph[MAX][MAX];
int dist[MAX], visited[MAX];
struct Node {
    int vertex;
    int weight;
    struct Node* next;
};
struct Node* adjList[MAX];

void addEdgeList(int u, int v, int w) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->weight = w;
    newNode->next = adjList[u];
    adjList[u] = newNode;

    newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = u;
    newNode->weight = w;
    newNode->next = adjList[v];
    adjList[v] = newNode;
}

int minDistance(int vertices) {
    int min = INT_MAX, index = -1;
    for (int i = 0; i < vertices; i++) {
        if (!visited[i] && dist[i] < min) {
            min = dist[i];
            index = i;
        }
    }
    return index;
}

void dijkstraMatrix(int vertices, int start) {
    for (int i = 0; i < vertices; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
    }
    dist[start] = 0;

    for (int i = 0; i < vertices - 1; i++) {
        int u = minDistance(vertices);
        visited[u] = 1;

        for (int v = 0; v < vertices; v++) {
            if (!visited[v] && graph[u][v] && dist[u] != INT_MAX &&
                dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    printf("\nShortest distances from %c:\n", 'A' + start);
    for (int i = 0; i < vertices; i++) {
        printf("%c : %d\n", 'A' + i, dist[i]);
    }
}

void dijkstraList(int vertices, int start) {
    for (int i = 0; i < vertices; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
    }
    dist[start] = 0;

    for (int i = 0; i < vertices - 1; i++) {
        int u = minDistance(vertices);
        visited[u] = 1;

        struct Node* temp = adjList[u];
        while (temp) {
            int v = temp->vertex;
            if (!visited[v] && dist[u] + temp->weight < dist[v]) {
                dist[v] = dist[u] + temp->weight;
            }
            temp = temp->next;
        }
    }

    printf("\nShortest distances from %c:\n", 'A' + start);
    for (int i = 0; i < vertices; i++) {
        printf("%c : %d\n", 'A' + i, dist[i]);
    }
}

int main() {
    int vertices, edges, w, choice;
    char startChar, endChar;
    for (int i = 0; i < MAX; i++) adjList[i] = NULL;

    printf("Enter number of vertices: ");
    scanf("%d", &vertices);

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    for (int i = 0; i < vertices; i++)
        for (int j = 0; j < vertices; j++)
            graph[i][j] = 0;

    for (int i = 0; i < edges; i++) {
        printf("\nEdge %d:\n", i + 1);
        printf("Start vertex (A-Z): ");
        scanf(" %c", &startChar);
        printf("End vertex (A-Z): ");
        scanf(" %c", &endChar);
        printf("Weight: ");
        scanf("%d", &w);
        int u = toupper(startChar) - 'A';
        int v = toupper(endChar) - 'A';
        graph[u][v] = w;
        graph[v][u] = w;
        addEdgeList(u, v, w);
    }

    do {
        printf("\nMenu:\n1. Dijkstra using Adjacency Matrix\n2. Dijkstra using Adjacency List\n3. Exit\nChoice: ");
        scanf("%d", &choice);
        if (choice == 1 || choice == 2) {
            printf("Enter start vertex (A-Z): ");
            scanf(" %c", &startChar);
            int start = toupper(startChar) - 'A';
            if (choice == 1)
                dijkstraMatrix(vertices, start);
            else
                dijkstraList(vertices, start);
        } else if (choice != 3) {
            printf("Invalid choice.\n");
        }
    } while (choice != 3);

    return 0;
}
