/*
 Observer pattern implementation.
*/
#include <functional>
#include <memory>
#include <vector>

template <typename T, typename... A>
class Observable {
  using F = std::function<void(A... args)>;

 public:
  void attach(std::weak_ptr<F> f) { slot.push_back(f); }

  void notify(A... args) const {
    for (const auto& fwp : slot) {
      if (auto fp = fwp.lock()) {
        F& f = *fp;
        f(args...);
      }
    }
  }

 private:
  // NOTE: replace std::vector by boost::signals2 to gain thread safety and
  // expired shared pointers tracking
  std::vector<std::weak_ptr<F>> slot;
};
