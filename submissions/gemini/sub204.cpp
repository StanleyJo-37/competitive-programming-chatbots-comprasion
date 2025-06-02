#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    // Use maps to store counts of numbers at even and odd indices in the initial array.
    // Key: T-shirt number, Value: count
    std::map<int, int> initial_even_counts;
    std::map<int, int> initial_odd_counts;

    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
        // Check if the current index 'i' is even or odd.
        // Using 0-indexed positions: 0, 1, 2, 3, ...
        // Even indices: 0, 2, 4, ...
        // Odd indices: 1, 3, 5, ...
        if (i % 2 == 0) {
            initial_even_counts[a[i]]++;
        } else {
            initial_odd_counts[a[i]]++;
        }
    }

    // Create a sorted version of the array 'a'.
    std::vector<int> b = a;
    std::sort(b.begin(), b.end());

    // Use maps to store counts of numbers at even and odd indices in the sorted array.
    std::map<int, int> final_even_counts;
    std::map<int, int> final_odd_counts;

    for (int i = 0; i < n; ++i) {
        // Check if the current index 'i' is even or odd.
        if (i % 2 == 0) {
            final_even_counts[b[i]]++;
        } else {
            final_odd_counts[b[i]]++;
        }
    }

    // The core logic:
    // For each operation (swapping two adjacent friends), both chosen friends flip their directions.
    // Initially, all friends face 'right'. To end up facing 'right', each friend must have
    // flipped their direction an even number of times.
    //
    // Consider a specific friend 'F' who starts at initial position 'i' and ends up at final position 'j'.
    // Each time 'F' is involved in an adjacent swap, its direction flips.
    // When 'F' at position 'p' swaps with 'G' at 'p+1':
    // 'F' moves to 'p+1', 'G' moves to 'p'.
    // Both 'F' and 'G' flip their directions.
    // The parity of 'F's position changes from 'p % 2' to '(p+1) % 2'.
    // The number of times 'F' flips its direction is equal to the number of times it is involved in a swap.
    //
    // It is a known property that if an element moves from position 'i' to position 'j' through a sequence
    // of adjacent swaps, the parity of the number of swaps it is involved in is the same as the parity of (j - i).
    // That is, (number of swaps for F) % 2 == (j - i) % 2.
    //
    // For 'F' to end up facing 'right', it must have an even number of flips.
    // So, (j - i) % 2 must be 0, which means 'j' and 'i' must have the same parity.
    // (i.e., both even or both odd).
    //
    // This implies that a friend who starts at an even position must end up at an even position.
    // And a friend who starts at an odd position must end up at an odd position.
    //
    // Therefore, for each distinct T-shirt number 'V':
    // The count of friends with T-shirt number 'V' who start at an even position must be equal to
    // the count of positions requiring T-shirt number 'V' that are even in the sorted array.
    // Similarly, for odd positions.
    //
    // If these counts match for all T-shirt numbers, then it is possible. Otherwise, it is not.

    bool possible = true;
    // Compare the maps directly. std::map provides operator== which compares sizes and elements.
    // If initial_even_counts and final_even_counts are not identical, then it's impossible.
    // Same for odd counts.
    if (initial_even_counts != final_even_counts || initial_odd_counts != final_odd_counts) {
        possible = false;
    }

    // Print the result.
    if (possible) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }
}

int main() {
    // Optimize C++ standard streams for faster input/output.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
