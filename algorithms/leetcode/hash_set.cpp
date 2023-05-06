// https://leetcode.com/explore/learn/card/hash-table/182/practical-applications/1139/

// see also std::unordered_set

#include <array>
#include <optional>

class MyHashSet {
   public:
    MyHashSet() {}

    void add(int key) {
        unsigned n = hash(key);
        table_[n] = key;
    }

    void remove(int key) {
        unsigned n = hash(key);
        table_[n] = std::optional<int>{};
    }

    bool contains(int key) const {
        unsigned n = hash(key);
        return table_[n].has_value();
    }

   private:
    std::array<std::optional<int>, 1000001> table_;

    unsigned hash(int value) const { return value % table_.size(); }
};
