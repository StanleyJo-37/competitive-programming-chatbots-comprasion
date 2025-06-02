#include <iostream>
#include <vector>
#include <algorithm>

// Function to check if a given time 'T' is achievable.
// This function determines if all dishes can be at Petya's home by time 'T'.
// The overall time is max(max_courier_delivery_time, total_petya_pickup_time).
// For a given T, we need to ensure both components are <= T.
//
// Logic for making choices:
// For each dish 'i':
// 1. If a_i > T and b_i > T: It's impossible to get this dish by time T. Return false.
// 2. If a_i <= T and b_i > T: Courier *must* deliver this dish. This choice is valid
//    because a_i <= T. This dish contributes to the maximum courier time, but since
//    we are checking for T, and a_i <= T, it doesn't violate the courier time constraint.
//    It does not add to Petya's pickup time.
// 3. If a_i > T and b_i <= T: Petya *must* pick up this dish. This choice is valid
//    because b_i <= T. This dish adds b_i to Petya's total pickup time.
// 4. If a_i <= T and b_i <= T: Petya has a choice. To minimize the overall time,
//    Petya should always choose the option that helps satisfy the constraints.
//    Since courier deliveries happen in parallel, if a_i <= T, choosing courier delivery
//    for this dish does not increase the maximum courier time beyond T.
//    However, Petya's pickup time is a sum. Every b_i added to it increases the total.
//    Therefore, to keep Petya's total pickup time as low as possible (and thus <= T),
//    Petya should prefer courier delivery for these dishes. This means this dish
//    does not add to Petya's pickup time.
//
// Based on this logic, we only accumulate b_i for dishes where Petya *must* pick them up.
bool check(long long T, int n, const std::vector<long long>& a, const std::vector<long long>& b) {
    long long current_pickup_time = 0; // Accumulates the time Petya spends picking up dishes.

    for (int i = 0; i < n; ++i) {
        if (a[i] > T && b[i] > T) {
            // Case 1: Both options take longer than T. Impossible to achieve T.
            return false;
        } else if (a[i] > T && b[i] <= T) {
            // Case 3: Courier delivery takes too long (a_i > T), but Petya can pick it up (b_i <= T).
            // Petya *must* pick up this dish. Add its time to Petya's total.
            current_pickup_time += b[i];
        }
        // Cases 2 and 4:
        // If a_i <= T (regardless of b_i's value relative to T), Petya can choose courier delivery.
        // As explained above, choosing courier delivery is always optimal in these cases
        // to minimize Petya's accumulated pickup time, because it doesn't violate the
        // courier time constraint (a_i <= T) and doesn't add to Petya's sequential sum.
        // So, no action is needed for current_pickup_time in these cases.
    }

    // After iterating through all dishes and making optimal choices,
    // check if Petya's total accumulated pickup time is within the allowed time T.
    return current_pickup_time <= T;
}

void solve() {
    int n;
    std::cin >> n;
    std::vector<long long> a(n);
    std::vector<long long> b(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    for (int i = 0; i < n; ++i) {
        std::cin >> b[i];
    }

    // Binary search for the minimum time 'T'.
    // The search space for 'T' ranges from 1 (minimum possible time, e.g., if n=1, a_1=1 or b_1=1)
    // up to a sufficiently large upper bound.
    // A safe upper bound is the maximum possible sum of all b_i values, which is
    // N * max(b_i) = 2 * 10^5 * 10^9 = 2 * 10^14.
    long long low = 1;
    long long high = 200000000000000LL; // 2 * 10^14, a safe upper bound.
    long long ans = high; // Initialize answer with a value that is definitely not the minimum.

    // Standard binary search loop.
    while (low <= high) {
        long long mid = low + (high - low) / 2; // Calculate mid to prevent potential overflow for (low + high).
        if (check(mid, n, a, b)) {
            // If 'mid' time is achievable, it means 'mid' is a possible answer.
            // We store 'mid' as a potential answer and try to find an even smaller time
            // by searching in the lower half of the range.
            ans = mid;
            high = mid - 1;
        } else {
            // If 'mid' time is not achievable, it means we need more time.
            // So, we search in the upper half of the range.
            low = mid + 1;
        }
    }

    // Output the minimum time found.
    std::cout << ans << std::endl;
}

int main() {
    // Optimize C++ standard streams for faster input/output.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams.
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads input.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t; // Read the number of test cases.
    while (t--) {
        solve(); // Solve each test case.
    }

    return 0;
}
