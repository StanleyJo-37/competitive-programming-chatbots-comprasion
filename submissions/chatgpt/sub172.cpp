#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); // Fast IO
    cin.tie(NULL);

    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        vector<long long> A(N);
        for (int i = 0; i < N; ++i) {
            cin >> A[i];
        }

        // Compute prefix sums for efficient range sum queries
        vector<long long> prefix(N + 1, 0); // prefix[0] = 0
        for (int i = 0; i < N; ++i) {
            prefix[i + 1] = prefix[i] + A[i];
        }

        long long min_time = LLONG_MAX;
        // Try all possible splits: assign first i tasks to processor 1, rest to processor 2
        // i ranges from 0 to N (0 means all to processor 2, N means all to processor 1)
        for (int i = 0; i <= N; ++i) {
            // Time taken by processor 1: sum of first i tasks
            long long time1 = prefix[i];
            // Time taken by processor 2: sum of remaining tasks
            long long time2 = prefix[N] - prefix[i];
            // The total time is the maximum of the two (since they work in parallel)
            long long total_time = max(time1, time2);
            if (total_time < min_time) {
                min_time = total_time;
            }
        }

        cout << min_time << '\n';
    }
    return 0;
}