#include<thread>
#include<mutex>
#include<iostream>
#include<chrono>
using namespace std;
class Counter
{
public:
    Counter():count(0){}
    // 增加计数器的值
    void increment()
    {
        // 先暂缓加锁，使用时间互斥量，因为后面需要判断是否超时
        std::unique_lock<std::mutex> ulg(tmtx,defer_lock);
        // 最多尝试五次
        int frequency = 5;
        while (frequency--)
        {
            if (ulg.try_lock())
            {
                // 增加次数1
                count += 1;
                return;
            }
            // 未获锁，休眠0.5秒尝试
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
        std::cout << "[Warning] Increment is failed" << std::endl;
    }

    // 减少计数器的值
    void decrement()
    {
        std::unique_lock<std::mutex> ulg(tmtx,defer_lock);
        int frequency = 3;
        // 最多尝试三次
        while (frequency--)
        {
            // 未获得锁，阻塞0.5秒
            if (ulg.try_lock())
            {
                count -= 1;
                return;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
        std::cout << "[Warning] Decrement is failed" << std::endl;
    }

    int get_value()
    {
        return count;
    }

private:
    int count;
    mutex tmtx;
};
void increment(Counter& counter,int n){
    cout<<"increment n is "<<n<<endl;
    for(int i=0;i<n;i++){
        counter.increment();
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

void decrement(Counter& counter,int n){
    cout<<"decrement n is "<<n<<endl;
    for(int i=0;i<n;i++){
        counter.decrement();
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

int main(){
    Counter counter;
    cout<<"count is "<<counter.get_value()<<endl;
    thread thread1(increment,ref(counter),5);
    thread thread2(decrement,ref(counter),3);
    thread1.join();
    thread2.join();
    cout<<"count is "<<counter.get_value()<<endl;
}