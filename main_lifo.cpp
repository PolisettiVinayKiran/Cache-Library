#include "Cache.h"
#include "LIFOEvictionPolicy.h"
#include <iostream>
#include <memory>

int main() {
    IEvictionPolicy<int>* lifoPolicy = new LIFOEvictionPolicy<int>();
    Cache<int, std::string> cache(3, std::move(lifoPolicy));

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
    if (cache.get(3, value)) {
        std::cout << "Key 3: " << value << std::endl;
    } else {
        std::cout << "Key 3 not found" << std::endl;
    }

    return 0;
}
