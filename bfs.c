#include <stdio.h>
#include <stdlib.h>

#define MAX 100

struct Node {
    int vertex;
    struct Node* next;
};

struct Node* adjList[MAX];
int visited[MAX];
int vertices;

struct Queue {
    int items[MAX];
    int front, rear;
};

struct Node* createNode(int v) {
    struct Node* newNode = malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

void addEdge(int src, int dest) {
    struct Node* newNode = createNode(dest);
    newNode->next = adjList[src];
    adjList[src] = newNode;

    newNode = createNode(src);
    newNode->next = adjList[dest];
    adjList[dest] = newNode;
}

struct Queue* createQueue() {
    struct Queue* q = malloc(sizeof(struct Queue));
    q->front = q->rear = -1;
    return q;
}

int isEmpty(struct Queue* q) {
    return q->rear == -1;
}

void enqueue(struct Queue* q, int value) {
    if (q->rear == MAX - 1) return;
    if (q->front == -1) q->front = 0;
    q->items[++q->rear] = value;
}

int dequeue(struct Queue* q) {
    if (isEmpty(q)) return -1;
    int val = q->items[q->front];
    if (q->front >= q->rear)
        q->front = q->rear = -1;
    else
        q->front++;
    return val;
}

void BFS(int start) {
    struct Queue* q = createQueue();
    visited[start] = 1;
    enqueue(q, start);

    while (!isEmpty(q)) {
        int current = dequeue(q);
        printf("%d ", current);

        struct Node* temp = adjList[current];
        while (temp != NULL) {
            if (!visited[temp->vertex]) {
                visited[temp->vertex] = 1;
                enqueue(q, temp->vertex);
            }
            temp = temp->next;
        }
    }
}

int main() {
    int edges, src, dest, start;

    printf("Enter number of vertices: ");
    scanf("%d", &vertices);

    for (int i = 0; i < vertices; i++) {
        adjList[i] = NULL;
        visited[i] = 0;
    }

    printf("Enter number of edges: ");
    scanf("%d", &edges);
    printf("Enter edges (src dest):\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d %d", &src, &dest);
        addEdge(src, dest);
    }

    printf("Enter starting vertex for BFS: ");
    scanf("%d", &start);
    printf("BFS: ");
    BFS(start);
    printf("\n");

    return 0;
}
