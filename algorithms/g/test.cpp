#include <algorithm>
#include <cassert>
#include <cinttypes>
#include <iostream>
#include <limits>
#include <unordered_map>
#include <vector>

using i64 = int64_t;
using i32 = int32_t;

// std::unordered_map<i64, std::unordered_map<i64, i32>> products;
std::unordered_map<i64, std::vector<std::pair<i32, i64>>> products;

void add_offer(i64 offer_id, i64 product_id, i32 price) {
    // products[product_id][offer_id] = price;
    if (products.count(product_id) == 0) {
        products[product_id].push_back({price, offer_id});
    } else {
        auto& offers = products[product_id];
        auto it = std::lower_bound(offers.begin(), offers.end(), std::make_pair(price, i64{0}));
        offers.insert(it, {price, offer_id});
    }
}

void remove_offer(i64 offer_id) {
    /*
    for (auto& [p_id, offers] : products) {
        auto it = offers.find(offer_id);
        if (it != offers.end()) {
            offers.erase(it);
        }
    }
    */
    for (auto& [p_id, offers] : products) {
        // auto it = std::lower_bound(offers.begin(), offers.end(), price);
        offers.erase(std::remove_if(offers.begin(), offers.end(),
                                    [offer_id](auto p) { return p.second == offer_id; }),
                     offers.end());
    }
}

i64 find_closest_offer(i64 product_id, i32 price) {
    // TODO
    i64 closest_offer_id = -1;
    i32 closest_price = std::numeric_limits<i32>::max();
    for (auto& [offer_id, product_price] : products[product_id]) {
        i32 diff = std::abs(price - product_price);
        if (diff < closest_price) {
            closest_price = diff;
            closest_offer_id = offer_id;
        }
    }
    return closest_offer_id;
}

int main() {
    add_offer(1, 1, 10);
    add_offer(2, 1, 14);
    add_offer(3, 1, 11);
    remove_offer(3);
    assert(find_closest_offer(1, 11) == 1);
    std::cout << "OK" << std::endl;
}
