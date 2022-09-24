// weighted directed graph (aka digraph) implemented with a adjency list

#include <cassert>

#include <iostream>
#include <optional>
#include <string>
#include <vector>

struct edge {
    edge(const std::string& u, const std::string& v, float w) : src{u}, dst{v}, weight{w} {}

    std::string src;
    std::string dst;
    float weight = 1.0f;
};

struct adjacency {
    adjacency(unsigned index, float weight) : index{index}, weight{weight} {}

    const unsigned index;
    const float weight;
};

class digraph {
   public:
    digraph(const std::vector<edge>& edges) {
        add_vertices(edges);
        add_edges(edges);
    }

    auto add_vertices(const std::vector<edge>& edges) -> void {
        for (const auto& edge : edges) {
            if (!index_of(edge.src))
                vertices_.push_back(edge.src);
            if (!index_of(edge.dst))
                vertices_.push_back(edge.dst);
        }
    }

    auto add_edges(const std::vector<edge>& edges) -> void {  //
        adjacency_list_.resize(vertices_.size());
        for (const auto& edge : edges) {
            unsigned src = index_of(edge.src).value();
            unsigned dst = index_of(edge.dst).value();
            adjacency_list_[src].push_back(adjacency{dst, edge.weight});
        }
    }

    // adjacent nodes by index
    auto neighbors(unsigned v) const -> std::vector<adjacency> {  //
        return adjacency_list_[v];
    }

    auto index_of(const std::string& vertex) const noexcept -> std::optional<unsigned> {
        for (unsigned i = 0; i < vertices_.size(); ++i)
            if (vertices_[i] == vertex)
                return i;
        return {};
    }

    auto print() const noexcept -> void {
        std::cout << "[ ";
        for (unsigned i = 0; i < vertices_.size(); ++i) {
            std::cout << i << ":" << vertices_[i] << " ";
        }
        std::cout << "]\n";
        std::cout << "{\n";
        for (unsigned i = 0; i < adjacency_list_.size(); ++i) {
            const auto& src = vertices_[i];
            const auto& adjacents = adjacency_list_[i];
            for (unsigned j = 0; j < adjacents.size(); j++) {
                const auto& adjacent = adjacents[j];
                const auto& dst = vertices_[adjacent.index];
                float weight = adjacent.weight;
                std::cout << "\t" << src << " -> " << dst << " : " << weight << "\n";
            }
        }
        std::cout << "}" << std::endl;
    }

   private:
    std::vector<std::string> vertices_;
    std::vector<std::vector<adjacency>> adjacency_list_;
};

auto main() -> int {
    digraph dg1{{{"a", "b", 1.2f}, {"a", "c", 2.2f}, {"c", "d", 4.2f}}};
    dg1.print();

    std::cout << "OK" << std::endl;
}
