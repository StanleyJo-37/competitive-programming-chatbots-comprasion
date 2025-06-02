#include <iostream> // Required for input/output operations (cin, cout)
#include <vector>   // Required for using std::vector
#include <algorithm> // Required for std::sort

int main() {
    // Optimize C++ standard streams for faster input/output.
    // This is a common competitive programming optimization that unties C++ streams
    // from C standard streams and disables flushing of cout before cin.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    long long n, k, x; // Declare n, k, x as long long to handle potentially large values.
                       // n: number of initial students (up to 200,000, fits int, but long long is safe).
                       // k: number of additional students allowed (up to 10^18, requires long long).
                       // x: maximum allowed level difference (up to 10^18, requires long long).
    std::cin >> n >> k >> x; // Read the input values for n, k, and x.

    std::vector<long long> a(n); // Declare a vector 'a' of size 'n' to store the student levels.
                                 // Student levels can be up to 10^18, so use long long.
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i]; // Read each student's level into the vector.
    }

    // Sort the student levels in ascending order.
    // This is a crucial step because the stability condition for a group
    // (neighboring elements differ by at most x) applies to the *sorted* levels.
    // Sorting allows us to easily identify gaps between students that might require new groups or additional students.
    std::sort(a.begin(), a.end());

    std::vector<long long> costs_to_bridge_gaps; // This vector will store the number of additional students
                                                 // required to bridge each "large" gap found between existing students.

    // Initialize the number of groups.
    // If there are students (n >= 1), we start with 1 group.
    // Each time we encounter a gap between adjacent students that is too large (diff > x)
    // and cannot be bridged by adding students, it forces a new group.
    long long groups_count = 1; 

    // Iterate through the sorted student levels to identify gaps between adjacent students.
    // We compare a[i] with a[i+1] for i from 0 to n-2.
    for (int i = 0; i < n - 1; ++i) {
        // Calculate the difference between the current student's level and the next student's level.
        long long diff = a[i+1] - a[i];

        // If the difference is greater than 'x', it means these two students (a[i] and a[i+1])
        // cannot be in the same stable group without either forming a new group or
        // inviting additional students to bridge the gap.
        if (diff > x) {
            // This gap initially forces a new group, so we increment the group count.
            groups_count++;
            
            // Calculate the minimum number of additional students needed to bridge this gap.
            // If the difference is 'diff' and max allowed difference is 'x',
            // we need to cover 'diff - 1' units of difference using segments of size 'x'.
            // The number of students needed is (diff - 1) / x using integer division.
            // For example, if diff = 9 and x = 3, we need (9-1)/3 = 2 students (e.g., levels 1, 4, 7, 10).
            // The levels would be a[i], a[i]+x, a[i]+2x, ..., a[i+1].
            costs_to_bridge_gaps.push_back((diff - 1) / x);
        }
    }

    // Sort the costs to bridge gaps in ascending order.
    // This is a greedy approach: to minimize the total number of groups,
    // we should use our available 'k' additional students to bridge the "cheapest" gaps first.
    // Bridging a gap reduces the group count by one. By bridging cheaper gaps, we maximize
    // the number of groups we can merge (or splits we can avoid) with our limited 'k'.
    std::sort(costs_to_bridge_gaps.begin(), costs_to_bridge_gaps.end());

    // Iterate through the sorted costs to bridge gaps.
    for (long long cost : costs_to_bridge_gaps) {
        // If we have enough additional students ('k') to afford bridging the current gap ('cost').
        if (k >= cost) {
            k -= cost; // Deduct the cost from our budget of additional students.
            groups_count--; // Bridging this gap means we successfully merged two groups (or avoided a split),
                            // so we decrement the total number of groups.
        } else {
            // If we don't have enough students for the current gap,
            // we also won't have enough for any subsequent gaps (since they are sorted and thus larger or equal).
            // Therefore, we cannot bridge any more gaps and can stop.
            break;
        }
    }

    // Print the final calculated minimum number of stable groups.
    std::cout << groups_count << std::endl;

    return 0; // Indicate successful program execution.
}