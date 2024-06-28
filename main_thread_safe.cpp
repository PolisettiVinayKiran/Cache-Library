#include "ThreadSafeCache.h"
#include "FIFOEvictionPolicy.h"
#include <iostream>
#include <thread>

int main() {
    IEvictionPolicy<int>* policy = new FIFOEvictionPolicy<int>(); // Dynamically allocate policy
    ThreadSafeCache<int, std::string> cache(3, policy);

    std::thread t1([&]() {
        cache.put(1, "one");
        cache.put(2, "two");
        cache.put(3, "three");
    });

    std::thread t2([&]() {
        std::string value;
        if (cache.get(1, value)) {
            std::cout << "Thread 2: Key 1: " << value << std::endl;
        } else {
            std::cout << "Thread 2: Key 1 not found" << std::endl;
        }
    });

    t1.join();
    t2.join();

    return 0;
}
