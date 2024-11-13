typedef struct ListNode {
    int coef; // 계수
    int expon; // 차수
    struct ListNode *link;
} ListNode;

ListNode polyAdd(ListNode *a, ListNode *b) {
    ListNode *result;
    if (a->expon == b->expon) {
        result->coef = a->coef + b->coef;
        result->expon = a->expon;
        insertLast(result);
        a = a->link;
        b = b->link;
    }
}
