#include <iostream>
#include <atomic>
#include <thread>
using namespace std;
class SpinLock
{
private:
    atomic_flag flag = ATOMIC_FLAG_INIT;
public:
    void lock(){
        while(flag.test_and_set()){

        }
    }
    void unlock(){
        flag.clear();
    }
};


int main(){
    SpinLock spinlock;
    thread t1([&spinlock](){
        spinlock.lock();
        for(int i=0;i<10;i++){
            cout<<"t1 i is "<<i<<endl;
        }
        spinlock.unlock();
    });

    thread t2([&spinlock](){
        spinlock.lock();
        for(int i=0;i<10;i++){
            cout<<"t2 i is "<<i<<endl;
        }
        spinlock.unlock();
    });
    t1.join();
    t2.join();
}