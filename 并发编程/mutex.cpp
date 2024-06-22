#include<thread>
#include<mutex>
#include<iostream>
#include<chrono>
using namespace std;
chrono::milliseconds interval(100);
mutex mtx;
int job_shared = 0;
int job_exclusive = 0;
void job_1(){
    this_thread::sleep_for(interval);
    while(true){
        if(mtx.try_lock()){
            cout<<"share mission:"<<job_shared<<endl;
            mtx.unlock();
            return;
        }else{
            ++job_exclusive;
            cout<<"running other mission:"<<job_exclusive<<endl;
            this_thread::sleep_for(interval);
        }
    }
}
void job_2(){
    mtx.lock();
    this_thread::sleep_for(5*interval);
    job_shared++;
    mtx.unlock();

}
int main(){
    thread thread1(job_1);
    thread thread2(job_2);
    thread1.join();
    thread2.join();
    cout<<"job_exclusive:"<<job_exclusive<<endl;
}