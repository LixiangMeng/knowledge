#include<thread>
#include<mutex>
#include<iostream>
#include<chrono>
using namespace std;
mutex mtx;
void sharedFunc(int i){
    lock_guard<mutex> lg(mtx);
    cout<<"thread "<<i<<" is accessing shared resource"<<endl;
}
int main(){
    thread threads[5];
    for(int i=0;i<5;i++){
        threads[i] = thread(sharedFunc,i);
    }
    for(int i=0;i<5;i++)
        threads[i].join();
}