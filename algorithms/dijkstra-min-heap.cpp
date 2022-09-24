// Dijkstra Single-Source Shortest Paths (SSSP)
// Implemented using priority-queue (min-heap) and matrix digraph
// https://www-m3.ma.tum.de/foswiki/pub/MN0506/WebHome/dijkstra.pdf

#include <cassert>

#include <iostream>
#include <limits>
#include <vector>

// min-heap of (node, weight), where weight is the key
template <typename N, typename W>
class priority_queue final {
   public:
    auto push(const N& node, const W& weight) -> void {
        min_heap_.push_back({node, weight});
        std::push_heap(min_heap_.begin(), min_heap_.end(), comparator{});
    }

    auto pop() -> N {
        std::pop_heap(min_heap_.begin(), min_heap_.end(), comparator{});
        auto node = min_heap_.back().first;
        min_heap_.pop_back();
        return node;
    }

    auto contains(const N& node) const -> bool {
        auto it = min_heap_.cbegin();
        for (; it != min_heap_.cend(); ++it)
            if (it->first == node)
                return true;
        return false;
    }

    auto decrease_priority(const N& node, const W& new_weight) -> void {
        auto it = min_heap_.begin();
        for (; it != min_heap_.end(); ++it) {
            if (it->first == node) {
                float& old_weight = it->second;
                if (new_weight < old_weight) {
                    old_weight = new_weight;
                    std::make_heap(min_heap_.begin(), min_heap_.end(), comparator{});
                    return;
                }
            }
        }
        throw std::exception();
    }

    auto empty() const noexcept -> bool { return min_heap_.empty(); }

   private:
    // use > to get a min-heap (smallest first)
    struct comparator {
        bool operator()(const std::pair<N, W>& lhs, const std::pair<N, W>& rhs) const {
            return lhs.second > rhs.second;
        }
    };
    std::vector<std::pair<N, W>> min_heap_;
};

class graph {
   public:
    graph(std::initializer_list<std::initializer_list<float>> g) {
        auto it1 = std::cbegin(g);
        unsigned i = 0;
        for (; it1 != std::cend(g); ++it1, ++i) {
            auto it2 = it1->begin();
            g_.push_back({});
            for (; it2 != it1->end(); ++it2) {
                g_[i].push_back(*it2);
            }
        }
    }

    auto number_of_vertices() const -> unsigned { return g_.size(); }

    auto unvisited_neighbors(unsigned vertex, const priority_queue<unsigned, float>& q) const
        -> std::vector<unsigned> {
        std::vector<unsigned> neighbors;
        const std::vector<float>& adjs = g_[vertex];
        for (unsigned i = 0; i < adjs.size(); i++) {
            float w = adjs[i];
            if (w >= 0.0f && q.contains(i)) {
                neighbors.push_back(i);
            }
        }
        return neighbors;
    }

    auto edge_weight(unsigned u, unsigned v) const -> float {
        const auto& w = g_[u][v];
        if (w < 0)
            throw std::exception();
        return w;
    }

   private:
    std::vector<std::vector<float>> g_;
};

#define INFINITY (std::numeric_limits<float>::infinity())
#define UNDEFINED (-1)

auto shortest_path(const graph& g, unsigned source) -> std::vector<float> {
    unsigned num_vertices = g.number_of_vertices();
    std::vector<int> prev(num_vertices);    // predecessors
    std::vector<float> dist(num_vertices);  // distances from source to node i
    dist[source] = 0.0f;
    priority_queue<unsigned, float> q;
    for (unsigned vertex = 0; vertex < num_vertices; ++vertex) {
        if (vertex != source)
            dist[vertex] = INFINITY;
        prev[vertex] = UNDEFINED;
        q.push(vertex, dist[vertex]);
    }
    while (!q.empty()) {
        unsigned u = q.pop();
        std::vector<unsigned> neighbors_of_u = g.unvisited_neighbors(u, q);
        for (const auto& v : neighbors_of_u) {
            float alt = dist[u] + g.edge_weight(u, v);
            if (alt < dist[v]) {
                dist[v] = alt;
                prev[v] = static_cast<int>(u);
                q.decrease_priority(v, alt);
            }
        }
    }
    return dist;
}

auto main() -> int {
    // 0 -> 1 : 3.0
    // 0 -> 2 : 2.0
    // 1 -> 0 : 2.0
    // 1 -> 2 : 0.0
    // 2 -> 1 : 0.0
    graph g1 = {
        {-1.0f, 3.0f, 2.0f},  // edges leaving node 0
        {2.0f, -1.0f, 0.0f},  // edges leaving node 1
        {-1.0f, 0.0f, -1.0f}  // edges leaving node 2
    };
    std::vector<float> expected1 = {
        0.0f,  // 0 -> 0: 0.0
        2.0f,  // 0 -> 1: 2.0
        2.0f   // 0 -> 2: 2.0
    };
    assert(shortest_path(g1, 0) == expected1);

    std::cout << "OK" << std::endl;
}
