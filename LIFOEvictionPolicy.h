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
        else
        {
            keyAccessed(key);
        }
    }

    void keyRemoved(const K& key) override {
        if (set.find(key) != set.end()) {
            set.erase(key); // Remove fromt set

            std::stack<K> tempStack; // Remove from stack
            for(int i=0;i<stack_size;i++)
            {
                K topKey = stack.top();
                stack.pop();
                if(topKey != key)
                {
                    tempStack.push(topKey);
                }
            }
            while(!tempStack.empty())
            {
                stack.push(tempStack.top());
                tempStack.pop();
            }
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

    void clear() override {
        while(!stack.empty()) // Clear the stack
        {
            stack.pop();
        }
        set.clear(); // Clear the set
    }
};

#endif // LIFOCACHEPOLICY_H
