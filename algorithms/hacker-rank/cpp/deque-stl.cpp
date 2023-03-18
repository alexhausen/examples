// https://www.hackerrank.com/challenges/deque-stl/problem?isFullScreen=true
// https://www.geeksforgeeks.org/sliding-window-maximum-maximum-of-all-subarrays-of-size-k/

#include <deque>
#include <iostream>
using namespace std;

// remove indexes of the smaller elements (back to front)
// until we find an element > current
void remove_smaller_elements(deque<int>& d,
                              int current_element,
                              const int arr[]) {
    while (!d.empty() && current_element >= arr[d.back()]) {
        d.pop_back();
    }
}

// remove indexes that fall out of the windows (front to back)
void remove_indexes_out_of_window(deque<int>& d,
                                  int current_index,
                                  int window_size) {
    int min_index = current_index - window_size;
    while (!d.empty() && d.front() <= min_index) {
        d.pop_front();
    }
}

void printKMax(int arr[], int n, int k) {
    deque<int> d; // window (deque) with indexes of interest (larger at front)

    // initialize deque with the window of index of the elements,
    // keeping only the (index of the) larger ones (in the front)
    for (int i = 0; i < k; i++) {
        remove_smaller_elements(d, arr[i], arr);
        d.push_back(i);
    }

    for (int i = k; i < n; i++) {
        // the larger is always in the front of the deque
        int max = arr[d.front()];
        cout << max << " ";
        // remove indexes out of the window
        remove_indexes_out_of_window(d, i, k);
        // remove smaller elements again
        remove_smaller_elements(d, arr[i], arr);
        d.push_back(i);
    }

    // last maximum element of the last window
    cout << arr[d.front()] << endl;
}

int main() {
    int t;
    cin >> t;
    while (t > 0) {
        int n, k;
        cin >> n >> k;
        int i;
        int arr[n];
        for (i = 0; i < n; i++)
            cin >> arr[i];
        printKMax(arr, n, k);
        t--;
    }
    return 0;
}

/*stdin:
    2
    5 2
    3 4 6 3 4
    7 4
    3 4 5 8 1 4 10

*/
