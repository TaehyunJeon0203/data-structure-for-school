#include <stdio.h>
#include <stdbool.h>

int N, M;
int arr[8];
bool used[9];

void backtrack(int depth) {
    if (depth == M) {
        for (int i = 0; i < M; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
        return;
    }

    for (int i = 1; i <= N; i++) {
        if (!used[i]) {
            arr[depth] = i;
            used[i] = true;
            backtrack(depth + 1);
            used[i] = false;
        }
    }
}
int main() {
    scanf("%d %d", &N, &M);

    backtrack(0);

    return 0; 
}