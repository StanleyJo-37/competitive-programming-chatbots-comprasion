#include <iostream> // Required for input/output operations (cin, cout)
#include <vector>   // Required for using std::vector to store numbers and indices
#include <stack>    // Required for using std::stack for the monotonic stack logic
#include <algorithm> // Required for std::max function

int main() {
    // Optimize C++ standard streams for competitive programming.
    // This unties cin/cout from stdio and prevents flushing cout before cin.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int N;
    std::cin >> N; // Read the number of integers

    // Declare a vector 'a' of size N+1 to use 1-based indexing, matching the problem statement.
    // a[0] will be unused.
    std::vector<int> a(N + 1);
    for (int i = 1; i <= N; ++i) {
        std::cin >> a[i]; // Read the N integers into the vector
    }

    // 'left_indices[i]' will store the index j such that j < i, a[j] > a[i], and j is closest to i.
    // If no such j exists, left_indices[i] will be 0.
    std::vector<int> left_indices(N + 1, 0);
    std::stack<int> s; // Monotonic stack to find the next greater element to the left

    // Iterate from left to right (from index 1 to N) to find Left(i) for all i.
    // The stack will store indices of elements in decreasing order of their values.
    for (int i = 1; i <= N; ++i) {
        // While the stack is not empty AND the element at the index on top of the stack
        // is less than or equal to the current element a[i], pop from the stack.
        // This is because a[s.top()] is not strictly greater than a[i], so it cannot be Left(i).
        // Also, if a[s.top()] is not greater than a[i], it cannot be the closest greater element
        // for any future element k > i, because a[i] is closer and greater or equal.
        while (!s.empty() && a[s.top()] <= a[i]) {
            s.pop();
        }
        // If the stack is not empty after popping, the element at the top of the stack
        // is the closest element to the left that is strictly greater than a[i].
        if (!s.empty()) {
            left_indices[i] = s.top();
        }
        // Push the current index onto the stack.
        s.push(i);
    }

    // Clear the stack for reuse to find Right(i).
    // This ensures the stack is empty before the next pass.
    while (!s.empty()) {
        s.pop();
    }

    // 'right_indices[i]' will store the index k such that k > i, a[k] > a[i], and k is closest to i.
    // If no such k exists, right_indices[i] will be 0.
    std::vector<int> right_indices(N + 1, 0);

    // Iterate from right to left (from index N down to 1) to find Right(i) for all i.
    // The stack will store indices of elements in decreasing order of their values.
    for (int i = N; i >= 1; --i) {
        // While the stack is not empty AND the element at the index on top of the stack
        // is less than or equal to the current element a[i], pop from the stack.
        // Similar logic as for Left(i), but applied for elements to the right.
        while (!s.empty() && a[s.top()] <= a[i]) {
            s.pop();
        }
        // If the stack is not empty after popping, the element at the top of the stack
        // is the closest element to the right that is strictly greater than a[i].
        if (!s.empty()) {
            right_indices[i] = s.top();
        }
        // Push the current index onto the stack.
        s.push(i);
    }

    // Initialize max_product to 0. The product can be 0 if Left(i) or Right(i) is 0.
    // Use long long for max_product to prevent overflow, as N can be 10^5.
    // The maximum product can be (N-1) * (N-1) which is approximately 10^10,
    // exceeding the capacity of a 32-bit integer.
    long long max_product = 0;

    // Calculate IndexProduct(i) for each i and find the maximum.
    for (int i = 1; i <= N; ++i) {
        // Calculate the product for the current index i.
        // Cast to long long before multiplication to ensure the product is computed as long long.
        long long current_product = static_cast<long long>(left_indices[i]) * right_indices[i];
        // Update max_product if the current product is greater.
        max_product = std::max(max_product, current_product);
    }

    // Output the maximum IndexProduct found.
    std::cout << max_product << std::endl;

    return 0; // Indicate successful execution
}