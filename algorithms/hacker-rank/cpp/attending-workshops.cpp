// https://www.hackerrank.com/challenges/attending-workshops/problem?isFullScreen=true

#include<bits/stdc++.h>

using namespace std;

//Define the structs Workshops and Available_Workshops.
struct Workshop {
    int start;
    int end;
    int duration;
};

struct Available_Workshops {
    Workshop* workshops;
    int n;
};

//Implement the functions initialize and CalculateMaxWorkshops
Available_Workshops* initialize (int start_time[], int duration[], int n) {
    Available_Workshops* aw = new Available_Workshops{};
    aw->workshops = new Workshop[n];
    for (int i = 0; i < n; ++i) {
        aw->workshops[i].start = start_time[i];
        aw->workshops[i].end = start_time[i] + duration[i];
        aw->workshops[i].duration = duration[i];
    }
    aw->n = n;
    return aw;
}

int CalculateMaxWorkshops(Available_Workshops* ptr) {
    Workshop* begin_array = &ptr->workshops[0];
    Workshop* end_array = &ptr->workshops[ptr->n];
    // sort by end date
    sort(begin_array, end_array, [](const Workshop& w1, const Workshop& w2) {
        return w1.end < w2.end;
    });
    int max = 0;
    int current_end_time = 0;
    for (int i = 0; i < ptr->n; i++) {
        if (ptr->workshops[i].start >= current_end_time) {
            max++;
            current_end_time = ptr->workshops[i].end;
        }
    }
    return max;
}

int main(int argc, char *argv[]) {
    int n; // number of workshops
    cin >> n;
    // create arrays of unknown size n
    int* start_time = new int[n];
    int* duration = new int[n];

    for(int i=0; i < n; i++){
        cin >> start_time[i];
    }
    for(int i = 0; i < n; i++){
        cin >> duration[i];
    }

    Available_Workshops * ptr;
    ptr = initialize(start_time,duration, n);
    cout << CalculateMaxWorkshops(ptr) << endl;
    return 0;
}
