#ifndef FIFOEVICTIONPOLICY_H
#define FIFOEVICTIONPOLICY_H

#include "IEvictionPolicy.h"
#include <queue>
#include <unordered_set>

template<typename K>
class FIFOEvictionPolicy : public IEvictionPolicy<K> {
    std::queue<K> queue;
    std::unordered_set<K> set;

public:
    void keyAccessed(const K& key) override {
        // No operation for FIFO
    }

    void keyAdded(const K& key) override {
        if (set.find(key) == set.end()) {
            queue.push(key);
            set.insert(key);
        }
    }

    void keyRemoved(const K& key) override {
        if (set.find(key) != set.end()) {
            set.erase(key);
        }
    }

    K evictKey() override {
        if (queue.empty()) {
            throw std::runtime_error("No keys to evict");
        }
        K key = queue.front();
        queue.pop();
        set.erase(key);
        return key;
    }
};

#endif // FIFOCACHEPOLICY_H
