#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

template <class T>
class BoundedBlockingQueue {
public:
    BoundedBlockingQueue(int limit, int waitMs) : limit(limit), waitMs(waitMs) {}

    void push(const T& obj) {
        std::unique_lock<std::mutex> lock(mtx);
        notEmpty.wait(lock, [this] { return queue.size() < limit; });
        queue.push(obj);
        notEmpty.notify_one();
    }

    bool pop(T& data) {
        std::unique_lock<std::mutex> lock(mtx);
        if (notEmpty.wait_for(lock, std::chrono::milliseconds(waitMs), [this] { return !queue.empty(); })) {
            data = queue.front();
            queue.pop();
            notEmpty.notify_one();
            return true;
        }
        return false;
    }

private:
    std::queue<T> queue;
    int limit;
    int waitMs;
    std::mutex mtx;
    std::condition_variable notEmpty;
};

void producer(BoundedBlockingQueue<int>& bbq,int id){
     for (int i = 0; i < 20; ++i) {
            bbq.push(id * 20 + i);
    }
}
void consumer(BoundedBlockingQueue<int>& bbq){
    for (int i = 0; i < 200; ++i) {
        int data;
        if (bbq.pop(data)) {
            std::cout << data << " ";
        } else {
            std::cout << "null ";
        }
    }
}
int main() {
    BoundedBlockingQueue<int> bbq(20, 1000); 

    std::vector<std::thread> producers;
    for (int i = 0; i < 10; ++i) {
        producers.emplace_back(producer,std::ref(bbq), i);
    }

    std::thread consumerThread(consumer,std::ref(bbq));

    for (auto& t : producers) {
        t.join();
    }

    consumerThread.join();

    return 0;
}
