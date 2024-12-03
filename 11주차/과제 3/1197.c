#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int from;
    int to;
    int weight;
} Edge;

int parent[10001];
Edge edges[100001];

int compare(const void* a, const void* b) {
    return ((Edge*)a)->weight - ((Edge*)b)->weight;
}

int find(int x) {
    if (parent[x] == x) return x;
    return parent[x] = find(parent[x]);
}

void union_sets(int x, int y) {
    x = find(x);
    y = find(y);
    if (x != y) parent[y] = x;
}

int main() {
    int V, E;
    scanf("%d %d", &V, &E);
    
    for(int i = 1; i <= V; i++) {
        parent[i] = i;
    }
    
    for(int i = 0; i < E; i++) {
        scanf("%d %d %d", &edges[i].from, &edges[i].to, &edges[i].weight);
    }
    
    qsort(edges, E, sizeof(Edge), compare);
    
    long long result = 0;
    int edge_count = 0;
    
    for(int i = 0; i < E && edge_count < V-1; i++) {
        int from = edges[i].from;
        int to = edges[i].to;
        
        if(find(from) != find(to)) {
            union_sets(from, to);
            result += edges[i].weight;
            edge_count++;
        }
    }
    
    printf("%lld\n", result);
    
    return 0;
}