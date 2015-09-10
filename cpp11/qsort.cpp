#include <iostream>
#include <vector>

int partition(std::vector<int>& v, const int low, const int high) {
  int pivot = v[high];
  int i = low;
  for (int j = low; j < high; j++) {
    if (v[j] <= pivot) {
      std::swap(v[i], v[j]);
      i++;
    }
  }
  std::swap(v[i], v[high]);
  return i;
}

void quicksort(std::vector<int>& v, const int low, const int high) {
  if (low < high) {
    int p = partition(v, low, high);
    quicksort(v, low, p - 1);
    quicksort(v, p + 1, high);
  }
}


int main() {

  std::vector<int> v = { 4, 9, 1, 2, 5, 6, 0, 3 };

  quicksort(v, 0, 7);

  for (const int& x : v) {
    std::cout << x << " ";
  }
  std::cout << std::endl;

}
