#include <iostream> // Required for input/output operations (cin, cout)
#include <vector>   // Required for std::vector
#include <numeric>  // Required for std::gcd (C++17)
#include <cmath>    // Required for std::log2 and std::abs
#include <algorithm> // Required for std::max

// Function to compute GCD of two long long numbers
long long calculate_gcd(long long a, long long b) {
    // std::gcd handles a=0 or b=0 correctly, returning the other number.
    // For positive integers, it's standard Euclidean algorithm.
    return std::gcd(a, b);
}

// Sparse table for range GCD queries.
// st[k][i] stores the GCD of the subarray starting at index 'i' with length 2^k.
std::vector<std::vector<long long>> st;
// log_table[i] stores floor(log2(i)). Used to quickly find 'k' for query length.
std::vector<int> log_table;

// Function to build the sparse table for a given array.
void build_sparse_table(const std::vector<long long>& arr) {
    int n = arr.size();
    // max_log is the maximum power of 2 needed, i.e., ceil(log2(n)).
    // For n=0, max_log should be 0. For n=1, max_log=1.
    // std::floor(std::log2(n)) gives k such that 2^k <= n.
    // We need up to 2^k where 2^k can cover the whole array.
    // If n=0, log2(0) is undefined. If n=1, log2(1)=0.
    // For n > 0, max_log = floor(log2(n)) + 1 is a safe upper bound for the number of levels.
    int max_log = (n == 0) ? 0 : std::floor(std::log2(n)) + 1; 
    st.assign(max_log, std::vector<long long>(n));
    log_table.assign(n + 1, 0);

    // Precompute log_table for O(1) query length calculation.
    // log_table[i] = floor(log2(i)).
    // log_table[1] is 0.
    for (int i = 2; i <= n; i++) {
        log_table[i] = log_table[i / 2] + 1;
    }

    // Base case: k=0, each element is its own GCD for a range of length 2^0 = 1.
    for (int i = 0; i < n; i++) {
        st[0][i] = arr[i];
    }

    // Fill the sparse table for k > 0.
    // st[k][i] is GCD of st[k-1][i] and st[k-1][i + 2^(k-1)].
    // This covers a range of length 2^k by combining two ranges of length 2^(k-1).
    for (int k = 1; k < max_log; k++) {
        for (int i = 0; i + (1 << k) <= n; i++) {
            st[k][i] = calculate_gcd(st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);
        }
    }
}

// Function to query GCD in a range [L, R] (inclusive).
long long query_gcd(int L, int R) {
    // If L > R, it's an invalid range. In this problem, L <= R is guaranteed by logic.
    // If L == R, the range has length 1, and its GCD is just the element itself.
    if (L == R) {
        return st[0][L];
    }
    // Calculate k such that 2^k is the largest power of 2 less than or equal to (R - L + 1).
    // This 'k' is used to select the appropriate level in the sparse table.
    int k = log_table[R - L + 1];
    // The GCD of range [L, R] is the GCD of two overlapping blocks of size 2^k.
    // The first block starts at L. The second block ends at R.
    return calculate_gcd(st[k][L], st[k][R - (1 << k) + 1]);
}

void solve() {
    int n;
    std::cin >> n; // Read the size of the array 'a'

    std::vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i]; // Read array elements
    }

    // If n=1, the only possible friend group has size 1 (the element itself).
    // This is the base case and minimum possible answer.
    if (n == 1) {
        std::cout << 1 << "\n";
        return;
    }

    // Define a new array 'c' where c[k] = |a[k] - a[k+1]|.
    // A subarray a[i...j] is a friend group if there exists m >= 2 such that
    // all elements have the same remainder modulo m.
    // This is equivalent to saying that m divides all differences |a[x] - a[y]| for x,y in [i,j].
    // Specifically, m must divide GCD(|a[i]-a[i+1]|, ..., |a[j-1]-a[j]|).
    // So, we are looking for the longest subarray c[i...j-1] such that its GCD is >= 2.
    // The length of the 'a' subarray (j - i + 1) will be (length of 'c' subarray) + 1.
    std::vector<long long> c(n - 1);
    for (int i = 0; i < n - 1; i++) {
        c[i] = std::abs(a[i] - a[i+1]);
    }

    // Build the sparse table for the 'c' array to enable efficient GCD queries.
    build_sparse_table(c);

    // Initialize max_friend_group_size to 1. A single element is always a friend group.
    int max_friend_group_size = 1;

    // Iterate through all possible starting points 'i' for the 'c' subarray.
    // The 'c' array has n-1 elements, indexed from 0 to n-2.
    for (int i = 0; i < n - 1; i++) {
        // Optimization: If c[i] is 1, then any GCD involving c[i] will be 1.
        // This means c[i] cannot be the start of a 'c' subarray whose GCD is >= 2.
        // Thus, we can skip this 'i' as it won't contribute to a friend group of size > 1.
        // The binary search below would correctly handle this case by finding no valid 'j',
        // but this check avoids unnecessary binary searches.
        if (c[i] == 1) {
            continue;
        }

        // For a fixed starting point 'i' in 'c', we use binary search to find the largest 'j'
        // (rightmost index in 'c') such that GCD(c[i...j]) is >= 2.
        int low = i;
        int high = n - 2; // The last valid index in the 'c' array.
        int current_max_j = i - 1; // Stores the rightmost index 'j' found so far for current 'i'.
                                   // Initialized to i-1 to indicate no valid 'j' found yet.

        while (low <= high) {
            int mid = low + (high - low) / 2; // Calculate mid-point to avoid overflow
            long long current_gcd = query_gcd(i, mid); // Query GCD for range c[i...mid]

            if (current_gcd >= 2) {
                // If the GCD is >= 2, this range c[i...mid] is valid.
                // We record 'mid' as a potential 'current_max_j' and try to extend the range further to the right.
                current_max_j = mid;
                low = mid + 1;
            } else {
                // If the GCD is 1, this range c[i...mid] is not valid.
                // We need to shrink the range from the right by moving 'high' to 'mid - 1'.
                high = mid - 1;
            }
        }

        // If a valid 'c' subarray was found (meaning current_max_j was updated to be >= i).
        if (current_max_j >= i) {
            // The length of the 'c' subarray is (current_max_j - i + 1).
            // The corresponding 'a' friend group has length (length of 'c' subarray) + 1.
            // Update the overall maximum friend group size found so far.
            max_friend_group_size = std::max(max_friend_group_size, (current_max_j - i + 1) + 1);
        }
    }

    std::cout << max_friend_group_size << "\n"; // Output the result for the current test case
}

int main() {
    // Optimize C++ standard streams for faster input/output.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard I/O.
    // std::cin.tie(NULL) prevents cin from flushing cout before each input operation.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t; // Read the number of test cases
    while (t--) {
        solve(); // Solve each test case
    }

    return 0; // Indicate successful execution
}
