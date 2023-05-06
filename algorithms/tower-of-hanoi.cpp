// Hanoi tower
// Tower of Hanoi is a mathematical puzzle where we have three rods (A, B, and C) and N disks.
// Initially, all the disks are stacked in decreasing value of diameter i.e., the smallest disk is
// placed on the top and they are on rod A. The objective of the puzzle is to move the entire stack
// to another rod (here considered C), obeying the following simple rules:
//
// - Only one disk can be moved at a time.
// - Each move consists of taking the upper disk from one of the stacks and placing it on top of
//   another stack i.e. a disk can only be moved if it is the uppermost disk on a stack.
// - No disk may be placed on top of a smaller disk.

#include <iostream>

auto hanoi(int n, char from, char to, char aux) -> void {
    if (n == 0) return;
    // std::cout << "aux " << n << " " << from << " " << to << std::endl;
    hanoi(n-1, from, aux, to);
    std::cout << "Move " << n << " " << from << " " << to << std::endl;
    hanoi(n-1, aux, to, from);
}

auto main() -> int {
    hanoi(4, 'A', 'C', 'B');
}
