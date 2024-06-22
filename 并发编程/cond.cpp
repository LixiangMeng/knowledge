#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

mutex mtx;
condition_variable cv;
int num = 1;
void con_1(){
    while(1){
        unique_lock<mutex> lock(mtx);
        cv.wait(lock,[]{
            return num==1;
        });
        num++;
        cout<<"thread A print 1 "<<endl;
        cv.notify_one();
    }
}

void con_2(){
    while(1){
        unique_lock<mutex> lock(mtx);
        cv.wait(lock,[]{
            return num==2;
        });
        num--;
        cout<<"thread B print 2 "<<endl;
        cv.notify_one();
    }
}

int main(){
    //int num = 1;
    thread t1(con_1);
    thread t2(con_2);
    t1.join();
    t2.join();
}