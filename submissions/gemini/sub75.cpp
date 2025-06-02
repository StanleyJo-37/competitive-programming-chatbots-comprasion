#include <iostream>
#include <vector>
#include <algorithm>

// Function to check if it's possible to achieve a minimum distance of at least 'X'
// between any two marked numbers.
// M: The total number of integers in the circular arrangement (0 to M-1).
// N: The number of intervals.
// intervals: A vector of pairs, where each pair {L_i, R_i} represents an interval.
bool check(long long X, long long M, int N, const std::vector<std::pair<long long, long long>>& intervals) {
    // If the target minimum distance X is 0, it's always possible.
    // For example, we can just pick L_i for all intervals.
    if (X == 0) {
        return true;
    }

    // We use a greedy approach to determine if X is achievable.
    // We try to pick the first number A_1 as small as possible, i.e., L_1.
    // Then, for subsequent numbers A_i, we pick them as small as possible
    // while satisfying the minimum distance constraint (A_i >= A_{i-1} + X)
    // and the interval constraint (A_i >= L_i).
    // This strategy minimizes the "linear" distance A_N - A_1.
    // If even this minimal A_N - A_1 fails the circular distance check,
    // then no other choice (which would result in a larger A_N - A_1) can succeed.

    // Initialize the current chosen number (A_1) to the lower bound of the first interval.
    long long current_A = intervals[0].first;
    // Store this as the first point for the circular distance check later.
    long long first_A = current_A;

    // Iterate through the intervals starting from the second one.
    for (int i = 1; i < N; ++i) {
        // The next number A_i must be at least 'current_A + X' to satisfy the minimum distance.
        // It also must be within its own interval, so A_i >= L_i.
        // Therefore, A_i must be at least max(L_i, current_A + X).
        current_A = std::max(intervals[i].first, current_A + X);

        // After determining the minimum possible value for A_i,
        // check if it exceeds the upper bound R_i of its interval.
        // If it does, it means we cannot place A_i while maintaining the minimum distance X
        // and staying within the interval bounds, given the previous choices.
        // Since we chose A_1 as small as possible and subsequent A_j as small as possible,
        // any other valid sequence would only result in larger A_j values,
        // making it even harder to satisfy A_j <= R_j.
        // Thus, if current_A > R_i, X is not possible.
        if (current_A > intervals[i].second) {
            return false;
        }
    }

    // All numbers A_1, ..., A_N have been successfully placed within their intervals
    // and satisfy the linear distance constraint (A_i - A_{i-1} >= X).
    // Now, we must check the circular distance between the last chosen number (A_N, which is current_A)
    // and the first chosen number (A_1, which is first_A).
    // The circular distance is M - (A_N - A_1). This must be at least X.
    // This inequality can be rewritten as: A_N - A_1 <= M - X.
    if (current_A - first_A > M - X) {
        // If the linear distance A_N - A_1 is too large, meaning the wrap-around distance is too small,
        // then X is not possible.
        return false;
    }

    // If all checks pass, it means we found a valid set of A_i's for the given X.
    return true;
}

int main() {
    // Optimize C++ standard streams for faster input/output operations.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    long long M; // Total numbers in the circle
    int N;       // Number of intervals
    std::cin >> M >> N;

    // Read the N intervals.
    std::vector<std::pair<long long, long long>> intervals(N);
    for (int i = 0; i < N; ++i) {
        std::cin >> intervals[i].first >> intervals[i].second;
    }

    // The problem asks to maximize the minimum distance. This is a classic
    // "maximize the minimum" problem, which can be solved using binary search on the answer.
    // The possible range for the minimum distance X is [0, M/N].
    // M/N is the average distance if all N points were equally spaced.
    // The maximum possible distance between any two points on a circle is M/2.
    // So, M/N is a valid and tighter upper bound for the binary search.
    long long low = 0;
    long long high = M / N;
    long long ans = 0; // Stores the maximum possible minimum distance found so far.

    // Perform binary search.
    while (low <= high) {
        // Calculate mid-point to avoid potential overflow: low + (high - low) / 2.
        long long mid = low + (high - low) / 2;

        // Check if 'mid' distance is achievable.
        if (check(mid, M, N, intervals)) {
            // If 'mid' is achievable, it means we might be able to do even better.
            // Store 'mid' as a potential answer and try for a larger distance.
            ans = mid;
            low = mid + 1;
        } else {
            // If 'mid' is not achievable, it means 'mid' is too large.
            // We need to try a smaller distance.
            high = mid - 1;
        }
    }

    // Output the maximized minimum distance.
    std::cout << ans << std::endl;

    return 0;
}
