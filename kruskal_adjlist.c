#include <stdio.h>

struct Edge {
    int u, v, w;
};

int par[10];
struct Edge edges[50];

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
    int n, e, i, j, min, minW = 0, num_edges = 1;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++)
        par[i] = i;

    printf("Enter number of edges: ");
    scanf("%d", &e);

    printf("Enter edges (u v weight) 0-indexed:\n");
    for (i = 0; i < e; i++)
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);

    while (num_edges < n) {
        min = 999;
        int pos = -1;

        for (i = 0; i < e; i++) {
            if (edges[i].w < min) {
                min = edges[i].w;
                pos = i;
            }
        }

        if (pos == -1) break;

        int u = findparent(edges[pos].u);
        int v = findparent(edges[pos].v);

        if (Union(u, v)) {
            printf("%d. Edge: %d - %d --> %d\n", num_edges, edges[pos].u, edges[pos].v, edges[pos].w);
            minW += edges[pos].w;
            num_edges++;
        }

        edges[pos].w = 999; // Mark used
    }

    printf("Minimum Spanning Tree Weight: %d\n", minW);
    return 0;
}
