#include <iostream> // Required for input/output operations (std::cin, std::cout, std::endl)
#include <vector>   // Required for using std::vector to store prefix sums
#include <numeric>  // Not strictly necessary as sum is calculated manually, but often useful for algorithms like std::accumulate

int main() {
    // Optimize C++ standard streams for competitive programming.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams,
    // which can significantly speed up I/O operations.
    // std::cin.tie(NULL) prevents std::cout from being flushed before each std::cin operation,
    // further improving performance for interactive problems or large I/O.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n; // Read the number of elements in the array.

    // Use std::vector<long long> for prefix sums.
    // The problem states array elements |a[i]| <= 10^9 and n <= 5*10^5.
    // The total sum can be up to 5*10^5 * 10^9 = 5*10^14, which exceeds the capacity of a 32-bit integer (int).
    // A 64-bit integer (long long) is required to store such large sums.
    // P[k] will store the sum of elements from a[1] to a[k] (1-based indexing as per problem).
    // P[0] is initialized to 0, representing the sum before the first element.
    std::vector<long long> P(n + 1, 0);

    // Calculate prefix sums.
    // The problem uses 1-based indexing for array 'a', so we iterate from k=1 to n.
    for (int k = 1; k <= n; ++k) {
        long long val;
        std::cin >> val; // Read the k-th element of the array.
        P[k] = P[k - 1] + val; // P[k] is the sum of a[1]...a[k].
    }

    // The total sum of the array is P[n].
    long long total_sum = P[n];

    // If the total sum is not divisible by 3, it's impossible to split the array
    // into three parts with equal sum. In this case, the answer is 0.
    if (total_sum % 3 != 0) {
        std::cout << 0 << std::endl;
        return 0;
    }

    // Calculate the target sum for each of the three parts.
    long long target_sum = total_sum / 3;

    // 'ans' will store the final count of ways to split the array.
    long long ans = 0;
    // 'count_first_part_sum' keeps track of how many valid end points for the first part
    // (i.e., indices 'k' where P[k] == target_sum) have been encountered so far.
    long long count_first_part_sum = 0;

    // Iterate through possible end points for the second part of the array.
    // Let 'j' be the 1-based index for the end of the second part.
    // The problem requires 2 <= i <= j <= n - 1.
    // This implies:
    // 1. The first part (a[1]...a[i-1]) must be non-empty, so i-1 >= 1.
    // 2. The second part (a[i]...a[j]) must be non-empty, so i <= j. This also means i-1 < j.
    // 3. The third part (a[j+1]...a[n]) must be non-empty, so j+1 <= n, which means j <= n-1.
    //
    // We are looking for pairs of indices (i-1, j) such that:
    // P[i-1] == target_sum (sum of first part)
    // P[j] - P[i-1] == target_sum (sum of second part) => P[j] == 2 * target_sum
    // P[n] - P[j] == target_sum (sum of third part) => P[j] == P[n] - target_sum == 3*target_sum - target_sum == 2*target_sum
    //
    // The loop for 'j' iterates from 1 to n-1.
    // When we are at index 'j':
    // - If P[j] == 2 * target_sum, it means the sum of elements from a[1] to a[j] is 2 * target_sum.
    //   This 'j' is a potential end point for the second part.
    //   For each such 'j', we need to count how many valid 'i-1' exist such that P[i-1] == target_sum AND i-1 < j.
    //   'count_first_part_sum' correctly stores the count of such 'i-1' values that have been processed *before* the current 'j'.
    //   So, we add 'count_first_part_sum' to 'ans'.
    // - If P[j] == target_sum, it means the sum of elements from a[1] to a[j] is target_sum.
    //   This 'j' is a potential end point for the first part.
    //   We increment 'count_first_part_sum' so that it can be used for future 'j'' values (where j' > j).
    // The order of these two 'if' statements is crucial: we must count valid first parts *before*
    // considering the current 'j' as a potential first part itself.
    for (int j = 1; j < n; ++j) { // 'j' iterates from 1 up to n-1 (inclusive).
                                  // The last element a[n] must be part of the third segment,
                                  // so the second segment cannot extend to n.
        if (P[j] == 2 * target_sum) {
            ans += count_first_part_sum;
        }

        if (P[j] == target_sum) {
            count_first_part_sum++;
        }
    }

    std::cout << ans << std::endl; // Print the final count of ways.

    return 0; // Indicate successful execution.
}