// https://leetcode.com/explore/learn/card/hash-table/184/comparison-with-other-data-structures/1121/

#include <cassert>
#include <unordered_map>
#include <vector>

bool containsNearbyDuplicate(const std::vector<int>& nums, int k) {
    std::unordered_map<int, int> hash;
    for (int i = 0; i < nums.size(); ++i) {
        int n = nums[i];
        if (hash.count(n) == 1) {
            int diff = i - hash[n];
            if (diff <= k) {
                return true;
            }
        }
        hash[n] = i;
    }
    return false;
}

int main() {
    assert(containsNearbyDuplicate({1,2,3,1}, 3) == true);
    assert(containsNearbyDuplicate({1,0,1,1}, 1) == true);
    assert(containsNearbyDuplicate({1,2,3,1,2,3}, 2) == false);
}
