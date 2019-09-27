#include <cassert>

int main() {
  const char s[] = "\x0000000000a";
  assert(sizeof(s) == 2);
}
