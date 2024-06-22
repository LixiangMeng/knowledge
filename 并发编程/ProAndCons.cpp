#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <queue>
#include <chrono>
using namespace std;
mutex mtx;
condition_variable cv;
queue<int> product;
void producer(int id){
    for(int i=0;i<5;i++){
        unique_lock<mutex> lock(mtx);
        product.push(id*100+i);
        cout<<"Producer "<<id<<" produced "<<product.back()<<endl;
        cv.notify_one();
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}
void consumer(int id){
    for(int i=0;i<5;i++){
        unique_lock<mutex> lock(mtx);
        cv.wait(lock,[]{return !product.empty();});
        int prod = product.front();
        product.pop();
        cout<<"Consumer "<<id<<" comsumed "<<prod<<endl;
    }
}
int main(){
    thread producers[2];
    thread consumers[2];
    for(int i=0;i<2;i++){
        producers[i] = thread(producer,i+1);
    }
    for(int i=0;i<2;i++){
        consumers[i] = thread(consumer,i+1);
    }
    for (int i = 0; i < 2; ++i) {
        producers[i].join();
        consumers[i].join();
    }
}