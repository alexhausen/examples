#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

class Component {
public:
    Component(int order) : order_(order) {
    }

    bool operator <(const Component& other) const {
        return order_ < other.order_;
    }

private:
    int order_;

    friend std::ostream& operator<<(std::ostream&, const Component&);
};

std::ostream& operator<<(std::ostream& stream, const Component& ob) {
    stream << "{" << ob.order_ << "}";
}

typedef std::vector<std::shared_ptr<Component>> SharedComponentVector;

void print_components(const SharedComponentVector& components) {
    for (const auto& component: components) {
        if (component) {
            std::cout << *component << " ";
        } else {
            std::cout << "{-} ";
        }
    }
    std::cout << std::endl;
}

void remove_null_components(SharedComponentVector& components) {
    auto it = std::remove_if(components.begin(), components.end(),
                             [&] (std::shared_ptr<Component> c) { return c.get() == nullptr; });
    components.erase(it, components.end());
}

//(stable) sort elements
void sort_components(SharedComponentVector& components) {
    std::stable_sort(components.begin(), components.end(),
                     [&] (std::shared_ptr<Component> a, std::shared_ptr<Component> b) { return a && b ? *a < *b : false; });
}

int main() {
    SharedComponentVector components = {
        std::make_shared<Component>(23),
        std::make_shared<Component>(21),
        std::make_shared<Component>(22),
        std::shared_ptr<Component>(),
        std::shared_ptr<Component>(),
        std::make_shared<Component>(22),
    };

    print_components(components);
    sort_components(components);
    print_components(components); //output {21} {22} {23} {-} {-} {22}
    remove_null_components(components);
    sort_components(components);
    print_components(components); //output {21} {22} {22} {23}

    return 0;
}
