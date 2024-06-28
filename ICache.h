#ifndef ICACHE_H
#define ICACHE_H

#include <string>
#include <memory>

// Interface for a generic cache
template<typename K, typename V>
class ICache {
public:
    virtual ~ICache() = default;  // Virtual destructor for polymorphic behavior
    virtual void put(const K& key, const V& value) = 0;  // Insert or update value associated with key
    virtual bool get(const K& key, V& value) = 0;  // Retrieve value associated with key
    virtual void remove(const K& key) = 0;  // Remove entry associated with key
    virtual void clear() = 0;  // Clear all entries from the cache
    virtual size_t size() const = 0;  // Get the current number of entries in the cache
};

#endif // ICACHE_H
