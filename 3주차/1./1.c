#include <stdio.h>

int* findMax(int arr[], int size);

int main(void) {

    int score[10] = {50, 90, 93, 77, 88, 56, 89, 95,100,99};

    int *ps = findMax(score, 10);

    printf("최대값: %d\n", *ps);  // 여기서 제일 큰 값인 100이 출력되어야 합니다.

    printf("최대값 위치의 다음 값: %d\n", *(ps+1));  // 여기서 100의 오른쪽 값인 99가 출력되어야 합니다.

    printf("최대값 위치의 이전 값: %d\n", *(ps-1));  // 여기서 100의 왼쪽 값인 95가 출력되어야 합니다.

}

int* findMax(int arr[], int size) {
    int *max = &arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > *max) {
            max = &arr[i];
        }
    }
    return max;
}