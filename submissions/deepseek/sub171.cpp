#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        vector<int> A(N), B(N);
        for (int i = 0; i < N; ++i) {
            cin >> A[i];
        }
        for (int i = 0; i < N; ++i) {
            cin >> B[i];
        }

        // Compute prefix sum of A (sum of A[0..i])
        vector<int> prefixA(N + 1, 0);
        for (int i = 0; i < N; ++i) {
            prefixA[i + 1] = prefixA[i] + A[i];
        }

        // Compute suffix sum of B (sum of B[i..N-1])
        vector<int> suffixB(N + 1, 0);
        for (int i = N - 1; i >= 0; --i) {
            suffixB[i] = suffixB[i + 1] + B[i];
        }

        // The answer is the maximum of (prefixA[i] + suffixB[i]) for all i in 0..N
        int maxProfit = 0;
        for (int i = 0; i <= N; ++i) {
            maxProfit = max(maxProfit, prefixA[i] + suffixB[i]);
        }

        cout << maxProfit << '\n';
    }

    return 0;
}