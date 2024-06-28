#ifndef LIFOEVICTIONPOLICY_H
#define LIFOEVICTIONPOLICY_H

#include "IEvictionPolicy.h"
#include <stack>
#include <unordered_set>

template<typename K>
class LIFOEvictionPolicy : public IEvictionPolicy<K> {
    std::stack<K> stack;
    std::unordered_set<K> set;

public:
    void keyAccessed(const K& key) override {
        // No operation for LIFO
    }

    void keyAdded(const K& key) override {
        if (set.find(key) == set.end()) {
            stack.push(key);
            set.insert(key);
        }
    }

    void keyRemoved(const K& key) override {
        if (set.find(key) != set.end()) {
            set.erase(key);
        }
    }

    K evictKey() override {
        if (stack.empty()) {
            throw std::runtime_error("No keys to evict");
        }
        K key = stack.top();
        stack.pop();
        set.erase(key);
        return key;
    }
};

#endif // LIFOCACHEPOLICY_H
