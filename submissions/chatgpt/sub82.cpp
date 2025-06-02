#include <bits/stdc++.h>
using namespace std;

// For each test case, we need to find the minimum number of breakfasts to change
// so that for all i, there is no j such that A_i >= A_j and C_i < C_j.
// This is equivalent to: if we sort by cost, the attractiveness must be strictly increasing.
// We can change A_i to any value in [L_i, R_i].
// The problem reduces to: find the minimum number of changes so that the sequence of A_i (after possible change in [L_i, R_i]) is strictly increasing in cost order.

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;

        // Each breakfast: {cost, attractiveness, L, R, original index}
        vector<tuple<int, int, int, int, int>> breakfasts(N);
        for (int i = 0; i < N; ++i) {
            int A, C, L, R;
            cin >> A >> C >> L >> R;
            breakfasts[i] = {C, A, L, R, i};
        }

        // Sort by cost (since costs are distinct, this is unique)
        sort(breakfasts.begin(), breakfasts.end());

        // For DP: dp[i] = minimal number of changes for first i+1 breakfasts, ending with i-th breakfast's attractiveness in [L_i, R_i]
        // But we can do greedy: try to keep as many original A_i as possible, i.e., find the longest strictly increasing subsequence
        // where A_i in [L_i, R_i], and for those not in the sequence, we must change.

        // We need to find the longest strictly increasing subsequence (LIS) of A_i, where A_i in [L_i, R_i]
        // For each position, we can either keep A_i (if possible), or change it to some value in [L_i, R_i]
        // But to minimize changes, we want to keep as many original A_i as possible, and for the rest, assign values in [L_i, R_i] to make the sequence strictly increasing.

        // Step 1: Find the LIS of original A_i in cost order
        vector<int> A(N), L(N), R(N);
        for (int i = 0; i < N; ++i) {
            tie(ignore, A[i], L[i], R[i], ignore) = breakfasts[i];
        }

        // To find LIS, we use patience sorting (O(N log N))
        // We need strictly increasing, so we use upper_bound
        vector<int> lis; // stores the last value of the increasing sequence of length i+1 at lis[i]
        vector<int> pos(N); // pos[i] = length of LIS ending at i (0-based)
        for (int i = 0; i < N; ++i) {
            // Only keep A[i] if it is in [L[i], R[i]]
            if (A[i] < L[i] || A[i] > R[i]) {
                pos[i] = -1; // cannot keep original
                continue;
            }
            // Find the position to insert A[i] in lis
            auto it = upper_bound(lis.begin(), lis.end(), A[i]);
            int idx = it - lis.begin();
            if (it == lis.end()) {
                lis.push_back(A[i]);
            } else {
                *it = A[i];
            }
            pos[i] = idx;
        }

        // The length of the LIS is the maximum value in pos + 1
        int max_lis = 0;
        for (int i = 0; i < N; ++i) {
            if (pos[i] != -1) max_lis = max(max_lis, pos[i] + 1);
        }

        // Now, we need to check if it's possible to assign values in [L_i, R_i] to the rest to make the sequence strictly increasing
        // We can do this greedily: assign the minimal possible value in [L_i, R_i] that is strictly greater than the previous value

        // Try to reconstruct the sequence with minimal changes
        int changes = 0;
        long long prev = LLONG_MIN;
        bool possible = true;
        for (int i = 0; i < N; ++i) {
            // If we can keep A[i] and it's strictly greater than prev, do so
            if (A[i] >= L[i] && A[i] <= R[i] && A[i] > prev) {
                prev = A[i];
                continue;
            }
            // Otherwise, try to assign the minimal value in [L[i], R[i]] that is > prev
            long long assign = max((long long)L[i], prev + 1);
            if (assign > R[i]) {
                possible = false;
                break;
            }
            prev = assign;
            ++changes;
        }

        if (!possible) {
            cout << -1 << '\n';
        } else {
            cout << changes << '\n';
        }
    }
    return 0;
}