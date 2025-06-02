#include <iostream> // Required for input/output operations (std::cin, std::cout)
#include <vector>   // Required for std::vector to store ground levels
#include <algorithm> // Required for std::max and std::min functions

// Function to solve a single test case
void solve() {
    int n;          // Number of sections in the fence
    long long k;    // Height of each section
    std::cin >> n >> k; // Read n and k

    // h stores the ground levels for each section.
    // Using long long for h_i to match k's type and for safety,
    // as h_i can be up to 10^8.
    std::vector<long long> h(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> h[i]; // Read ground levels
    }

    // current_min_b and current_max_b represent the minimum and maximum
    // possible base height for the current section being considered.
    // These values are updated iteratively.
    // For the first section (index 0), its base must be exactly h[0]
    // according to Rule 2 ("the first ... section should stand on the corresponding ground levels").
    long long current_min_b = h[0];
    long long current_max_b = h[0];

    // A boolean flag to track if it's possible to build the fence.
    bool possible = true;

    // Iterate from the second section (index 1) up to the last section (index n-1).
    // We determine the valid range for section 'i' based on section 'i-1' and its own ground rules.
    for (int i = 1; i < n; ++i) {
        // 1. Calculate the range for the current section (h[i]) based on the previous section's
        //    possible range [current_min_b, current_max_b].
        //    Rule 1: "consecutive sections should have a common side of length at least 1".
        //    This implies that if section (i-1) has base b_{i-1}, then section i's base b_i
        //    must satisfy: b_{i-1} - k + 1 <= b_i <= b_{i-1} + k - 1.
        //    So, if b_{i-1} is in [current_min_b, current_max_b], then b_i must be in:
        //    [current_min_b - k + 1, current_max_b + k - 1].
        long long next_min_b_from_prev = current_min_b - k + 1;
        long long next_max_b_from_prev = current_max_b + k - 1;

        // 2. Calculate the range for the current section (h[i]) based on its own ground level rules.
        long long next_min_b_from_rules = h[i];
        long long next_max_b_from_rules;

        if (i == n - 1) {
            // If this is the last section (index n-1), it must stand exactly on its ground level.
            // Rule 2: "...the last sections should stand on the corresponding ground levels".
            next_max_b_from_rules = h[i];
        } else {
            // For intermediate sections (1 < i < n), they can be on ground level or higher,
            // but not higher than k-1 from ground level.
            // Rule 3: "sections between may be either on the ground level or higher,
            // but not higher than k - 1 from the ground level h_i".
            // This means h_i <= b_i <= h_i + k - 1.
            next_max_b_from_rules = h[i] + k - 1;
        }

        // 3. Combine the constraints: The new possible range for the current section is the
        //    intersection of the range derived from the previous section and the range derived
        //    from its own ground rules.
        current_min_b = std::max(next_min_b_from_prev, next_min_b_from_rules);
        current_max_b = std::min(next_max_b_from_prev, next_max_b_from_rules);

        // 4. Check for impossibility: If at any point the minimum possible base height
        //    becomes greater than the maximum possible base height, it means there's no
        //    valid height for this section that satisfies all rules up to this point.
        //    Therefore, it's impossible to build the fence.
        if (current_min_b > current_max_b) {
            possible = false;
            break; // No need to check further sections
        }
    }

    // After iterating through all sections:
    // If 'possible' is still true, it means we successfully found a valid range for each section.
    // Specifically, for the last section, its required height h[n-1] was implicitly
    // within its calculated range because next_min_b_from_rules and next_max_b_from_rules
    // were both h[n-1], and if current_min_b <= current_max_b, it implies h[n-1] is valid.
    if (possible) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }
}

int main() {
    // Optimize C++ standard streams for faster input/output.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams.
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads input.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t; // Number of test cases
    std::cin >> t; // Read the number of test cases
    while (t--) {
        solve(); // Solve each test case
    }

    return 0; // Indicate successful execution
}
