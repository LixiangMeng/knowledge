#include <shared_mutex>
#include <mutex>
#include <vector>
#include <iostream>
using namespace std;
class ReadWriteVector {
private:
    std::shared_mutex rw_mutex_;
    std::vector<int> vec_;

public:
    void add(int value) {
        std::unique_lock<std::shared_mutex> lock(rw_mutex_);
        vec_.push_back(value);
    }

    int get(int index) {
        std::shared_lock<std::shared_mutex> lock(rw_mutex_);
        return vec_.at(index);
    }

    size_t size() {
        std::shared_lock<std::shared_mutex> lock(rw_mutex_);
        return vec_.size();
    }
};

int main() {
    ReadWriteVector rwVec;
    rwVec.add(10);
    std::cout << "Element at index 0: " << rwVec.get(0) << std::endl;
    return 0;
}