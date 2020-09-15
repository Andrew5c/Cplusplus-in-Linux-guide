/**
* Copyright(c)
* All rights reserved.
* Author : Andrew. Q
* Date : 2020-09-10-18.32.57
* Description : 链表表示的两个数相加
*/
#include <iostream>

using namespace std;

// 结构体定义链表
// 初始化列表对结构体变量进行初始化
struct ListNode{
    int val;
    ListNode* next;
    ListNode(int x): val(x), next(NULL){}
};

void printList(ListNode* head)
{
    ListNode* temp = head;
    if(temp == NULL)
        return;
    while(temp){
        cout << temp->val << ' ';
        temp = temp->next;
    }
    cout << endl;
}

// 直接递归  逆序输出链表
void reversePrintList(ListNode* head)
{
    // 递归终止条件
    if(head->next == NULL){
        cout << head->val;
        return;
    }
    reversePrintList(head->next);
    cout << head->val;
    return;
}

class Solution
{
public:
    ListNode* addTwoNums(ListNode* l1, ListNode* l2) {
        // 首先定义一个头结点，-1只是一个标志
        ListNode* head = new ListNode(-1);
        ListNode* h = head;
        int sum = 0;
        // 进位标志，且第一次相加没有进位
        bool carry = false;

        while(l1!=NULL || l2!=NULL){
            if(l1 != NULL){
                sum += l1->val;
                l1 = l1->next;
            }
            if(l2 != NULL){
                sum += l2->val;
                l2 = l2->next;
            }
            // 两个个位数相加，进位只可能进1
            if(carry)
                sum++;
            h->next = new ListNode(sum%10);
            h = h->next;
            carry = sum>=10?true:false;
            sum = 0;
        }
        // 最后一次考虑进位
        if(carry)
            h->next = new ListNode(1);
        return head->next;
    }
};

// 28+45 = 73
int main()
{
    ListNode* my11 = new ListNode(8);
    ListNode* my12 = new ListNode(2);
    my11->next = my12;

    ListNode* my21 = new ListNode(5);
    ListNode* my22 = new ListNode(4);
    my21->next = my22;

    Solution mysolution;
    ListNode* res = mysolution.addTwoNums(my11, my21);

    cout << "Hello world!" << endl;
    printList(res);
    reversePrintList(res);
    return 0;
}
