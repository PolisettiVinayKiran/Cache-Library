#ifndef CACHE_H
#define CACHE_H

#include "ICache.h"
#include "IEvictionPolicy.h"
#include <unordered_map>
#include <memory>

// Cache implementation using a key-value store with eviction policy
template<typename K, typename V>
class Cache : public ICache<K, V> {
    std::unordered_map<K, V> cache;        // Storage for key-value pairs
    IEvictionPolicy<K>* evictionPolicy;    // Eviction policy to manage cache size
    size_t maxSize;                        // Maximum number of entries the cache can hold

public:
    Cache(size_t size, IEvictionPolicy<K>* policy)
        : maxSize(size), evictionPolicy(policy) {}

    void put(const K& key, const V& value) override {
        if (cache.size() >= maxSize) {                    // If cache is full
            K evictKey = evictionPolicy->evictKey();     // Determine key to evict
            cache.erase(evictKey);                       // Remove evicted key from cache
            evictionPolicy->keyRemoved(evictKey);        // Notify eviction policy
        }
        cache[key] = value;                              // Add/update key-value pair in cache
        evictionPolicy->keyAdded(key);                    // Notify eviction policy of added key
    }

    bool get(const K& key, V& value) override {
        if (cache.find(key) != cache.end()) {            // If key exists in cache
            value = cache[key];                          // Retrieve value
            evictionPolicy->keyAccessed(key);            // Notify eviction policy of accessed key
            return true;                                 // Return success
        }
        return false;                                    // Return failure
    }

    void remove(const K& key) override {
        if (cache.find(key) != cache.end()) {            // If key exists in cache
            cache.erase(key);                            // Remove key from cache
            evictionPolicy->keyRemoved(key);             // Notify eviction policy
        }
    }

    void clear() override {
        cache.clear();                                  // Clear all entries from cache
    }

    size_t size() const override {
        return cache.size();                            // Return current size of cache
    }
};

#endif // CACHE_H
