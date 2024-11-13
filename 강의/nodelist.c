#include<stdio.h>

typedef int element;

typedef struct ListNode {
    element data;
    struct ListNode *link;
} ListNode;

ListNode* insertFirst(ListNode *head, int data) {
    ListNode *p = (ListNode *)malloc(sizeof(ListNode));
    p->data = data;
    p->link = head;
    head = p;

    return head;
}

ListNode* insert(ListNode *head, ListNode *prev, int data) {
    ListNode *p = (ListNode *)malloc(sizeof(ListNode));
    p->data = data;
    p->link = prev->link;
    prev->link = p;

    return head;
}

ListNode* deleteFirst(ListNode *head) {
    ListNode *removed;
    removed = head;
    head = head->link;
    free(removed);

    return head;
}

ListNode* delete(ListNode *head, ListNode *prev) {
    ListNode *removed;
    removed = prev->link;
    prev->link = removed->link;
    free(removed);

    return head;
}

ListNode* printNode(ListNode *head) {
    ListNode *pos;
    pos = head;
    while(pos != NULL) {
        printf("%d", pos->data);
        pos = pos->link;
    }
    // for(ListNode *p = head; p!=NULL; p->p->link)
}

ListNode* searchList(ListNode *head, element data) {
    ListNode *pos;
    pos = head;
    while(pos != NULL) {
        if (pos->data == data) {
            return pos;
        }
    }
}

ListNode* concatList(ListNode *a, ListNode *b) {
    ListNode *aPos;
    aPos = a;
    ListNode *aTail;
    while (aPos->link != NULL) {
        aPos = aPos->link;
    }
    aPos = b;
    
}

int main() {
    // 첫 노드 생성
    ListNode *head = NULL;

    head = (ListNode *)malloc(sizeof(ListNode));

    head->data = 10;
    head->link = NULL;
}
