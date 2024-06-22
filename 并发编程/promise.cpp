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

    // ����future�����promise
    std::future<int> fut = prom.get_future();

    // ͨ��promise��ʵ�����̼߳��ͨ��
    std::thread t1(set, std::ref(prom));
    std::thread t2(getvalue, std::ref(fut));

    t1.join();
    t2.join();
}