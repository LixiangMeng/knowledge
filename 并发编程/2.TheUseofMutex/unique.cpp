
#include <iostream>
#include <mutex>
#include<stack>
#include<thread>
#include<exception>
std::mutex mtx;
int main() {
    std::unique_lock<std::mutex>  lock(mtx);
    // �ж��Ƿ�ӵ����
    if (lock.owns_lock())
    {
        std::cout << "Main thread has the lock." << std::endl;
    }
    else
    {
        std::cout << "Main thread does not have the lock." << std::endl;
    }
    std::thread t([]() {
        std::unique_lock<std::mutex> lock(mtx, std::defer_lock);
        // �ж��Ƿ�ӵ����
        if (lock.owns_lock())
        {
            std::cout << "Thread has the lock." << std::endl;
        }
        else
        {
            std::cout << "Thread does not have the lock." << std::endl;
        }
        // ����
        lock.lock();
        // �ж��Ƿ�ӵ����
        if (lock.owns_lock())
        {
            std::cout << "Thread has the lock." << std::endl;
        }
        else
        {
            std::cout << "Thread does not have the lock." << std::endl;
        }
        // ����
        lock.unlock();
        });
    t.join();
}