#include <stdio.h>

int sumOneToN(int N);

int main(void) {
    int N = 10;
    printf("%d\n", sumOneToN(N));
}

int sumOneToN(int N) {
    int sum = 0;
    for (int i = 1; i <= N; i++) {
        sum += i;
    }
    return sum;
}

/*
이 함수의 시간 복잡도는 O(N)이다.
함수의 for 루프가 정확히 N번 반복된다.
루프 내부의 덧셈 연산도 있긴 하지만 이는 루프 반복 횟수에 비해 미미하다.
따라서 전체 연산은 N에 비례하여 증가하므로 시간 복잡도는 O(N)이다.
*/
