/*
What happens when you attempt to compile and run the following code?
*/

#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

using namespace std;

template <class T>
struct Out {
    ostream& out;

    Out(ostream& o) : out(o) {}

    void operator()(const T& val) { out << val << ""; }
};

int main() {
    int t1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int t2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vector<int> v1(t1, t1+10);
    vector<int> v2(t2, t2+10);
    vector<int> v3(10);
    transform(v1.begin(), v1.end(), v2.rbegin(), v3.end(), minus<int>());
    for_each(v3.rbegin(), v3.rend(), Out<int>(cout));
    cout << endl;
    return 0;
}
