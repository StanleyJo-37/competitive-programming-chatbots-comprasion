#include <iostream>
#include <vector>
#include <algorithm>
#include <climits> // For LLONG_MIN, LLONG_MAX

// Global vectors for input arrays and segment trees.
// Using global variables simplifies passing them to recursive segment tree functions.
std::vector<long long> a_arr;
std::vector<long long> b_arr;
std::vector<long long> tree_max_a; // Segment tree for range maximum queries on array 'a'
std::vector<long long> tree_min_b; // Segment tree for range minimum queries on array 'b'

// Function to build the segment tree for maximum values of array 'a'.
// node: current node index in the segment tree array.
// start, end: range covered by the current node [start, end].
void build_max_a(int node, int start, int end) {
    if (start == end) {
        // Leaf node: stores the value of the array element.
        tree_max_a[node] = a_arr[start];
    } else {
        // Internal node: recursively build children and combine their results.
        int mid = start + (end - start) / 2; // Calculate mid-point to avoid overflow
        build_max_a(2 * node, start, mid); // Build left child
        build_max_a(2 * node + 1, mid + 1, end); // Build right child
        // The value for the current node is the maximum of its children's values.
        tree_max_a[node] = std::max(tree_max_a[2 * node], tree_max_a[2 * node + 1]);
    }
}

// Function to query maximum value in a range [l, r] from the segment tree for 'a'.
// node: current node index.
// start, end: range covered by the current node [start, end].
// l, r: query range [l, r].
long long query_max_a(int node, int start, int end, int l, int r) {
    // If the current node's range is completely outside the query range, return LLONG_MIN.
    // LLONG_MIN is used because it's the identity for max operation (won't affect the true max).
    if (r < start || end < l) {
        return LLONG_MIN;
    }
    // If the current node's range is completely inside the query range, return its stored value.
    if (l <= start && end <= r) {
        return tree_max_a[node];
    }
    // If the current node's range is partially inside/outside, recurse on children.
    int mid = start + (end - start) / 2;
    long long p1 = query_max_a(2 * node, start, mid, l, r); // Query left child
    long long p2 = query_max_a(2 * node + 1, mid + 1, end, l, r); // Query right child
    // Combine results from children.
    return std::max(p1, p2);
}

// Function to build the segment tree for minimum values of array 'b'.
// Similar logic to build_max_a, but uses min.
void build_min_b(int node, int start, int end) {
    if (start == end) {
        tree_min_b[node] = b_arr[start];
    } else {
        int mid = start + (end - start) / 2;
        build_min_b(2 * node, start, mid);
        build_min_b(2 * node + 1, mid + 1, end);
        tree_min_b[node] = std::min(tree_min_b[2 * node], tree_min_b[2 * node + 1]);
    }
}

// Function to query minimum value in a range [l, r] from the segment tree for 'b'.
// Similar logic to query_max_a, but uses min and LLONG_MAX as identity.
long long query_min_b(int node, int start, int end, int l, int r) {
    // LLONG_MAX is used because it's the identity for min operation.
    if (r < start || end < l) {
        return LLONG_MAX;
    }
    if (l <= start && end <= r) {
        return tree_min_b[node];
    }
    int mid = start + (end - start) / 2;
    long long p1 = query_min_b(2 * node, start, mid, l, r);
    long long p2 = query_min_b(2 * node + 1, mid + 1, end, l, r);
    return std::min(p1, p2);
}

int main() {
    // Optimize C++ standard streams for faster input/output.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n;

    // Resize vectors to accommodate 'n' elements.
    a_arr.resize(n);
    b_arr.resize(n);
    // Segment tree typically requires 4*N space for safety.
    tree_max_a.resize(4 * n);
    tree_min_b.resize(4 * n);

    // Read input arrays.
    for (int i = 0; i < n; ++i) {
        std::cin >> a_arr[i];
    }
    for (int i = 0; i < n; ++i) {
        std::cin >> b_arr[i];
    }

    // Build the segment trees. Root node is 1, covers range [0, n-1].
    build_max_a(1, 0, n - 1);
    build_min_b(1, 0, n - 1);

    long long total_count = 0; // Stores the final count of valid (l, r) pairs.
    int current_segment_start = 0; // Marks the beginning of the current valid segment.

    // Iterate through the array to find maximal contiguous segments where a_k <= b_k.
    for (int i = 0; i < n; ++i) {
        if (a_arr[i] > b_arr[i]) {
            // If a_i > b_i, this index breaks any valid range.
            // Process the segment [current_segment_start, i-1].
            if (current_segment_start <= i - 1) {
                int L = current_segment_start;
                int R = i - 1;
                
                // For each possible right endpoint 'r' in the current segment [L, R].
                for (int r = L; r <= R; ++r) {
                    // Binary search for the smallest 'l' (l_start_candidate) in [L, r]
                    // such that max(a[l...r]) >= min(b[l...r]).
                    int l_start_candidate = r + 1; // Initialize with an invalid index (one past 'r').
                    int low = L, high = r;
                    while (low <= high) {
                        int mid = low + (high - low) / 2;
                        long long max_val_a = query_max_a(1, 0, n - 1, mid, r);
                        long long min_val_b = query_min_b(1, 0, n - 1, mid, r);
                        if (max_val_a >= min_val_b) {
                            l_start_candidate = mid; // 'mid' is a possible start, try smaller 'l'.
                            high = mid - 1;
                        } else {
                            low = mid + 1; // 'mid' is too far right, need to move 'l' left.
                        }
                    }

                    // Check if the found l_start_candidate actually results in equality.
                    // If l_start_candidate is out of bounds or max_a != min_b at that point, no solution.
                    if (l_start_candidate <= r) {
                        long long max_val_a_at_start = query_max_a(1, 0, n - 1, l_start_candidate, r);
                        long long min_val_b_at_start = query_min_b(1, 0, n - 1, l_start_candidate, r);
                        if (max_val_a_at_start == min_val_b_at_start) {
                            int l_start = l_start_candidate;

                            // Binary search for the largest 'l' (l_end_candidate) in [l_start, r]
                            // such that max(a[l...r]) <= min(b[l...r]).
                            int l_end_candidate = l_start - 1; // Initialize with an invalid index (one before 'l_start').
                            low = l_start;
                            high = r;
                            while (low <= high) {
                                int mid = low + (high - low) / 2;
                                long long max_val_a = query_max_a(1, 0, n - 1, mid, r);
                                long long min_val_b = query_min_b(1, 0, n - 1, mid, r);
                                if (max_val_a <= min_val_b) {
                                    l_end_candidate = mid; // 'mid' is a possible end, try larger 'l'.
                                    low = mid + 1;
                                } else {
                                    high = mid - 1; // 'mid' is too far left, need to move 'l' right.
                                }
                            }
                            int l_end = l_end_candidate;
                            
                            // Add the count of valid 'l' values for this 'r' to the total.
                            total_count += (l_end - l_start + 1);
                        }
                    }
                }
            }
            current_segment_start = i + 1; // Start a new segment after this breaking point.
        }
    }

    // After the loop, process the last segment if it extends to the end of the array.
    if (current_segment_start <= n - 1) {
        int L = current_segment_start;
        int R = n - 1;
        for (int r = L; r <= R; ++r) {
            int l_start_candidate = r + 1;
            int low = L, high = r;
            while (low <= high) {
                int mid = low + (high - low) / 2;
                long long max_val_a = query_max_a(1, 0, n - 1, mid, r);
                long long min_val_b = query_min_b(1, 0, n - 1, mid, r);
                if (max_val_a >= min_val_b) {
                    l_start_candidate = mid;
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            }

            if (l_start_candidate <= r) {
                long long max_val_a_at_start = query_max_a(1, 0, n - 1, l_start_candidate, r);
                long long min_val_b_at_start = query_min_b(1, 0, n - 1, l_start_candidate, r);
                if (max_val_a_at_start == min_val_b_at_start) {
                    int l_start = l_start_candidate;

                    int l_end_candidate = l_start - 1;
                    low = l_start;
                    high = r;
                    while (low <= high) {
                        int mid = low + (high - low) / 2;
                        long long max_val_a = query_max_a(1, 0, n - 1, mid, r);
                        long long min_val_b = query_min_b(1, 0, n - 1, mid, r);
                        if (max_val_a <= min_val_b) {
                            l_end_candidate = mid;
                            low = mid + 1;
                        } else {
                            high = mid - 1;
                        }
                    }
                    int l_end = l_end_candidate;
                    total_count += (l_end - l_start + 1);
                }
            }
        }
    }

    // Print the final total count.
    std::cout << total_count << std::endl;

    return 0;
}
