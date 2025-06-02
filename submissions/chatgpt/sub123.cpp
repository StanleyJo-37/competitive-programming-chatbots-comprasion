#include <bits/stdc++.h>
using namespace std;

// Fast IO for large input/output
ios_base::sync_with_stdio(false);
cin.tie(NULL);

int main() {
    int T;
    cin >> T;
    while (T--) {
        int N, Q;
        cin >> N >> Q;
        vector<int> P(N);
        for (int i = 0; i < N; ++i) cin >> P[i];
        // Sort the enemy powers in ascending order for greedy approach
        sort(P.begin(), P.end());

        // For each query, simulate the process
        while (Q--) {
            long long X;
            cin >> X;
            int cnt = 0;
            long long curr = X;
            // Use a visited array to avoid modifying P for each query
            // Instead, use a pointer to the first un-killable enemy
            int i = 0;
            // Use a min-heap to simulate the process efficiently
            // But since we always want to fight the weakest available, sorted array is enough
            // Try to kill as many as possible in order
            while (i < N && curr > P[i]) {
                // If current power is greater than enemy's, kill and update power
                curr = 2 * (curr - P[i]);
                ++cnt;
                ++i;
            }
            cout << cnt << '\n';
        }
    }
    return 0;
}