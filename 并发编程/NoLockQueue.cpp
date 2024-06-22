#include<atomic>
#include<iostream>
using namespace std;
class AtomicStack{

private:
    struct Node
    {
        int data;
        atomic<Node*> next;
        Node(int data):data(data),next(nullptr){}
    };
    atomic<Node*> head{nullptr};

public:
    void push(int data){
        Node* node = new Node(data);
        while (true)
        {
            Node* oldhead = head.load(memory_order_relaxed);
            node->next = oldhead;
            if(head.compare_exchange_weak(oldhead,node,memory_order_release,memory_order_relaxed))
                break;
        }
        
    }
    bool pop(int& data){
        Node* oldhead = head.exchange(nullptr,memory_order_acquire);
        if(oldhead!=nullptr){
            Node* newHead = atomic_load(&oldhead->next);
            data = oldhead->data;
            delete oldhead;
            head.store(newHead,memory_order_release);
            return true;

        }
        return false;
    }

};
int main(){
    AtomicStack stack;
    stack.push(42);
    int value;
    if(stack.pop(value)){
        std::cout << "Popped value: " << value << std::endl;
    }
    return 0;
}