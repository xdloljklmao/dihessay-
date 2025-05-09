#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>

#define MAX 100

int graph[MAX][MAX];
int visited[MAX], parent[MAX], key[MAX];

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

int selectMinVertex(int vertices) {
    int min = INT_MAX, idx = -1;
    for (int i = 0; i < vertices; i++) {
        if (!visited[i] && key[i] < min) {
            min = key[i];
            idx = i;
        }
    }
    return idx;
}

void primMatrix(int vertices) {
    for (int i = 0; i < vertices; i++) {
        key[i] = INT_MAX;
        visited[i] = 0;
        parent[i] = -1;
    }

    key[0] = 0;

    for (int i = 0; i < vertices - 1; i++) {
        int u = selectMinVertex(vertices);
        visited[u] = 1;

        for (int v = 0; v < vertices; v++) {
            if (graph[u][v] && !visited[v] && graph[u][v] < key[v]) {
                key[v] = graph[u][v];
                parent[v] = u;
            }
        }
    }

    printf("\nMST using Adjacency Matrix:\n");
    int total = 0;
    for (int i = 1; i < vertices; i++) {
        printf("%c - %c : %d\n", 'A' + parent[i], 'A' + i, key[i]);
        total += key[i];
    }
    printf("Total Weight: %d\n", total);
}

void primList(int vertices) {
    for (int i = 0; i < vertices; i++) {
        key[i] = INT_MAX;
        visited[i] = 0;
        parent[i] = -1;
    }

    key[0] = 0;

    for (int i = 0; i < vertices - 1; i++) {
        int u = selectMinVertex(vertices);
        visited[u] = 1;

        struct Node* temp = adjList[u];
        while (temp) {
            int v = temp->vertex;
            if (!visited[v] && temp->weight < key[v]) {
                key[v] = temp->weight;
                parent[v] = u;
            }
            temp = temp->next;
        }
    }

    printf("\nMST using Adjacency List:\n");
    int total = 0;
    for (int i = 1; i < vertices; i++) {
        printf("%c - %c : %d\n", 'A' + parent[i], 'A' + i, key[i]);
        total += key[i];
    }
    printf("Total Weight: %d\n", total);
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
        printf("\nMenu:\n1. Prim using Adjacency Matrix\n2. Prim using Adjacency List\n3. Exit\nChoice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: primMatrix(vertices); break;
            case 2: primList(vertices); break;
            case 3: printf("Exiting...\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 3);

    return 0;
}
