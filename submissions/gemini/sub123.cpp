#include <iostream>
#include <vector>
#include <algorithm>
#include <string> // Required for std::string in __int128 output

// Custom input/output for __int128_t (GCC extension).
// This is necessary because standard iostream does not support __int128_t by default.
// It converts the 128-bit integer to a string for printing.
std::ostream& operator<<(std::ostream& os, __int128_t value) {
    if (value == 0) return os << "0"; // Handle zero case
    std::string s = "";
    bool negative = false;
    if (value < 0) { // Handle negative numbers
        negative = true;
        value = -value;
    }
    // Convert digits to characters in reverse order
    while (value > 0) {
        s += (value % 10) + '0';
        value /= 10;
    }
    if (negative) s += '-'; // Add negative sign if applicable
    std::reverse(s.begin(), s.end()); // Reverse the string to get correct order
    return os << s;
}

void solve() {
    int N, Q;
    std::cin >> N >> Q; // Read N (number of warriors) and Q (number of queries)
    std::vector<long long> P(N);
    for (int i = 0; i < N; ++i) {
        std::cin >> P[i]; // Read warrior powers
    }

    // Sort enemy powers in ascending order.
    // This is a crucial greedy step: fighting weaker enemies first maximizes remaining power.
    // This strategy ensures that if it's possible to defeat a certain number of enemies,
    // doing so in increasing order of power will leave us with the most power,
    // thus maximizing the chances of defeating more enemies.
    std::sort(P.begin(), P.end());

    // Precompute scaled prefix sums for the first ~60 warriors.
    // The power transformation is X_new = 2 * (X_old - P_i).
    // After defeating k warriors (P_0, ..., P_{k-1}), the initial power X_0 must satisfy:
    // X_0 > P_{k-1}/2^(k-1) + sum_{j=0 to k-2} (P_j / 2^j).
    // Let S_k = sum_{j=0 to k-1} (P_j / 2^j).
    // The condition to defeat k warriors is X_0 > P_{k-1}/2^(k-1) + S_{k-1}.
    // To avoid floating point issues and maintain precision, we scale all terms by 2^60.
    // 2^60 is chosen because P_j (up to 10^9) divided by 2^j becomes effectively 0 for j >= 60
    // (since 2^60 is much larger than 10^9). This means the sum S_k converges for k >= 60.
    // scaled_S_k[k] = sum_{j=0 to k-1} (P[j] * 2^(60-j)).
    // This sum can be large, so we use __int128_t (128-bit integer type).
    // The size of scaled_S_k is min(N, 60) + 1.
    // scaled_S_k[0] corresponds to 0 warriors killed (sum is 0).
    // scaled_S_k[k] corresponds to the sum for the first k warriors (P[0]...P[k-1]).
    // So, scaled_S_k[60] contains the sum for P[0]...P[59].
    std::vector<__int128_t> scaled_S_k(std::min(N, 60) + 1);
    scaled_S_k[0] = 0; // Base case: 0 warriors killed, sum is 0.

    // Populate the scaled_S_k array.
    // The loop iterates up to min(N, 60) because terms P[j] * 2^(60-j) become 0 for j >= 60.
    for (int i = 0; i < std::min(N, 60); ++i) {
        // scaled_S_k[i+1] accumulates the sum up to P[i].
        // P[i] is multiplied by 2^(60-i) to scale it correctly.
        scaled_S_k[i+1] = scaled_S_k[i] + ((__int128_t)P[i] << (60 - i));
    }

    // Process each query.
    for (int q = 0; q < Q; ++q) {
        long long X_initial;
        std::cin >> X_initial; // Read initial power for the current query

        // Scale initial power X_initial by 2^60 for comparison with scaled_S_k values.
        __int128_t X_scaled = (__int128_t)X_initial << 60;

        // Binary search for the maximum number of warriors 'k' that can be killed.
        // 'k' ranges from 0 to N.
        int low = 0, high = N;
        int max_killed = 0; // Stores the maximum number of warriors found so far

        while (low <= high) {
            int mid = low + (high - low) / 2; // mid is the number of warriors we are trying to kill.

            if (mid == 0) { // It's always possible to kill 0 warriors.
                max_killed = std::max(max_killed, mid);
                low = mid + 1; // Try to kill more warriors.
                continue;
            }
            
            // If mid is greater than N, it's an invalid number of warriors to try to kill.
            if (mid > N) {
                high = mid - 1; // Reduce the search range.
                continue;
            }

            bool possible = false;
            // The condition to kill 'mid' warriors is X_0 > P_{mid-1}/2^(mid-1) + S_{mid-1}.
            // In scaled form: X_scaled > (P[mid-1] << (60-(mid-1))) + scaled_S_k[mid-1].

            // Check if (mid-1) is within the range where P[j]/2^j terms are significant (0 to 59).
            if (mid - 1 < 60) {
                // Calculate the required scaled value for X_initial to defeat 'mid' warriors.
                // This includes the sum up to P[mid-2] (scaled_S_k[mid-1])
                // and the term for P[mid-1] (P[mid-1] << (60-(mid-1))).
                __int128_t required_val = scaled_S_k[mid-1];
                required_val += ((__int128_t)P[mid-1] << (60 - (mid-1)));
                
                if (X_scaled > required_val) {
                    possible = true;
                }
            } else { // mid-1 >= 60.
                // For j >= 60, P[j]/2^j is effectively 0 (since P_j <= 10^9).
                // This means P[mid-1]/2^(mid-1) is effectively 0.
                // Also, S_{mid-1} (sum up to P[mid-2]) converges to S_60 (sum up to P[59]).
                // So the condition simplifies to X_0 > S_60.
                // In scaled form: X_scaled > scaled_S_k[60].
                if (X_scaled > scaled_S_k[60]) {
                    possible = true;
                }
            }

            if (possible) {
                max_killed = std::max(max_killed, mid); // Update max_killed
                low = mid + 1; // Try to kill more warriors (search in upper half).
            } else {
                high = mid - 1; // Cannot kill 'mid' warriors, try fewer (search in lower half).
            }
        }
        std::cout << max_killed << "\n"; // Print the result for the current query
    }
}

int main() {
    // Optimize C++ standard streams for competitive programming.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams,
    // which can speed up I/O operations.
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads input,
    // further speeding up I/O.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int T;
    std::cin >> T; // Read the number of test cases
    while (T--) {
        solve(); // Solve each test case
    }

    return 0;
}
