
#include<queue>
#include<thread>
#include <mutex>
#include <condition_variable>
#include <iostream>
using namespace std;

template<typename T>
class threadsafe_queue
{
private:
    mutex mtx;
    condition_variable cond;
    queue<T> que;
public:
    void push(T value){
        unique_lock<mutex> lock(mtx);
        que.push(value);
        cond.notify_one();
    }
    void pop(T& value){
        unique_lock<mutex> lock(mtx);
        cond.wait(lock,[this]{return !que.empty();});
        value = que.front();
        que.pop();
    }
    bool try_pop(T& value){
        unique_lock<mutex> lock(mtx);
        //cond.wait(lock,[this]{return !que.empty();});
        if(que.empty()){
            return true;
        }
        value = que.front();
        que.pop();
        return false;
    }
};

int main(){
    threadsafe_queue<int> que;
    mutex mtx_print;
    thread producer([&](){
        for(int i=0;i<100;i++){
            que.push(i);
            {
                std::lock_guard<std::mutex> printlk(mtx_print);
                cout<<"producer push data "<<i<<endl;
            }
            this_thread::sleep_for(chrono::milliseconds(100));
        }
    });

    thread consumer1([&](){
        while (true)
        {
            int value;
            que.pop(value);
            {
                std::lock_guard<std::mutex> printlk(mtx_print);
                cout<<"consumer1 pop data "<<value<<endl;
            }
            this_thread::sleep_for(chrono::milliseconds(100));
        }
        
    });

    thread consumer2([&](){
        int value;
        while (true)
        {
            if (que.try_pop(value)){
                std::lock_guard<std::mutex> printlk(mtx_print);
                cout<<"que is empty() "<<endl;
                break;
            }
            else{
                std::lock_guard<std::mutex> printlk(mtx_print);
                cout<<"consumer2 pop data "<<value<<endl;
            }
            this_thread::sleep_for(chrono::milliseconds(100));
        }
        
    });
    producer.join();
    consumer1.join();
    consumer2.join();
}