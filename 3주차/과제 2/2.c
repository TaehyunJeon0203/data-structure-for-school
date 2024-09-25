#include <stdio.h>

int sumOneToN(int N);

int main(void) {
    int N = 10;
    printf("%d\n", sumOneToN(N));
}

int sumOneToN(int N) {
    int sum = N * (N + 1) / 2;
    return sum;
}

/*
이 함수의 시간 복잡도는 O(1)이다.
N에 어떠한 수가 오더라도 단 한 번의 연산으로 결과를 얻을 수 있기 때문이다.
*/
