#include <stdio.h>
#include <stdlib.h>

int tree[1024];
int result[10][1024]; // 각 레벨별 노드
int width[10] = {0}; // 각 레벨의 노드 개수

void build_tree(int start, int end, int level, int K) {
    if (level == K) return;
    
    int mid = (start + end) / 2;
    result[level][width[level]++] = tree[mid];
    
    build_tree(start, mid - 1, level + 1, K);
    build_tree(mid + 1, end, level + 1, K);
}

int main() {
    int K;
    scanf("%d", &K);
    
    int nodes = (1 << K) - 1;
    
    for(int i = 0; i < nodes; i++) {
        scanf("%d", &tree[i]);
    }
    
    build_tree(0, nodes - 1, 0, K);
    
    for(int i = 0; i < K; i++) {
        for(int j = 0; j < width[i]; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}