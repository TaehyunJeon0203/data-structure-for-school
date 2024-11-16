/*
아래 코드는 큐를 기반으로 고객을 받고 처리한 이후, VIP 고객, 일반 고객, 전체 고객의 통계를 출력하는
시뮬레이션 프로그램이다.
아래 모델에서 큐는 대기 줄의 역할을 한다.

시뮬레이션은 50000번 반복되며 1번 반복마다 VIP 고객은 10%, 일반 고객은 20%의 확률로 생성된다.

고객이 생성된다면 고객 정보를 customer라는 이름의 구조체에 저장하게 되며,
이 구조체는 id, arrival_time, service_time, is_vip라는 멤버 변수를 가지고 있다.
id 는 고객의 고유한 id이며, arrival_time은 고객이 도착한 시점의 clock을 저장한다.
service_time에는 고객의 서비스를 처리하는 데 필요한 시간 즉, 1 부터 3까지의 난수가 저장된다.
is_vip는 해당 고객이 VIP인지 아닌지를 구분하는 변수이며, VIP라면 1, 아니라면 0을 저장한다.
이후 해당 고객을 큐에 enqueue 하게 된다.

이후 서비스를 처라하게 되는데
먼저 현재 업무를 처리중인 고객이 있는지 확인하게 된다.
처리중인 업무가 존재한다면(service_time이 0보다 크다면) 해당 고객의 service_time을 1 감소시킨 후 다음 clock로 넘어가게 된다.
업무 처리 중인 고객이 없다면 큐에서 고객 한 명을 dequeue한 이후
service_customer에 해당 고객의 id를, service_time에 해당 고객의 service_time을 저장한다.

VIP고객과 일반 고객의 방문 수와, 대기 시간은 vip_wait, vip_customers, normal_wait, normal_customers 에 저장되며,
시뮬레이션이 종료된 이무 VIP고객, 일반 고객, 전체 고객의 통계가 출력된다.
각 통계는 전체 대기시간, 총 고객 수 그리고 평균 대기 시간으로 구성되며,
평균 대기시간은 전체 대기시간을 총 고객 수로 나누어 출력한다.
정수형으로 출력 시에 각 고격 등급 별로 큰 차이가 보이지 않으므로 전체 대기시간을 float 형으로 바꾸어 계산한 후 소수점 세번째 자리까지 표기한다.

-------------------------------------------------------------------
VIP의 큐가 비어있지 않다면 무조건적으로 VIP 고객을 먼저 처리하느 방식으로 구현한 결과

====VIP 고객 통계====
VIP 전체 대기 시간=6753분
VIP 방문 수=5054
VIP 평균 대기 시간=1.336

====일반 고객 통계====
일반 고객 전체 대기 시간=176176678분
일반 고객 방문 수=9874
일반 고�� 평균 대기 시간=17842.482

====전체 통계====
전체 대기 시간=176183431분
총 고객 수=14928
평균 대기 시간=11802.212

위와 같이 일반 고객의 대기시간이 기하급수적으로 상승하였다.
*/

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
        element none = {0, 0, 0, 0};
        return none;
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

    QueueType vip_queue, normal_queue;
    init_queue(&vip_queue);
    init_queue(&normal_queue);

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
                enqueue(&vip_queue, customer);
            } else {
                customer.is_vip = 0;
                normal_customers++;
                printf("일반 고객 %d이 %d분에 들어옵니다. 업무처리시간=%d분\n",
                customer.id, customer.arrival_time, customer.service_time);
                enqueue(&normal_queue, customer);
            }

        }

        // 서비스 처리
        if (service_time > 0) {
            printf("고객 %d 업무처리중입니다.\n", service_customer);
            service_time--;
        } else {
            static int normal_count = 0;

            // VIP 큐가 비어있지 않으면 우선 처리, 단 일반 고객 3명 연속 처리는 보장
            if (!is_empty(&vip_queue) && normal_count < 3) {
                element customer = dequeue(&vip_queue);
                service_customer = customer.id;
                service_time = customer.service_time;
                int wait_time = clock - customer.arrival_time;
                total_wait += wait_time;
                vip_wait += wait_time;
                printf("VIP 고객 %d이 %d분에 업무를 시작합니다. 대기 시간은 %d 분이었습니다.\n",
                    customer.id, clock, wait_time);
                normal_count = 0;
            } else if (!is_empty(&normal_queue)) {
                element customer = dequeue(&normal_queue);
                service_customer = customer.id;
                service_time = customer.service_time;
                int wait_time = clock - customer.arrival_time;
                total_wait += wait_time;
                normal_wait += wait_time;
                printf("일반 고객 %d이 %d분에 업무를 시작합니다. 대기 시간은 %d 분이었습니다.\n",
                    customer.id, clock, wait_time);
                normal_count++;
                if (normal_count >= 3) normal_count = 0;  // 3명 처리 후 리셋
            }
        }
    }
    // VIP 고객 통계
    printf("\n====VIP 고객 통계====\n");
    printf("VIP 전체 대기 시간=%d분\n", vip_wait);
    printf("VIP 방문 수=%d\n", vip_customers);
    if (vip_customers > 0) {
        printf("VIP 평균 대기 시간=%.3f\n", (float)vip_wait / vip_customers);
    }
    // 일반 고객 통계
    printf("\n====일반 고객 통계====\n");
    printf("일반 고객 전체 대기 시간=%d분\n", normal_wait);
    printf("일반 고객 방문 수=%d\n", normal_customers);
    if (normal_customers > 0) {
        printf("일반 고객 평균 대기 시간=%.3f\n", (float)normal_wait / normal_customers);
    }
    // 전체 통계
    printf("\n====전체 통계====\n");
    printf("전체 대기 시간=%d분\n", total_wait);
    printf("총 고객 수=%d\n", total_customers);
    if (normal_customers > 0) {
        printf("평균 대기 시간=%.3f\n", (float)total_wait / total_customers);
    }
}