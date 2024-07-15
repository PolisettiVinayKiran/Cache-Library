#include "Cache.h"
#include "LRUEvictionPolicy.h"
#include <iostream>
#include <memory>

int main() {
    // Create LRU eviction policy
    IEvictionPolicy<int>* lruPolicy = new LRUEvictionPolicy<int>();
    Cache<int, std::string> cache(3, lruPolicy);

    // Test basic puts and gets
    cache.put(1, "one");
    cache.put(2, "two");
    cache.put(3, "three");

    std::string value;
    if (cache.get(1, value)) {
        std::cout << "Key 1: " << value << std::endl;
    } else {
        std::cout << "Key 1 not found" << std::endl;
    }

    // Add more elements to test eviction and access ordering
    cache.put(4, "four");
    cache.put(5, "five");

    // Check if key 2 is evicted
    if (cache.get(2, value)) {
        std::cout << "Key 2: " << value << std::endl;
    } else {
        std::cout << "Key 2 not found" << std::endl;
    }

    // Access key 3 to promote it to the front
    if (cache.get(3, value)) {
        std::cout << "Key 3: " << value << std::endl;
    } else {
        std::cout << "Key 3 not found" << std::endl;
    }

    // Add more elements to test size limit and eviction
    cache.put(6, "six");

    // Check if key 1 is evicted
    if (cache.get(1, value)) {
        std::cout << "Key 1: " << value << std::endl;
    } else {
        std::cout << "Key 1 not found" << std::endl;
    }

    return 0;
}
