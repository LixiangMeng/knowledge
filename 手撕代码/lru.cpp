#include<iostream>
#include<unordered_map>
using namespace std;
class Node{
public:
    int key,value;
    Node *next,*prev;
    Node(int key=0,int value=0):key(key),value(value){}
};

class LRUCache
{
private:
    int capacity;
    Node* dummy;
    unordered_map<int, Node*> cache;

    void remove(Node *x){
        x->next->prev = x->prev;
        x->prev->next = x->next;
    }

    void put_front(Node *x){
        auto it = cache.find(x->key);
        if(it==cache.end()){
            
        }
    }
public:
    LRUCache(int capacity):capacity(capacity),dummy(new Node()){
        dummy->next = dummy;
        dummy->prev = dummy;
    }
    int get(int key){

    }

    void put(){

    }
};



int main(){

}