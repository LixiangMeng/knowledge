#include <iostream>
#include <future>
#include <thread>
using namespace std;
void set(promise<int>& promise){
    promise.set_value(10);
}
void getvalue(future<int>& fut){
    int num = fut.get();
    cout<<"num is "<<num<<endl;
}
int main(){
     std::promise<int> prom;

    // 关联future对象和promise
    std::future<int> fut = prom.get_future();

    // 通过promise，实现了线程间的通信
    std::thread t1(set, std::ref(prom));
    std::thread t2(getvalue, std::ref(fut));

    t1.join();
    t2.join();
}