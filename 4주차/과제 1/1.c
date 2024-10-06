#include <stdio.h>

int solution(int n) {
    if (n <= 1) return n;

    int a = 0, b = 1, c;
    for (int i = 2; i <= n; i++) {
        c = (a + b) % 1234567;
        a = b;
        b = c;
    }
    return c;
}


int main() {
    int n;
    scanf("%d", &n);
    
    int result = solution(n);
    printf("%d\n", result);
}