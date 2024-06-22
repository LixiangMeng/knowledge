#include<iostream>
#include<thread>
#include<string>
#include<chrono>
using namespace std;
void printHello(std::string str){
    cout<<str<<endl;
}
void waitPrint(string msg){
    std::this_thread::sleep_for(std::chrono::seconds(2));
    cout<< "sleep over"<<endl;
    cout<<msg<<endl;
}
int main(){
    std::thread thread1(printHello,"my name is meng");
    thread thread2([](string str){
        cout<<str<<endl;
    }, "thread2");
    thread1.join();
    thread2.join();

    thread thread3(waitPrint, "detach thread");
    cout<<"before detach:"<<thread3.joinable()<<endl;
    thread3.join();
    
    cout<<"after detach:"<<thread3.joinable()<<endl;
    
}