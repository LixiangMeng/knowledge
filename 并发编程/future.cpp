#include<iostream>
#include<future>
using namespace std;
int func(int x){
    cout<<"is running"<<endl;
    return x;
}
int main(){
    future<int> result = async(launch::async,func,5);

    // ģ��ִ�б�Ĳ���
    std::cout << "Doing something else..." << std::endl;
    std::cout << "Doing something else..." << std::endl;
    std::cout << "Doing something else..." << std::endl;
    
    int square = result.get();
    cout<<"result: "<<square<<endl;
    return 0;
}