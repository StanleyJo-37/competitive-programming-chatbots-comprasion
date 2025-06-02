#include <iostream> // Required for standard input/output operations (cin, cout)
#include <vector>   // Required for using std::vector
#include <numeric>  // Required for std::iota (to initialize parent array efficiently)
#include <algorithm> // Required for std::max

// DSU (Disjoint Set Union) parent array.
// parent[i] stores the parent of element i. If parent[i] == i, then i is the representative of its set.
std::vector<int> parent;
// DSU segment sum array.
// segment_sum[i] stores the sum of elements in the contiguous segment whose representative is i.
std::vector<long long> segment_sum;

// Find operation with path compression.
// This function finds the representative (root) of the set containing element v.
int find_set(int v) {
    // If v is its own parent, it is the representative of its set.
    if (v == parent[v])
        return v;
    // Otherwise, recursively find the representative of its parent and apply path compression
    // by setting v's parent directly to the representative.
    return parent[v] = find_set(parent[v]);
}

// Union operation.
// This function merges the sets containing elements a and b.
void unite_sets(int a, int b) {
    // Find the representatives of the sets containing a and b.
    a = find_set(a);
    b = find_set(b);
    // If they are not already in the same set.
    if (a != b) {
        // Merge set b into set a by making a the parent of b's representative.
        // (This is a simple union without rank/size optimization, but path compression makes it efficient enough).
        parent[b] = a;
        // Add the sum of set b to the sum of set a.
        segment_sum[a] += segment_sum[b];
    }
}

int main() {
    // Optimize C++ standard streams for faster input/output.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams.
    // std::cin.tie(NULL) prevents cin from flushing cout before each input operation.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n;

    // Array 'a' stores the initial non-negative integers.
    // Using long long for elements to match problem constraints (up to 10^9).
    std::vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    // Permutation 'p' defines the order of elements to be destroyed.
    // The input is 1-indexed, so convert to 0-indexed immediately.
    std::vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> p[i];
        p[i]--; // Convert to 0-indexed
    }

    // Initialize DSU structures.
    // Resize parent vector to 'n' elements.
    parent.resize(n);
    // Use std::iota to initialize parent[i] = i for all i, meaning each element is initially in its own set.
    std::iota(parent.begin(), parent.end(), 0);

    // Initialize segment_sum vector to 'n' elements, all with value 0.
    // In the reverse process, elements are initially "destroyed" (not available), so their sums are 0.
    segment_sum.assign(n, 0);

    // 'is_available' tracks whether an element a[i] is currently "available" (not destroyed)
    // in the reverse process. Initially all elements are considered destroyed, so all are false.
    std::vector<bool> is_available(n, false);

    // 'max_overall_sum' keeps track of the maximum segment sum found so far during the reverse process.
    // It must be long long to accommodate sums up to 10^14.
    long long max_overall_sum = 0;

    // 'results' will store the answers for each step of the forward destruction process.
    // results[k] will store the maximum sum after (k+1) elements have been destroyed.
    std::vector<long long> results(n);

    // The state after all 'n' elements are destroyed (the last operation in the forward process)
    // results in an empty array of non-destroyed elements, so the maximum sum is 0.
    results[n - 1] = 0;

    // Process the destruction operations in reverse order.
    // The loop variable 'i' iterates from (n-1) down to 1.
    // p[i] is the (i+1)-th element to be destroyed in the original forward sequence.
    // When we process p[i] in reverse, we are "un-destroying" it, making it available.
    // This corresponds to the state *before* p[i] was destroyed in the forward sequence.
    // This state is after 'i' elements (p[0]...p[i-1]) have been destroyed.
    // So, the max_overall_sum at this point should be stored in results[i-1].
    for (int i = n - 1; i >= 1; --i) {
        int current_idx = p[i]; // Get the 0-indexed element that is being "un-destroyed"

        // Mark the current element as available.
        is_available[current_idx] = true;
        // Set its initial segment sum to its own value.
        segment_sum[current_idx] = a[current_idx];

        // Update the overall maximum sum. A single element can form a segment.
        max_overall_sum = std::max(max_overall_sum, segment_sum[current_idx]);

        // Check left neighbor:
        // If 'current_idx' is not the first element (current_idx > 0)
        // AND its left neighbor (current_idx - 1) is already available (was "un-destroyed" earlier).
        if (current_idx > 0 && is_available[current_idx - 1]) {
            // Unite the segment containing 'current_idx' with the segment containing 'current_idx - 1'.
            unite_sets(current_idx, current_idx - 1);
            // After uniting, update max_overall_sum with the sum of the newly merged segment.
            // The representative of 'current_idx' now holds the combined sum.
            max_overall_sum = std::max(max_overall_sum, segment_sum[find_set(current_idx)]);
        }

        // Check right neighbor:
        // If 'current_idx' is not the last element (current_idx < n - 1)
        // AND its right neighbor (current_idx + 1) is already available.
        if (current_idx < n - 1 && is_available[current_idx + 1]) {
            // Unite the segment containing 'current_idx' (which might have already merged with left neighbor)
            // with the segment containing 'current_idx + 1'.
            unite_sets(current_idx, current_idx + 1);
            // Update max_overall_sum with the sum of the newly merged segment.
            max_overall_sum = std::max(max_overall_sum, segment_sum[find_set(current_idx)]);
        }

        // Store the current max_overall_sum.
        // This max_overall_sum represents the state where elements p[i], p[i+1], ..., p[n-1] are available,
        // and elements p[0], ..., p[i-1] are destroyed.
        // This corresponds to the state after 'i' elements (p[0]...p[i-1]) have been destroyed in the forward process.
        // Since results[k] stores the answer after (k+1) destructions, we store it at results[i-1].
        results[i - 1] = max_overall_sum;
    }

    // Print the results for each step of the forward destruction process.
    // results[0] corresponds to the state after 1st destruction, results[1] after 2nd, ..., results[n-1] after n-th.
    for (int i = 0; i < n; ++i) {
        std::cout << results[i] << "\n";
    }

    return 0;
}