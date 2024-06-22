#include <iostream>
#include <atomic>
#include <memory>
#include <thread>
using namespace std;
template<typename T>
class LockfreeStack
{
private:
    struct Node
    {
        T data;
        Node* next;
        Node(T& data):data(data),next(nullptr){}
    };
    atomic<Node*> head_;

public:
    LockfreeStack():head_(nullptr){}
    ~LockfreeStack(){}

    void push(T& value){
        Node* new_node = new Node(value);
        new_node->next = head_.load();
        while (!head_.compare_exchange_weak(new_node->next, new_node));
        
    }
    bool pop(T& value){
        Node* old_head = head_.load();
        while(old_head&&!head_.compare_exchange_weak(old_head,old_head->next));
        if (old_head)
        {
            value = old_head->data;
            delete old_head;
            return true;
        }
        return false;
        
    }
};


int main(){ 
    LockfreeStack<int> stack;
    thread t1([&stack](){
        for(int i=0;i<100;i++){
            stack.push(i);
        }
    });
    thread t2([&stack](){
        for (int i = 0; i < 100; i++)
        {
            int value;
            if(stack.pop(value)){
                cout<<"value is "<<value<<endl;
            }
        }
        
    });
    t1.join();
    t2.join();
}