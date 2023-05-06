// https://leetcode.com/explore/learn/card/hash-table/182/practical-applications/1140/

// see also std::unordered_map

#include <cassert>

#include <array>
#include <map>

class MyHashMap {
   public:
    MyHashMap() {}

    void put(int key, int value) {
        unsigned n = hash(key);
        auto& bucket = table_[n];
        bucket[key] = value;
    }

    int get(int key) const {
        unsigned n = hash(key);
        auto& bucket = table_[n];
        auto it = bucket.find(key);
        if (it == bucket.end()) {
             return -1;
        }
        return it->second;
    }

    void remove(int key) {
        unsigned n = hash(key);
        auto& bucket = table_[n];
        bucket.erase(key);
    }

   private:
    std::array<std::map<int, int>, 1000> table_;

    unsigned hash(int key) const {
        assert(key >= 0);
        return key % table_.size();
    }
};
