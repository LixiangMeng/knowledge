#include<queue>
#include <mutex>
#include <condition_variable>
#include <iostream>
using namespace std;
template<typename T>
class ThreadSafeQueue{
private:
    queue<T> queue_;
    mutex mtx_;
    condition_variable cond_;

public:
    void push(T value){
        lock_guard<mutex> lg(mtx_);
        queue_.push(value);
        cond_.notify_one();
    }
    T pop(){
        unique_lock<mutex> lock(mtx_);
        cond_.wait(lock,[this]{ 
            return !queue_.empty();});
        T value = queue_.front();
        queue_.pop();
        return value;
    }
    bool empty(){
        lock_guard<mutex> lock(mtx_);
        return queue_.empty();
    }
};
int main(){
    ThreadSafeQueue<int> que;
    //int value1 = que.pop();
    que.push(1);
    int value = que.pop();
    cout<<"value="<<value<<endl;
    return 0;
}