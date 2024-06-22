#include <iostream>
#include <mutex>
#include<stack>
#include<thread>
#include<exception>
using namespace std;
struct empty_stack : std::exception
{
    const char* what() const throw() {
        return "empty stack!";
    };
};

template<typename T>
class threadsafe_stack1
{
private:
    stack<T> data;
    mutable mutex m;
public:
    threadsafe_stack1(){}
    threadsafe_stack1(const threadsafe_stack1& other){
        lock_guard<mutex> lock(m);
        data = other.data;
    }
    ~threadsafe_stack1(){}

    void Push(T new_value){
        lock_guard<mutex> lock(m);
        data.push(new_value);
    }
    void Pop(T& value){
        lock_guard<mutex> lock(m);
        if (data.empty()) throw empty_stack();
        value = data.top();
        data.pop();
    }
    bool Empty() const
    {
        std::lock_guard<std::mutex> lock(m);
        return data.empty();
    }
};

int main(){
    threadsafe_stack1<int> safe_stack;
    safe_stack.Push(1);
    thread t1([&safe_stack](){
        if(!safe_stack.Empty()){
            cout<<"thread t1 is running"<<endl;
            this_thread::sleep_for(chrono::milliseconds(1000));
            int value;
            safe_stack.Pop(value);
            cout<<"pop value is "<<value<<endl;
        }
    });
    thread t2([&safe_stack](){
        if(!safe_stack.Empty()){
            cout<<"thread t2 is running"<<endl;
            this_thread::sleep_for(chrono::milliseconds(1000));
            int value;
            safe_stack.Pop(value);
            cout<<"pop value is "<<value<<endl;
        }
    });
    t1.join();
    t2.join();
}