#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false); // Fast IO
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        vector<int> A(N), B(N);
        for (int i = 0; i < N; ++i) cin >> A[i];
        for (int i = 0; i < N; ++i) cin >> B[i];

        // Precompute prefix sums for A and B
        vector<long long> prefixA(N+1, 0), prefixB(N+1, 0);
        for (int i = 0; i < N; ++i) {
            prefixA[i+1] = prefixA[i] + A[i];
            prefixB[i+1] = prefixB[i] + B[i];
        }

        // Try all possible move points: before day 1 (move at 0), after day N (move at N), or between any two days
        // For move at k (0 <= k <= N): first k days in Chefland, rest in Chefabad
        // Profit = sum_{i=1}^{k} A[i] + sum_{i=k+1}^{N} B[i]
        //         = prefixA[k] + (prefixB[N] - prefixB[k])
        long long maxProfit = 0;
        for (int k = 0; k <= N; ++k) {
            long long profit = prefixA[k] + (prefixB[N] - prefixB[k]);
            if (profit > maxProfit) maxProfit = profit;
        }
        cout << maxProfit << '\n';
    }
    return 0;
}