#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Function to check if it's possible to keep max candies per day <= maxCandies
// with at most M balloons distributed in total
bool isPossible(const vector<long long>& A, const vector<long long>& B, long long N, long long M, long long maxCandies) {
    long long balloonsNeeded = 0;
    for (long long i = 0; i < N; ++i) {
        // If B[i] == 0, we never need to give candies, so skip
        if (B[i] == 0) continue;
        // For day i, to keep candies <= maxCandies, we must give at least:
        // A[i] - floor(maxCandies / B[i]) balloons (but not less than 0)
        long long maxCandiesPerDay = maxCandies / B[i];
        long long minBalloons = max(0LL, A[i] - maxCandiesPerDay);
        // We cannot give more balloons than A[i] (she doesn't want more)
        minBalloons = min(minBalloons, A[i]);
        balloonsNeeded += minBalloons;
        // If at any point we need more balloons than we have, return false
        if (balloonsNeeded > M) return false;
    }
    return balloonsNeeded <= M;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long N, M;
    cin >> N >> M;
    vector<long long> A(N), B(N);
    for (long long i = 0; i < N; ++i) cin >> A[i];
    for (long long i = 0; i < N; ++i) cin >> B[i];

    // Binary search for the minimum possible value of max(C1, ..., CN)
    // Lower bound: 0, Upper bound: max(A[i] * B[i]) over all i (worst case: no balloons given)
    long long left = 0, right = 0;
    for (long long i = 0; i < N; ++i) {
        right = max(right, A[i] * B[i]);
    }

    long long answer = right;
    while (left <= right) {
        long long mid = left + (right - left) / 2;
        if (isPossible(A, B, N, M, mid)) {
            // If possible, try to minimize further
            answer = mid;
            right = mid - 1;
        } else {
            // Otherwise, increase the allowed max candies
            left = mid + 1;
        }
    }

    cout << answer << '\n';
    return 0;
}