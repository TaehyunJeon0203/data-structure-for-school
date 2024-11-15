#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_QUEUE_SIZE 5

typedef struct {
    int id;
    int arrival_time;
    int service_time;
    int is_vip;
} element;

typedef struct {
    element data[MAX_QUEUE_SIZE];
    int front, rear;
} QueueType;

void init_queue(QueueType *q) {
    q->front = q->rear = 0;
}

int is_empty(QueueType *q) {
    return (q->front == q->rear);
}

int is_full(QueueType *q) {
    return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

void enqueue(QueueType *q, element item) {
    if (is_full(q)) {
        printf("큐가 포화상태입니다\n");
        return;
    }
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
}

element dequeue(QueueType *q) {
    if (is_empty(q)) {
        printf("큐가 공백상태입니다\n");
        exit(1);
    }
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}

int random100() {
    return rand() % 100;
}

int main(void) {
    int minutes = 50000;
    int total_wait = 0;
    int total_customers = 0;
    int service_time = 0;
    int service_customer;

    int vip_wait = 0;
    int vip_customers = 0;
    int normal_wait = 0;
    int normal_customers = 0;

    QueueType queue;
    init_queue(&queue);

    srand(time(NULL));

    for (int clock = 0; clock < minutes; clock++) {
        printf("현재 시각=%d\n", clock);
        int random_value = random100();
        // 고객 도착
        if (random_value < 30) {
            element customer;
            customer.id = total_customers++;
            customer.arrival_time = clock;
            customer.service_time = rand() % 3 + 1;

            // VIP 고객 10%, 일반 고객 20%
            if (random_value < 10) {
                customer.is_vip = 1;
                vip_customers++;
            printf("VIP 고객 %d이 %d분에 들어옵니다. 업무처리시간=%d분\n",
            customer.id, customer.arrival_time, customer.service_time);
            } else {
                customer.is_vip = 0;
                normal_customers++;
                printf("일반 고객 %d이 %d분에 들어옵니다. 업무처리시간=%d분\n",
                customer.id, customer.arrival_time, customer.service_time);
            }

            enqueue(&queue, customer);
        }

        // 서비스 처리
        if (service_time > 0) {
            printf("고객 %d 업무처리중입니다.\n", service_customer);
            service_time--;
        } else {
            if (!is_empty(&queue)) {
                element customer = dequeue(&queue);
                service_customer = customer.id;
                service_time = customer.service_time - 1;

                int wait_time = clock - customer.arrival_time;
                total_wait += wait_time;

                if (customer.is_vip) {
                    vip_wait += wait_time;
                    printf("VIP 고객 %d이 %d분에 업무를 시작합니다. 대기 시간은 %d 분이었습니다.\n",
                    customer.id, clock, wait_time);
                } else {
                    normal_wait += wait_time;
                    printf("일반 고객 %d이 %d분에 업무를 시작합니다. 대기 시간은 %d 분이었습니다.\n",
                    customer.id, clock, wait_time);
                }
            }
        }
    }
    // VIP 고객 통계
    printf("\n====VIP 고객 통계====\n");
    printf("VIP 전체 대기 시간=%d분\n", vip_wait);
    printf("VIP 방문 수=%d\n", vip_customers);
    if (vip_customers > 0) {
        printf("VIP 평균 대기 시간=%.2f\n", (float)vip_wait / vip_customers);
    }
    // 일반 고객 통계
    printf("\n====일반 고객 통계====\n");
    printf("일반 고객 전체 대기 시간=%d분\n", normal_wait);
    printf("일반 고객 방문 수=%d\n", normal_customers);
    if (normal_customers > 0) {
        printf("일반 고객 평균 대기 시간=%.2f\n", (float)normal_wait / normal_customers);
    }
    // 전체 통계
    printf("\n====전체 통계====\n");
    printf("전체 대기 시간=%d분\n", total_wait);
    printf("총 고객 수=%d\n", total_customers);
    if (normal_customers > 0) {
        printf("평균 대기 시간=%.2f\n", (float)total_wait / total_customers);
    }
    // test 코드
    printf("%d %d\n", vip_wait, vip_customers);
    printf("%d %d\n", normal_wait, normal_customers);
    printf("%d %d\n", total_wait, total_customers);
}