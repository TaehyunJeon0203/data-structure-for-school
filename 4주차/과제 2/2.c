// 하노이탑 문제
#include <stdio.h>

void hanoi_tower(int n, char from, char tmp, char to) {
    if(n==1) {
        printf("원판 1을 %c에서 %c으로 옮긴다.\n", from, to);
    } else {
        hanoi_tower(n-1, from, to, tmp);
        printf("원판 %d을 %c에서 %c으로 옮긴다.\n",n, from, to);
        hanoi_tower(n-1, tmp, from, to);
    }
}
int main() {
    int n;
    printf("원판의 개수를 입력하세요: ");
    scanf("%d", &n);

    printf("하노이 탑 이동 순서:\n");
    hanoi_tower(n, 'A', 'B', 'C');
}