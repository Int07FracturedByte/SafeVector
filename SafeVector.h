#pragma once
#include <vector>
#include <mutex>

template <class T>
class SafeVector {
public:
    SafeVector() : vec(), mut(){}
    SafeVector(const SafeVector& orig) : vec(orig.vec), mut(){}

    void insert(T in, const int index) {
        std::lock_guard<std::mutex> lock(mut);
        vec[index] = std::move(in);
    }
    void push_back(T in) {
        std::lock_guard<std::mutex> lock(mut);
        vec.push_back(std::move(in));
    }
    T& operator[](const int index) {
        std::lock_guard<std::mutex> lock(mut);
        return vec[index];
    }

    size_t size() {
        std::lock_guard<std::mutex> lock(mut);
        return vec.size();
    }

    void erase(size_t index) {
        std::lock_guard<std::mutex> lock(mut);
        vec.erase(vec.begin() + index);
    }

private:
    std::vector<T> vec;
    std::mutex mut;    
};
