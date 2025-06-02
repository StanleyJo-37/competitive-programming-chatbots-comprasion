#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Structure to store intervals
struct Interval {
    int L, R;
    // For sorting intervals by L
    bool operator<(const Interval& other) const {
        return L < other.L;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int N, M;
        cin >> N >> M;

        vector<Interval> intervals(N);
        for (int i = 0; i < N; ++i) {
            cin >> intervals[i].L >> intervals[i].R;
        }

        // Sort intervals by starting time
        sort(intervals.begin(), intervals.end());

        // For binary search, we need a vector of Ls and Rs
        vector<int> Ls(N), Rs(N);
        for (int i = 0; i < N; ++i) {
            Ls[i] = intervals[i].L;
            Rs[i] = intervals[i].R;
        }

        // Process each query
        for (int i = 0; i < M; ++i) {
            int P;
            cin >> P;

            // Find the first interval whose R > P (i.e., interval that could contain P or is after P)
            // lower_bound on Ls to find the first interval with L >= P
            auto it = lower_bound(Ls.begin(), Ls.end(), P);

            int wait_time = -1;

            // Check if P is inside the previous interval (if any)
            if (it != Ls.begin()) {
                int idx = it - Ls.begin() - 1;
                // If P in [L, R)
                if (P >= Ls[idx] && P < Rs[idx]) {
                    wait_time = 0;
                }
            }

            // If not inside any interval, check if next interval is after P
            if (wait_time == -1) {
                if (it == Ls.end()) {
                    // No more intervals after P
                    wait_time = -1;
                } else {
                    // Next interval starts at Ls[it - Ls.begin()]
                    wait_time = Ls[it - Ls.begin()] - P;
                }
            }

            cout << wait_time << '\n';
        }
    }
    return 0;
}