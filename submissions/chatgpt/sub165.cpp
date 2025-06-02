#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); // Fast IO
    cin.tie(NULL);

    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        vector<long long> A(N + 1); // 1-based indexing

        for (int i = 1; i <= N; ++i) {
            cin >> A[i];
        }

        // Compute prefix sums: prefixSum[i] = sum of A[1] to A[i]
        vector<long long> prefixSum(N + 1, 0);
        for (int i = 1; i <= N; ++i) {
            prefixSum[i] = prefixSum[i - 1] + A[i];
        }

        // Compute suffix sums: suffixSum[i] = sum of A[i] to A[N]
        vector<long long> suffixSum(N + 2, 0); // N+2 to avoid out of bounds
        for (int i = N; i >= 1; --i) {
            suffixSum[i] = suffixSum[i + 1] + A[i];
        }

        // Find the minimum value of prefixSum(i) + suffixSum(i)
        long long minValue = LLONG_MAX;
        int minIndex = 1;
        for (int i = 1; i <= N; ++i) {
            long long value = prefixSum[i] + suffixSum[i];
            // If a new minimum is found, update minValue and minIndex
            if (value < minValue) {
                minValue = value;
                minIndex = i;
            }
            // If value equals minValue, keep the smallest index (already ensured by iterating from 1)
        }

        cout << minIndex << '\n';
    }
    return 0;
}