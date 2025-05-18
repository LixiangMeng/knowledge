#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>
using namespace std;
mutex mtx;
condition_variable cv_a,cv_b,cv_c;
int count = 0;
void print_a(){
    while(true){
        unique_lock<mutex> lck(mtx);
        cout<<"a"<<endl;
        cv_a.wait(lck,[](){return count%3==0;});
        count++;
        cv_b.notify_one();
    }
}

void print_b(){
    while(true){
        unique_lock<mutex> lck(mtx);
        cout<<"b"<<endl;
        cv_b.wait(lck,[](){return count%3==1;});
        count++;
        cv_c.notify_one();
    }
}

void print_c(){
    while(true){
        unique_lock<mutex> lck(mtx);
        cout<<"c"<<endl;
        cv_c.wait(lck,[](){return count%3==2;});
        count=0;
        cv_a.notify_one();
    }
}

int main(){
    thread t1(print_a);
    thread t2(print_b);
    thread t3(print_c);
    t1.join();
    t2.join();
    t3.join();
}