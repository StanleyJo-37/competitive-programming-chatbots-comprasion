#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <functional> // Not strictly needed for default std::priority_queue (max-heap)

void solve() {
    int n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    std::vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    long long total_magazines = 0;
    // A max-priority queue to store magazine counts of boxes that are
    // currently "candidates" to be covered by an available lid.
    // The elements in this priority queue represent the 'a_j' values of boxes 'j'
    // that are either:
    // 1. Boxes 'k' (where s[k] == '0') that are waiting for a lid from 'k+1'.
    //    When we are at index 'i', if s[i] == '1', this lid can potentially cover
    //    any such 'k < i' if 'k+1' is 'i'.
    // 2. Boxes 'k' (where s[k] == '1') whose own lid is still available to cover 'k'.
    //    When we are at index 'i', if s[i] == '1', this lid can potentially cover 'i'.
    // The crucial rule is that a lid at box 'i' can only cover box 'i' or box 'i-1'.
    // This means a lid can only affect boxes at its current position or to its left.
    // By iterating from left to right (i = 0 to n-1), when we encounter a lid at 'i',
    // all boxes 'j <= i' that could potentially be covered by this lid (or by a lid
    // from 'j' that could have moved to 'j-1', etc.) are already considered.
    std::priority_queue<long long> pq; 

    for (int i = 0; i < n; ++i) {
        if (s[i] == '0') {
            // If box i has no lid, it cannot provide a lid.
            // It can only be covered by a lid from box (i+1).
            // So, a_i is a potential candidate for a future lid (specifically, from i+1).
            // We add it to the priority queue of candidates.
            pq.push(a[i]);
        } else { // s[i] == '1'
            // If box i has a lid, this lid can cover box i (value a_i)
            // or box (i-1) (value a_{i-1}).
            // The lid at box i can cover box i. So a_i is a candidate.
            // We add a_i to the priority queue of candidates.
            pq.push(a[i]);

            // Now, we have a lid at box i. We must use this lid.
            // The priority queue 'pq' now contains all 'a_j' values for boxes 'j <= i'
            // that are currently "available" to be covered by a lid.
            // We have one lid (from box i) to assign. To maximize the total magazines,
            // we should use this lid to cover the box with the maximum value among
            // all currently available candidates in 'pq'.
            // So, we take the largest value from 'pq' (which is pq.top() for a max-heap),
            // add it to our total, and remove it from the candidates.
            if (!pq.empty()) {
                total_magazines += pq.top();
                pq.pop();
            }
        }
    }
    
    // After iterating through all boxes, any remaining elements in 'pq' are
    // '0' boxes that were never covered by a lid from their right, or '1' boxes
    // whose lids were never used. These cannot be covered, so they don't contribute
    // to the total_magazines. The logic correctly handles this by only adding to
    // total_magazines when a lid is available and assigned.

    std::cout << total_magazines << std::endl;
}

int main() {
    // Optimize C++ standard streams for competitive programming.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
