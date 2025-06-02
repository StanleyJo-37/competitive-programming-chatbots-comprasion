#include <iostream>
#include <vector>
#include <numeric> // Required for std::all_of, though a manual loop is used for clarity and performance.
#include <algorithm> // Required for std::is_sorted, std::is_sorted_until, etc., but not directly used in the final O(N) solution.

int main() {
    // Optimize C++ standard streams for faster input/output.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams.
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads input.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n; // Read the number of elements in the array.

    std::vector<long long> a(n); // Declare a vector to store the array elements.
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i]; // Read array elements into the vector.
    }

    // Handle base cases where it's impossible to make the array unsorted.
    // 1. If n is 1: An array with one element is always considered sorted (both non-decreasing and non-increasing vacuously).
    //    There are no two distinct positions to swap.
    // 2. If n is 2: Let the array be [x, y].
    //    If x == y, Petya cannot swap equal integers, so no valid swap.
    //    If x != y, swapping them results in [y, x].
    //    Both [x, y] (if x < y, non-decreasing; if x > y, non-increasing) and [y, x] (if y < x, non-decreasing; if y > x, non-increasing)
    //    are always sorted. Thus, for n=2, it's impossible to make the array unsorted by a valid swap.
    if (n <= 2) {
        std::cout << -1 << std::endl;
        return 0; // Exit the program.
    }

    // Check if all elements in the array are identical.
    // The problem states: "Petya can not swap equal integers even if they are in distinct positions in the array."
    // If all elements are the same (e.g., [1, 1, 1]), then there are no two distinct integers to swap.
    // In this scenario, no valid swap can be performed, so the array cannot be made unsorted.
    bool all_elements_same = true;
    for (int i = 1; i < n; ++i) {
        if (a[i] != a[0]) {
            all_elements_same = false; // Found at least one element different from the first element.
            break; // No need to check further, not all elements are the same.
        }
    }

    if (all_elements_same) {
        std::cout << -1 << std::endl;
        return 0; // Exit the program.
    }

    // If n > 2 and not all elements are the same, a solution always exists.
    // The strategy is to find the first pair of adjacent elements (a[i], a[i+1]) that are different.
    // Swapping these two elements will always result in an unsorted array.
    //
    // Proof:
    // Since `n > 2` and `all_elements_same` is false, there must be at least one index `i`
    // such that `a[i] != a[i+1]`. (If `a[i] == a[i+1]` for all `i`, then `a[0] == a[1] == ... == a[n-1]`,
    // which contradicts `all_elements_same` being false).
    // Let `i` be the smallest such index.
    //
    // Consider swapping `a[i]` and `a[i+1]`. Let the new array be `A'`.
    //
    // Case 1: `a[i] < a[i+1]`
    //   - `A'` is not non-decreasing: After swapping, `A'[i] = a[i+1]` and `A'[i+1] = a[i]`.
    //     Since `a[i] < a[i+1]`, it implies `A'[i] > A'[i+1]`. This violates the non-decreasing property.
    //   - `A'` is not non-increasing: We need to find `k` such that `A'[k] < A'[k+1]`.
    //     If `i > 0`: Since `i` is the *first* index where `a[i] != a[i+1]`, it means `a[0] = a[1] = ... = a[i]`.
    //       So, `a[i-1] = a[i]`.
    //       In `A'`, we have `A'[i-1] = a[i-1] = a[i]` and `A'[i] = a[i+1]`.
    //       Since `a[i] < a[i+1]`, it means `A'[i-1] < A'[i]`. This violates the non-increasing property.
    //     If `i = 0`: This means `a[0] < a[1]`.
    //       In `A'`, `A'[0] = a[1]` and `A'[1] = a[0]`.
    //       Since `n > 2`, there exists `a[2]`. In the original array, `a[0] < a[1]`.
    //       If the original array was non-decreasing, `a[0] <= a[1] <= a[2]`.
    //       If `a[0] = a[2]`, then `a[0] < a[1] <= a[0]`, which is a contradiction.
    //       Therefore, `a[0] < a[2]` must be true.
    //       In `A'`, `A'[1] = a[0]` and `A'[2] = a[2]`.
    //       Since `a[0] < a[2]`, it means `A'[1] < A'[2]`. This violates the non-increasing property.
    //
    // Case 2: `a[i] > a[i+1]` (similar logic, just reversed inequalities)
    //   - `A'` is not non-increasing: After swapping, `A'[i] = a[i+1]` and `A'[i+1] = a[i]`.
    //     Since `a[i] > a[i+1]`, it implies `A'[i] < A'[i+1]`. This violates the non-increasing property.
    //   - `A'` is not non-decreasing: We need to find `k` such that `A'[k] > A'[k+1]`.
    //     If `i > 0`: Since `i` is the *first* index where `a[i] != a[i+1]`, it means `a[0] = a[1] = ... = a[i]`.
    //       So, `a[i-1] = a[i]`.
    //       In `A'`, we have `A'[i-1] = a[i-1] = a[i]` and `A'[i] = a[i+1]`.
    //       Since `a[i] > a[i+1]`, it means `A'[i-1] > A'[i]`. This violates the non-decreasing property.
    //     If `i = 0`: This means `a[0] > a[1]`.
    //       In `A'`, `A'[0] = a[1]` and `A'[1] = a[0]`.
    //       Since `n > 2`, there exists `a[2]`. In the original array, `a[0] > a[1]`.
    //       If the original array was non-increasing, `a[0] >= a[1] >= a[2]`.
    //       If `a[0] = a[2]`, then `a[0] > a[1] >= a[0]`, which is a contradiction.
    //       Therefore, `a[0] > a[2]` must be true.
    //       In `A'`, `A'[1] = a[0]` and `A'[2] = a[2]`.
    //       Since `a[0] > a[2]`, it means `A'[1] > A'[2]`. This violates the non-decreasing property.
    //
    // In all valid scenarios, swapping the first pair of adjacent distinct elements makes the array unsorted.

    for (int i = 0; i < n - 1; ++i) {
        if (a[i] != a[i+1]) {
            // Found the first pair of distinct adjacent elements.
            // Output their 1-indexed positions (i+1 and i+2) and exit.
            std::cout << i + 1 << " " << i + 2 << std::endl;
            return 0; // Exit the program after finding a valid pair.
        }
    }

    // This part of the code should theoretically be unreachable given the preceding logic.
    // If the loop completes without finding any `a[i] != a[i+1]`, it implies that
    // `a[0] == a[1] == ... == a[n-1]`, meaning all elements are identical.
    // This case is already handled by the `all_elements_same` check.
    // Therefore, this line would only be reached if there's a flaw in the problem statement's
    // guarantees or the analysis of edge cases.
    // For robustness in competitive programming, sometimes a final -1 is printed,
    // but based on the proof, it's not necessary here.
    return 0;
}