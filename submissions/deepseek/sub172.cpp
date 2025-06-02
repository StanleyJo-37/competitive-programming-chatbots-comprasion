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
        vector<int> A(N);
        for (int i = 0; i < N; ++i) {
            cin >> A[i];
        }

        // Compute prefix sum for first processor and suffix sum for second processor
        vector<long long> prefix(N + 1, 0), suffix(N + 1, 0);
        for (int i = 0; i < N; ++i) {
            prefix[i + 1] = prefix[i] + A[i];
        }
        for (int i = N - 1; i >= 0; --i) {
            suffix[i] = suffix[i + 1] + A[i];
        }

        // Find the minimum of the maximum between prefix[i] and suffix[i] for all possible i
        long long min_time = max(prefix[N], suffix[0]); // Initialize with all tasks on one processor
        for (int i = 1; i <= N; ++i) {
            long long current_max = max(prefix[i], suffix[i]);
            if (current_max < min_time) {
                min_time = current_max;
            }
        }

        cout << min_time << '\n';
    }

    return 0;
}