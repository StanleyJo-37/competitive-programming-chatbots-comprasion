#include <iostream> // Required for input/output operations (cin, cout)
#include <vector>   // Required for using std::vector to store broken segment positions and gaps
#include <algorithm> // Required for std::sort to sort the gaps
#include <functional> // Required for std::greater to sort in descending order

int main() {
    // Optimize C++ standard streams for faster input/output.
    // This unties cin/cout from C's stdio and prevents flushing cout before cin.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n; // Number of broken segments
    long long m; // Total length of the stick (not directly used in calculation, but defines range for b_i)
    int k; // Maximum number of tape pieces allowed

    // Read n, m, and k from standard input
    std::cin >> n >> m >> k;

    // Create a vector to store the positions of broken segments.
    // Use long long for elements because b_i can be up to 10^9.
    std::vector<long long> b(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> b[i]; // Read each broken segment position
    }

    // The initial total length of tape required if we use only one piece.
    // This piece would cover from the first broken segment (b[0]) to the last (b[n-1]).
    // Its length is calculated as (last_position - first_position + 1).
    long long total_length = b[n - 1] - b[0] + 1;

    // If we are allowed to use more than one piece (k > 1), we can make "cuts" in the tape.
    // Each cut effectively splits a single large tape piece into two,
    // saving the length of the "gap" (unbroken segments) between the two segments where the cut is made.
    // The number of segments saved by a cut between b[i] and b[i+1] is (b[i+1] - b[i] - 1).
    // To minimize the total tape length, we should make cuts at the largest gaps.

    // Create a vector to store the lengths of these "gaps" (potential savings).
    // There are n-1 possible gaps between n broken segments.
    std::vector<long long> gaps;
    // Only calculate gaps if there's more than one broken segment.
    if (n > 1) {
        for (int i = 0; i < n - 1; ++i) {
            // Calculate the length of the gap between b[i] and b[i+1].
            // This is (b[i+1] - b[i] - 1).
            // For example, if b[i]=20, b[i+1]=30, the gap is 30-20-1 = 9 segments (21 to 29).
            gaps.push_back(b[i+1] - b[i] - 1);
        }

        // Sort the gaps in descending order.
        // This allows us to easily pick the largest gaps to maximize savings.
        std::sort(gaps.begin(), gaps.end(), std::greater<long long>());

        // We can make at most k-1 cuts.
        // Iterate through the sorted gaps and subtract the largest k-1 gaps from the total length.
        // The loop runs for min(k-1, number of gaps) times.
        // Since 1 <= k <= n, and there are n-1 gaps, we will iterate at most n-1 times.
        for (int i = 0; i < k - 1; ++i) {
            // Subtract the current largest gap from the total length.
            // This effectively means we are using a new tape piece for the segments after this gap,
            // thus no longer covering the segments in this gap.
            total_length -= gaps[i];
        }
    }
    // If n=1, there are no gaps, and total_length is correctly b[0]-b[0]+1 = 1.
    // The loop for gaps won't run, and total_length remains 1, which is correct.

    // Print the minimum total length of tape required.
    std::cout << total_length << std::endl;

    return 0; // Indicate successful execution
}