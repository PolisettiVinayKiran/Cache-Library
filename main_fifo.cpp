#include "Cache.h"
#include "FIFOEvictionPolicy.h"
#include <iostream>
#include <memory>

int main() {
    IEvictionPolicy<int>* fifoPolicy = new FIFOEvictionPolicy<int>();
    Cache<int, std::string> cache(3, fifoPolicy);

    cache.put(1, "one");
    cache.put(2, "two");
    cache.put(3, "three");

    std::string value;
    if (cache.get(1, value)) {
        std::cout << "Key 1: " << value << std::endl;
    } else {
        std::cout << "Key 1 not found" << std::endl;
    }

    cache.put(4, "four");
    if (cache.get(2, value)) {
        std::cout << "Key 2: " << value << std::endl;
    } else {
        std::cout << "Key 2 not found" << std::endl;
    }

    return 0;
}
