// bfs
// https://leetcode.com/explore/learn/card/queue-stack/231/practical-application-queue/1375/

#include <cassert>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <vector>

std::vector<std::string> neighbors(const std::string& current) {
    std::vector<std::string> result;
    for (int i = 0; i < 4; i++) {
        int d = current[i] - '0';
        d++;
        d = d > 9 ? 0 : d;
        std::string s{current};
        s[i] = d + '0';
        result.push_back(s);
    }
    for (int i = 0; i < 4; i++) {
        int d = current[i] - '0';
        d--;
        d = d < 0 ? 9 : d;
        std::string s{current};
        s[i] = d + '0';
        result.push_back(s);
    }
    return result;
}

int openLock(const std::vector<std::string>& deadends, std::string target) {
    const std::vector<std::string> dead_ends{deadends.begin(), deadends.end()};
    if (dead_ends.count("0000"))
        return -1;
    std::queue<std::string> q;
    q.push("0000");
    std::vector<std::string> visited;
    visited.insert("0000");

    int count = 0;
    while (!q.empty()) {
        int size = q.size();
        for (int i = 0; i < size; i++) {
            std::string current = q.front();
            q.pop();
            if (current == target) {
                return count;
            }
            for (const std::string& neighbor : neighbors(current)) {
                if (dead_ends.count(neighbor))
                    continue;
                if (visited.count(neighbor))
                    continue;
                q.push(neighbor);
                visited.insert(neighbor);
            }
        }
        count++;
    }
    return -1;
}

int main() {
    assert(openLock({"0201", "0101", "0102", "1212", "2002"}, "0202") == 6);
    assert(openLock({"0000"}, "8888") == -1);
    std::cout << "OK" << std::endl;
}
