#include <iostream>
#include <mutex>
using namespace std;
class SingletonSafe
{
private:
    static SingletonSafe* single;
    static std::mutex mtx;
    SingletonSafe(/* args */){}
public:
    static SingletonSafe* getInstance(){
        lock_guard<mutex> lg(mtx);
        if(single!=nullptr){
            single = new SingletonSafe;
        }
        return single;
    }
    void print(){
        cout<<"safe of thread"<<endl;
    }
};
SingletonSafe* SingletonSafe::single = nullptr;
mutex SingletonSafe::mtx;

int main(){
    SingletonSafe* tmp = SingletonSafe::getInstance();
    tmp->print();
}