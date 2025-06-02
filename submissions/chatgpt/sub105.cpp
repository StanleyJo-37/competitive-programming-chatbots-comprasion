#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Fast input/output for large constraints
ios_base::sync_with_stdio(false);
cin.tie(NULL);

int main() {
    int T;
    cin >> T;
    // Since sum of N over all test cases <= 2e5, we can reuse a vector
    vector<int> A;
    while (T--) {
        int N;
        long long X;
        cin >> N >> X;
        A.resize(N);
        for (int i = 0; i < N; ++i) {
            cin >> A[i];
        }
        // The minimum time required is the maximum of:
        // 1. The minimum time to process all admins in any shop (ceil(X / A[i]) for each shop)
        // 2. The minimum time to process all shops for each admin (N shops, so at least N hours if only one admin)
        // But since each admin must visit all shops, and each shop can process at most A[i] admins per hour,
        // for each shop, the minimum hours needed for all admins to visit it is ceil(X / A[i])
        // The answer is the maximum of these values over all shops
        long long min_time = 0;
        for (int i = 0; i < N; ++i) {
            // Calculate ceil(X / A[i]) without floating point
            long long t = (X + A[i] - 1) / A[i];
            if (t > min_time) min_time = t;
        }
        // The answer is the maximum of min_time and N (since each admin must visit all N shops)
        // But actually, min_time already accounts for the bottleneck shop, and N is not a lower bound
        // (since with enough capacity, all admins can finish in 1 hour for each shop, so N hours total)
        // But the correct answer is the maximum of min_time and N, because:
        // - If there are more shops than the bottleneck time, admins must visit all shops (N hours)
        // - If the bottleneck shop takes more time, that's the limiting factor
        // But actually, each admin must visit all N shops, and each shop can process at most A[i] admins per hour,
        // so the minimum time is max over all shops of ceil(X / A[i])
        // So, the answer is max(min_time, N) only if X < N * min(A[i]), but the correct answer is just max(min_time, N)
        // Let's check the sample input to confirm:
        // For test case 1: N=2, X=3, A=[3,3] => ceil(3/3)=1 for both, so min_time=1, but answer is 2 (N)
        // So, the answer is max(min_time, N)
        cout << max(min_time, (long long)N) << '\n';
    }
    return 0;
}