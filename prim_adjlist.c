#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>

#define MAX 100

struct Node {
    int vertex;
    int weight;
    struct Node* next;
};

struct Node* adjList[MAX];
int visited[MAX], parent[MAX], key[MAX];

char letter(int v) {
    return 'A' + v;
}

void addEdge(int u, int v, int w) {
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
    int min = INT_MAX;
    int v = -1;
    for (int i = 0; i < vertices; i++) {
        if (!visited[i] && key[i] < min) {
            min = key[i];
            v = i;
        }
    }
    return v;
}

void prim(int vertices) {
    for (int i = 0; i < vertices; i++) {
        key[i] = INT_MAX;
        visited[i] = 0;
        parent[i] = -1;
    }

    key[0] = 0;  // Start from vertex A

    for (int i = 0; i < vertices - 1; i++) {
        int u = selectMinVertex(vertices);
        visited[u] = 1;

        struct Node* temp = adjList[u];
        while (temp != NULL) {
            int v = temp->vertex;
            if (!visited[v] && temp->weight < key[v]) {
                key[v] = temp->weight;
                parent[v] = u;
            }
            temp = temp->next;
        }
    }

    printf("\nMinimum Spanning Tree:\n");
    int totalWeight = 0;
    for (int i = 1; i < vertices; i++) {
        printf("%c - %c : %d\n", letter(parent[i]), letter(i), key[i]);
        totalWeight += key[i];
    }
    printf("Total Weight = %d\n", totalWeight);
}

int main() {
    int vertices, edges;
    char startChar, endChar;
    int weight;

    for (int i = 0; i < MAX; i++) {
        adjList[i] = NULL;
    }

    printf("Enter number of vertices: ");
    scanf("%d", &vertices);

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    for (int i = 0; i < edges; i++) {
        printf("\nEdge %d:\n", i + 1);
        printf("Start vertex (A, B, ...): ");
        scanf(" %c", &startChar);
        printf("End vertex (A, B, ...): ");
        scanf(" %c", &endChar);
        printf("Weight: ");
        scanf("%d", &weight);

        int u = toupper(startChar) - 'A';
        int v = toupper(endChar) - 'A';
        addEdge(u, v, weight);
    }

    prim(vertices);

    return 0;
}
