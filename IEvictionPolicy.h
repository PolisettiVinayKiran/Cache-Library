#ifndef IEVICTIONPOLICY_H
#define IEVICTIONPOLICY_H

#include <memory>

// Interface for eviction policies in a cache
template<typename K>
class IEvictionPolicy {
public:
    virtual ~IEvictionPolicy() = default;  // Virtual destructor for polymorphic behavior
    virtual void keyAccessed(const K& key) = 0;  // Called when a key is accessed
    virtual void keyAdded(const K& key) = 0;  // Called when a key is added to the cache
    virtual void keyRemoved(const K& key) = 0;  // Called when a key is removed from the cache
    virtual K evictKey() = 0;  // Determines which key to evict from the cache
};

#endif // IEVICTIONPOLICY_H
