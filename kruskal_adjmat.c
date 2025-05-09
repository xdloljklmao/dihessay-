#include <stdio.h>

int G[10][10], par[10];
int findparent(int i) {
    while (i != par[i])
        i = par[i];
    return i;
}

int Union(int i, int j) {
    if (i != j) {
        par[j] = i;
        return 1;
    }
    return 0;
}

int main() {
    int n, i, j, min, minW = 0, num_edges = 1;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    // Initialize parent array and graph
    for (i = 0; i < n; i++) {
        par[i] = i;
        for (j = 0; j < n; j++)
            G[i][j] = 99;
    }

    printf("Enter adjacency matrix (use 99 for no edge):\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &G[i][j]);

    while (num_edges < n) {
        min = 99;
        int a = -1, b = -1;

        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                if (G[i][j] < min) {
                    min = G[i][j];
                    a = i;
                    b = j;
                }

        if (a == -1 || b == -1) break;

        int u = findparent(a);
        int v = findparent(b);

        if (Union(u, v)) {
            printf("%d. Edge: %d - %d --> %d\n", num_edges, a, b, min);
            minW += min;
            num_edges++;
        }

        G[a][b] = G[b][a] = 99;
    }

    printf("Minimum Spanning Tree Weight: %d\n", minW);
    return 0;
}
