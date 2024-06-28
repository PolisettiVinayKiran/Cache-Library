# Cache Library

This repository contains a C++ Cache Library that supports various eviction policies such as FIFO, LRU, and custom policies. It provides a flexible interface to manage key-value pairs with efficient memory management using different eviction strategies.

## Table of Contents

- [Overview](#overview)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
  - [Building](#building)
  - [Testing](#testing)
- [Adding Custom Eviction Policy](#adding-custom-eviction-policy)
  - [Implementing a Custom Eviction Policy](#implementing-a-custom-eviction-policy)
  - [Integrating Custom Policy into Cache](#integrating-custom-policy-into-cache)
- [Running Main Files](#running-main-files)
  - [Creating a Main File](#creating-a-main-file)
  - [Compiling and Executing](#compiling-and-executing)
- [Contributing](#contributing)
- [License](#license)

## Overview

The Cache Library consists of the following components:
- `ICache.h`: Defines the interface for a cache.
- `Cache.h`: Implements the core cache functionality using an eviction policy.
- `IEvictionPolicy.h`: Defines the interface for eviction policies.
- `FIFOEvictionPolicy.h`, `LRUEvictionPolicy.h`, `LIFOEvictionPolicy.h`: Pre-implemented eviction policies.
- `ThreadSafeCache.h`: Extension of `Cache.h` with thread safety.

Eviction policies currently supported:
- FIFO (First-In-First-Out)
- LRU (Least Recently Used)
- LIFO (Last-In-First-Out)

## Getting Started

### Prerequisites

- C++ compiler that supports C++11 or later.
- Git (optional for cloning the repository).

### Installation

Clone the repository to your local machine:

```bash
https://github.com/PolisettiVinayKiran/Cache-Library.git
cd Cache-Library
```

### Building

No additional build steps are required beyond compilation of the main files.

### Testing

Run the provided `main_*` files to test each eviction policy and ensure functionality:

```bash
./main_fifo
./main_lru
./main_lifo
./main_thread_safe  # If testing the thread-safe version, please note that some versions of mignw, gcc won't support threads on windows
```

## Adding Custom Eviction Policy

To add a custom eviction policy, follow these steps:

### Implementing a Custom Eviction Policy

1. Define a custom eviction policy class within your `main` file.
2. Implement the `IEvictionPolicy` interface methods: `keyAccessed`, `keyAdded`, `keyRemoved`, and `evictKey`.

Example `main_custom.cpp`:

```cpp
#include "Cache.h"
#include "IEvictionPolicy.h"
#include <iostream>
#include <unordered_map>

// Define your custom eviction policy
template<typename K>
class MyCustomEvictionPolicy : public IEvictionPolicy<K> {
public:
    void keyAccessed(const K& key) override {
        // Custom logic for key access
    }

    void keyAdded(const K& key) override {
        // Custom logic for adding key
    }

    void keyRemoved(const K& key) override {
        // Custom logic for removing key
    }

    K evictKey() override {
        // Custom logic to evict a key
        // For example, return a random key
        throw std::runtime_error("Eviction policy not implemented");
    }
};

int main() {
    // Initialize Cache with Custom Eviction Policy
    MyCustomEvictionPolicy<int>* customPolicy = new MyCustomEvictionPolicy<int>();
    Cache<int, std::string> cache(10, customPolicy);

    // Add test cases here
    cache.put(1, "Value1");
    cache.put(2, "Value2");

    // Test cache operations
    std::string value;
    if (cache.get(1, value)) {
        std::cout << "Value retrieved: " << value << std::endl;
    }

    // Clean up
    delete customPolicy;

    return 0;
}
```

### Integrating Custom Policy into Cache

- No changes needed for `Cache.h` as long as your custom policy implements the `IEvictionPolicy` interface. To avoid repetitions, you can consider creating a `.h` header file (take a look at `FIFOEvictionPolicy.h`) of your custom eviction policy.

## Running Main Files

### Creating a Main File

Create a new `main_custom.cpp` file as shown in the example above to test your custom eviction policy.

### Compiling and Executing

Compile and run `main_custom.cpp` to test your custom eviction policy:

```bash
g++ -o main_custom main_custom.cpp
./main_custom
```