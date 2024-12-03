#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1001

int graph[MAX][MAX] = {0,};
int visited[MAX] = {0,};
int queue[MAX];
int N, M, V;

void dfs(int v) {
    visited[v] = 1;
    printf("%d ", v);
    
    for(int i = 1; i <= N; i++) {
        if(graph[v][i] == 1 && !visited[i]) {
            dfs(i);
        }
    }
}

void bfs(int v) {
    int front = 0, rear = 0;
    int pop;
    
    memset(visited, 0, sizeof(visited));
    
    queue[rear++] = v;
    visited[v] = 1;
    
    while(front < rear) {
        pop = queue[front++];
        printf("%d ", pop);
        
        for(int i = 1; i <= N; i++) {
            if(graph[pop][i] == 1 && !visited[i]) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }
    }
}

int main() {
    scanf("%d %d %d", &N, &M, &V);
    
    for(int i = 0; i < M; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        graph[x][y] = 1;
        graph[y][x] = 1;
    }
    
    dfs(V);
    printf("\n");
    bfs(V);
    printf("\n");
    
    return 0;
}