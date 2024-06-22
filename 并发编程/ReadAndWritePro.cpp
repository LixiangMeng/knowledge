#include <iostream>
#include <shared_mutex>
#include <vector>
#include <mutex>
#include <chrono>
#include <thread>
using namespace std;
class SharedData
{
private:
    shared_mutex rw_mtx;
    int data;
public:
    void write(int value){
        unique_lock<shared_mutex> writelock(rw_mtx);
        cout<<"writing "<<value<<endl;
        data = value;
        this_thread::sleep_for(chrono::milliseconds(500));
    }
    int read(){
        shared_lock<shared_mutex> readlock(rw_mtx);
        cout<<"reading "<<data<<endl;
        this_thread::sleep_for(chrono::milliseconds(500));
        return data; 
    }
};


int main(){
    SharedData sharedData;
    thread writers[1];
    thread readers[3];
    writers[0] = thread([&]{sharedData.write(42);});
    for(int i=0;i<3;i++){
        readers[i] = thread([&]{sharedData.read();});
    }
    writers[0].join();
    for (int i = 0; i < 3; i++)
    {
        readers[i].join();
    }
    return 0;
    
}