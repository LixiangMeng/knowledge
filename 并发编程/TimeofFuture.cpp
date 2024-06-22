#include <iostream>
#include <chrono>
#include <future>
#include <thread>
using namespace std;
int square(int x){
    this_thread::sleep_for(chrono::milliseconds(500));
    return x*x;
}
int cube(int x){
    this_thread::sleep_for(chrono::milliseconds(500));
    return x*x*x;
}
int add(int x,int y){
    this_thread::sleep_for(chrono::milliseconds(500));
    return x+y;
}
int main(){
    auto start = chrono::high_resolution_clock::now();
    int result1 = square(5);
    int result2 = cube(10);
    int result3 = add(result1,result2);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration_linear = end - start;
    cout<<"linear time is "<<duration_linear.count()<<endl;


    start = std::chrono::high_resolution_clock::now();

    promise<int> pro_square;
    future<int> fut_square = pro_square.get_future();
    thread t_square([&pro_square](){
        pro_square.set_value(square(5));
    });

    promise<int> pro_cube;
    future<int> fut_cube = pro_cube.get_future();
    thread t_cube([&pro_cube](){
        pro_cube.set_value(cube(10));
    });

    auto add_lambda = [&fut_square,&fut_cube](){
        int result1 = fut_square.get();
        int result2 = fut_cube.get();
        return add(result1,result2);
    };
    packaged_task<int()> pt_add(add_lambda);
    future<int> fut_add = pt_add.get_future();
    t_square.join();
    t_cube.join();
    pt_add();
    int result_add = fut_add.get();

    end = chrono::high_resolution_clock::now();
    duration_linear = end - start;
    cout<<"async time is "<<duration_linear.count()<<endl;

}