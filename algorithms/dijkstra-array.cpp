// Dijkstra Single-Source Shortest Paths (SSSP)
// Implemented using an array and adjency list digraph
// https://www-m3.ma.tum.de/foswiki/pub/MN0506/WebHome/dijkstra.pdf

#include <cassert>

#include <iostream>
#include <limits>
#include <set>
#include <tuple>
#include <vector>

#define INFINITY (std::numeric_limits<float>::infinity())
#define UNDEFINED (-1)

class graph {
   public:
    graph(std::initializer_list<std::tuple<unsigned, unsigned, float>> g) {
        std::set<unsigned> vertices;
        for (const auto& [u, v, _] : g) {
            vertices.insert(u);
            vertices.insert(v);
        }
        adjacency_list_.resize(vertices.size());
        for (const auto& [u, v, w] : g) {
            adjacency_list_[u].push_back(adjacency{v, w});
        }
    }

    auto number_of_vertices() const -> unsigned { return adjacency_list_.size(); }

    auto neighbors(unsigned vertex) const -> std::vector<unsigned> {
        std::vector<unsigned> neighbors;
        const auto& adjs = adjacency_list_[vertex];
        for (const auto& adj : adjs) {
            unsigned node = adj.index;
            neighbors.push_back(node);
        }
        return neighbors;
    }

    auto edge_weight(unsigned u, unsigned v) const -> float {
        const auto& adjs = adjacency_list_[u];
        for (const auto& adj : adjs) {
            if (adj.index == v) {
                return adj.weight;
            }
        }
        throw std::exception();
    }

   private:
    struct adjacency {
        adjacency(unsigned index, float weight) : index{index}, weight{weight} {}
        const unsigned index;
        const float weight;
    };

    std::vector<std::vector<adjacency>> adjacency_list_;
};

auto is_node_unvisited(unsigned node, const std::set<unsigned>& unvisited_nodes) {
    bool unvisited =
        std::find(unvisited_nodes.begin(), unvisited_nodes.end(), node) != unvisited_nodes.end();
    return unvisited;
}

auto unvisited_neighbors(const graph& g, unsigned node, const std::set<unsigned>& unvisited_nodes)
    -> std::vector<unsigned> {
    std::vector<unsigned> unvisited_neighbors;
    std::vector<unsigned> neighbors = g.neighbors(node);
    for (auto neighbor : neighbors) {
        bool unvisited = is_node_unvisited(neighbor, unvisited_nodes);
        if (unvisited) {
            unvisited_neighbors.push_back(neighbor);
        }
    }
    return unvisited_neighbors;
}

// Pop the node with the shortest distance from the list of unvisited nodes
auto pop_shortest_unvisited(const std::vector<float>& distances,
                            std::set<unsigned>& unvisited_nodes) -> unsigned {
    float shortest_distance = std::numeric_limits<float>::infinity();
    auto shortest_distance_it = unvisited_nodes.end();
    auto it = unvisited_nodes.begin();
    for (; it != unvisited_nodes.end(); ++it) {
        unsigned node = *it;
        float distance = distances[node];
        if (distance < shortest_distance) {
            shortest_distance = distance;
            shortest_distance_it = it;
        }
    }
    if (shortest_distance_it == unvisited_nodes.end()) {
        throw std::exception();
    }
    int shortest_distance_node = *shortest_distance_it;
    unvisited_nodes.erase(shortest_distance_it);
    return static_cast<unsigned>(shortest_distance_node);
}

auto shortest_path(const graph& g, unsigned source)
    -> std::pair<std::vector<float>, std::vector<int>> {
    std::vector<float> distances(g.number_of_vertices());
    std::vector<int> path(g.number_of_vertices());
    std::set<unsigned> unvisited_set;
    for (unsigned v = 0; v < g.number_of_vertices(); ++v) {
        distances[v] = INFINITY;
        path[v] = UNDEFINED;
        unvisited_set.insert(v);
    }
    distances[source] = 0.0f;

    while (!unvisited_set.empty()) {
        unsigned current = pop_shortest_unvisited(distances, unvisited_set);
        std::vector<unsigned> neighbors_of_u = unvisited_neighbors(g, current, unvisited_set);
        for (unsigned neighbor : neighbors_of_u) {
            // update the shortest distances by adding the weight of edge current->neighbor
            float new_distance = distances[current] + g.edge_weight(current, neighbor);
            if (new_distance < distances[neighbor]) {
                distances[neighbor] = new_distance;
                path[neighbor] = current;
            }
        }
    }
    return {distances, path};
    /*
    for each vertex v in Graph.Vertices:
        dist[v] ← INFINITY
        prev[v] ← UNDEFINED
        add v to Q
    dist[source] ← 0
    while Q is not empty:
        u ← vertex in Q with min dist[u]
        remove u from Q
        for each neighbor v of u still in Q:
            alt ← dist[u] + Graph.Edges(u, v)
            if alt < dist[v]:
                dist[v] ← alt
                prev[v] ← u
    return dist[], prev[]
    */
}

auto print_path(const std::vector<int> path) -> void {
    for (int v = 0; v < static_cast<int>(path.size()); ++v) {
        auto previous = path[v];
        if (previous != UNDEFINED) {
            std::cout << previous << "->" << v << std::endl;
        }
    }
}

auto main() -> int {
    graph g1{{
        {0, 1, 3.0f},  // 0 -> 1 : 3.0
        {0, 2, 2.0f},  // 0 -> 2 : 2.0
        {1, 0, 2.0f},  // 1 -> 0 : 2.0
        {1, 2, 0.0f},  // 1 -> 2 : 0.0
        {2, 1, 0.0f}   // 2 -> 1 : 0.0
    }};
    auto [distances1, path1] = shortest_path(g1, 0);
    std::vector<float> expected_distance1 = {
        0.0f,  // -> 0 : 0.0
        2.0f,  // -> 1 : 2.0
        2.0f   // -> 2 : 2.0
    };
    assert(distances1 == expected_distance1);
    print_path(path1);

    std::cout << "----" << std::endl;

    graph g2{{
        {0, 1, 2.0f},   // 0 -> 1 : 2.0
        {0, 2, 6.0f},   // 0 -> 2 : 6.0
        {1, 3, 5.0f},   // 1 -> 3 : 5.0
        {2, 3, 8.0f},   // 2 -> 3 : 8.0
        {3, 4, 10.0f},  // 3 -> 4 : 10.0
        {3, 5, 15.0f},  // 3 -> 5 : 15.0
        {4, 5, 6.0f},   // 4 -> 5 : 6.0
        {4, 6, 2.0f},   // 4 -> 6 : 2.0
        {5, 6, 6.0f},   // 5 -> 6  : 6.0
    }};
    std::vector<float> expected_distance2 = {
        0.0f,   // 0 -> 0 : 0.0
        2.0f,   // 0 -> 1 : 2.0
        6.0f,   // 0 -> 2 : 6.0
        7.0f,   // 0 -> 1 -> 3 : 7.0
        17.0f,  // 0 -> 1 -> 3 -> 4 : 17.0
        22.0f,  // 0 -> 1 -> 3 -> 5 : 22.0
        19.0f   // 0 -> 1 -> 3 -> 4 -> 6 : 19.0
    };
    auto [distances2, path2] = shortest_path(g2, 0);
    assert(distances2 == expected_distance2);
    print_path(path2);

    std::cout << "OK" << std::endl;
}
