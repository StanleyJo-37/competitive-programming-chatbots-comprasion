#include <iostream> // Required for input/output operations (std::cin, std::cout)
#include <vector>   // Required for std::vector
#include <algorithm> // Required for std::sort, std::max, std::upper_bound

// Function to recursively generate all possible subsequence sums for a given range of the array.
// The sums are stored in the 'sums' vector.
// 'idx': current index in the array 'a' being considered.
// 'limit': the exclusive upper bound for indices in 'a' for this half.
// 'current_sum': the sum accumulated so far for the current subsequence.
// 'a': the original input array.
// 'sums': vector to store all generated subsequence sums.
void generate_sums(int idx, int limit, long long current_sum, const std::vector<int>& a, std::vector<long long>& sums) {
    // Base case: If we have considered all elements in the current half (reached the limit index),
    // add the current_sum to our list of sums and return.
    if (idx == limit) {
        sums.push_back(current_sum);
        return;
    }

    // Recursive step 1: Exclude the current element a[idx] from the subsequence.
    // Move to the next element without adding a[idx] to current_sum.
    generate_sums(idx + 1, limit, current_sum, a, sums);

    // Recursive step 2: Include the current element a[idx] in the subsequence.
    // Add a[idx] to current_sum and move to the next element.
    // Note: current_sum + a[idx] could exceed standard integer limits, so long long is used.
    generate_sums(idx + 1, limit, current_sum + a[idx], a, sums);
}

int main() {
    // Optimize C++ standard streams for faster input/output.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams,
    // allowing them to operate independently and potentially faster.
    // std::cin.tie(NULL) prevents std::cout from flushing before each std::cin operation,
    // which can speed up interactive problems but is generally good practice for competitive programming.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;          // Number of elements in the array.
    long long m;    // The modulo value.
    
    // Read n and m from standard input.
    std::cin >> n >> m;

    std::vector<int> a(n); // Declare a vector of size n to store array elements.
    // Read array elements from standard input.
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    // Implement the Meet-in-the-Middle strategy.
    // Divide the array into two halves.
    // n1: number of elements in the first half (from index 0 to n1-1).
    // n2: number of elements in the second half (from index n1 to n-1).
    int n1 = n / 2;
    int n2 = n - n1; // This ensures n1 + n2 = n

    // sums1 will store all possible subsequence sums from the first half.
    std::vector<long long> sums1;
    // Call generate_sums for the first half, starting from index 0 up to n1 (exclusive limit).
    generate_sums(0, n1, 0, a, sums1);

    // sums2 will store all possible subsequence sums from the second half.
    std::vector<long long> sums2;
    // Call generate_sums for the second half, starting from index n1 up to n (exclusive limit).
    generate_sums(n1, n, 0, a, sums2);

    // Sort sums2 to enable efficient searching using std::upper_bound.
    // This is crucial for the combination step's performance.
    std::sort(sums2.begin(), sums2.end());

    // Initialize max_mod_sum to 0. The empty subsequence sum is 0, and 0 % m is 0.
    // This also covers the case where the optimal sum is 0.
    long long max_mod_sum = 0;

    // Iterate through each sum s1 generated from the first half.
    for (long long s1 : sums1) {
        // First, update max_mod_sum with s1 % m. This covers cases where the optimal s2 is 0
        // (i.e., the empty subsequence from the second half is chosen, or s2 itself is 0).
        max_mod_sum = std::max(max_mod_sum, s1 % m);

        // We want to find an s2 from sums2 such that (s1 + s2) % m is maximized.
        // This can be broken down into two main scenarios for s1 + s2:

        // Scenario 1: s1 + s2 results in a sum less than m.
        // In this case, (s1 + s2) % m = s1 + s2.
        // To maximize this, we need to find the largest s2 such that (s1 % m) + s2 < m.
        // Let current_s1_mod_m = s1 % m. We are looking for s2 such that s2 < m - current_s1_mod_m.
        // Or, equivalently, s2 <= m - 1 - current_s1_mod_m.
        long long current_s1_mod_m = s1 % m;
        long long target_for_s2 = m - 1 - current_s1_mod_m;

        // Use std::upper_bound to find an iterator to the first element in sums2 that is strictly greater than target_for_s2.
        auto it = std::upper_bound(sums2.begin(), sums2.end(), target_for_s2);

        // If 'it' is not the beginning of sums2, it means there is at least one element
        // in sums2 that is less than or equal to target_for_s2.
        // The element just before 'it' (pointed to by std::prev(it)) is the largest such s2.
        if (it != sums2.begin()) {
            long long s2_candidate = *std::prev(it); // Get the largest s2 <= target_for_s2
            // Update max_mod_sum with the sum (s1 + s2_candidate) % m.
            // Since we chose s2_candidate such that (s1 % m) + s2_candidate < m,
            // (s1 + s2_candidate) % m simplifies to (s1 % m) + s2_candidate.
            max_mod_sum = std::max(max_mod_sum, (current_s1_mod_m + s2_candidate));
        }

        // Scenario 2: s1 + s2 results in a sum greater than or equal to m.
        // In this case, (s1 + s2) % m = s1 + s2 - k*m for some integer k.
        // To maximize (s1 + s2) % m, we want to maximize s1 + s2.
        // This means picking the largest possible s2 from sums2.
        // sums2.back() gives the largest sum in sums2 (since it's sorted).
        // sums2 is guaranteed not to be empty because generate_sums always adds 0 for the empty subsequence.
        max_mod_sum = std::max(max_mod_sum, (s1 + sums2.back()) % m);
    }

    // Print the maximum possible value of sum % m.
    std::cout << max_mod_sum << std::endl;

    return 0; // Indicate successful execution.
}