#ifndef THREAD_SAFE_CACHE_H
#define THREAD_SAFE_CACHE_H

#include "ICache.h"
#include "IEvictionPolicy.h"
#include <unordered_map>
#include <memory>
#include <mutex>

template<typename K, typename V>
class ThreadSafeCache : public ICache<K, V> {
    std::unordered_map<K, V> cache;
    IEvictionPolicy<K>* evictionPolicy;
    size_t maxSize;
    mutable std::mutex mutex; // mutable because lock() method in std::lock_guard is const

public:
    ThreadSafeCache(size_t size, IEvictionPolicy<K>* policy)
        : maxSize(size), evictionPolicy(policy) {}

    void put(const K& key, const V& value) override {
        std::lock_guard<std::mutex> lock(mutex); // lock before performing critical operations
        if (cache.size() >= maxSize) {
            K evictKey = evictionPolicy->evictKey();
            cache.erase(evictKey);
            evictionPolicy->keyRemoved(evictKey);
        }
        cache[key] = value;
        evictionPolicy->keyAdded(key);
    }

    bool get(const K& key, V& value) override {
        std::lock_guard<std::mutex> lock(mutex);
        auto it = cache.find(key);
        if (it != cache.end()) {
            value = it->second;
            evictionPolicy->keyAccessed(key);
            return true;
        }
        return false;
    }

    void remove(const K& key) override {
        std::lock_guard<std::mutex> lock(mutex);
        auto it = cache.find(key);
        if (it != cache.end()) {
            cache.erase(it);
            evictionPolicy->keyRemoved(key);
        }
    }

    void clear() override {
        std::lock_guard<std::mutex> lock(mutex);
        cache.clear();
    }

    size_t size() const override {
        std::lock_guard<std::mutex> lock(mutex);
        return cache.size();
    }
};

#endif // THREAD_SAFE_CACHE_H
