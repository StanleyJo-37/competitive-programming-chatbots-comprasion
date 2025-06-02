#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

// Function to solve a single test case.
void solve() {
    int n;
    std::cin >> n;
    
    // pos[v] stores the 0-indexed position of value v in the permutation.
    // The vector is of size n+1 to handle values from 1 to n.
    std::vector<int> pos(n + 1);
    for (int i = 0; i < n; ++i) {
        int p_i;
        std::cin >> p_i;
        pos[p_i] = i;
    }

    // A permutation of size 1 is already sorted.
    if (n <= 1) {
        std::cout << 0 << std::endl;
        return;
    }
    
    // We identify the longest, centrally-located, contiguous block of numbers
    // that are already in sorted order in the permutation.
    // l and r are the values of the leftmost and rightmost elements of this block.
    // We start with the centermost elements.
    // For n=5, the center is 3. l=3, r=3.
    // For n=6, the center is 3 and 4. l=3, r=4.
    int l = (n + 1) / 2;
    int r = (n + 2) / 2;
    
    // If n is even, the initial block has two elements, l and r.
    // We must check if they are in the correct relative order.
    // If pos[l] > pos[r], we cannot keep them both. This means the largest
    // sorted central block has size 0. All n elements must be moved.
    // This requires n/2 operations, as each operation moves two elements.
    if (n % 2 == 0 && pos[l] > pos[r]) {
        std::cout << n / 2 << std::endl;
        return;
    }

    // Now, we know the initial block [l, r] is sorted. We expand outwards.
    // The loop continues as long as we can expand the block to [l-1, r+1]
    // while maintaining the sorted-position property.
    // We must ensure l-1 is positioned before l, and r is positioned before r+1.
    while (l > 1 && pos[l - 1] < pos[l] && pos[r] < pos[r + 1]) {
        l--;
        r++;
    }

    // The numbers that must be moved are {1, ..., l-1}.
    // There are l-1 such numbers on the left. By symmetry (since r = n-l+1),
    // there are also l-1 numbers on the right {r+1, ..., n}.
    // Total numbers to move = 2 * (l-1).
    // Since each operation moves two numbers, the minimum number of operations is l-1.
    std::cout << l - 1 << std::endl;
}

int main() {
    // Use fast I/O.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    
    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    
    return 0;
}