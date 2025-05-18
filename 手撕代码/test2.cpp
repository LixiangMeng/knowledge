// 4. 对单向链表进行排序，要求时间复杂度和空间复杂度最小
// // 单向链表节点结构
// typedef struct Node {
//     int data;               // 节点数据
//     struct Node* next;      // 指向下一个节点的指针
// } Node;
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector<int> val;
struct Node{
    int data;
    Node* next;
    Node(int data):data(data){}
};
// Node* sort(Node *head){
//     Node* dummy = new Node(-1);
//     dummy->next = head;
//     Node* tmp = head;
//     while(tmp){
//         val.push_back(tmp->data);
//         tmp = tmp->next; 
//     }
//     sort(val.begin(),val.end());
//     tmp = head;
//     for(int i=0;i<val.size();i++){
//         tmp->data = val[i];
//         tmp = tmp->next;
//     }
//     return dummy->next;
// }
Node *merge(Node*x,Node*y){
    Node* dummy = new Node(-1);
    Node* tmp = new Node(-1);
    dummy = tmp;
    while(x&&y){
        if(x->data<=y->data){
            tmp->next = x;
            x=x->next;
        }else{
            tmp->next = y;
            y=y->next;
        }
        tmp=tmp->next;
    }

    if(x!=nullptr){
        tmp->next = x;
    }else if(y!=nullptr){
        tmp->next = y;
    }
    return dummy->next;
}
Node* getmid(Node* head){
    Node* fast = head;
    Node* slow = head;
    while(slow&&head){
        fast = fast->next;
        slow = slow->next;
        if(fast){
            fast = fast->next;
        }
    }
    return slow;
}
Node *sort(Node* head){
    if(head==nullptr||head->next==nullptr){
        return head;
    }
    Node* mid = getmid(head);
    Node* left = sort(head);
    Node* right = sort(mid);
    Node* list = merge(left,right);
    return list;
}
int main(){
    Node* head = new Node(2);
    Node* node1 = new Node(1);
    head->next = node1;
    Node* node2 = new Node(3);
    node1->next = node2;
    Node* result = sort(head);
    while(result){
        cout<<result->data<<",";
        result = result->next;
    }
}