#ifndef LRUEVICATIONPOLICY_H
#define LRUEVICATIONPOLICY_H

#include "IEvictionPolicy.h"
#include <list>
#include <unordered_map>

template<typename K>
class LRUEvictionPolicy : public IEvictionPolicy<K> {
    std::list<K> lru_list;
    std::unordered_map<K, typename std::list<K>::iterator> map;

public:
    void keyAccessed(const K& key) override {
        if (map.find(key) != map.end()) {
            lru_list.erase(map[key]);
            lru_list.push_front(key);
            map[key] = lru_list.begin();
        }
    }

    void keyAdded(const K& key) override {
        if (map.find(key) == map.end()) {
            lru_list.push_front(key);
            map[key] = lru_list.begin();
        }
    }

    void keyRemoved(const K& key) override {
        if (map.find(key) != map.end()) {
            lru_list.erase(map[key]);
            map.erase(key);
        }
    }

    K evictKey() override {
        if (lru_list.empty()) {
            throw std::runtime_error("No keys to evict");
        }
        K key = lru_list.back();
        lru_list.pop_back();
        map.erase(key);
        return key;
    }
};

#endif // LRUEVICATIONPOLICY_H
