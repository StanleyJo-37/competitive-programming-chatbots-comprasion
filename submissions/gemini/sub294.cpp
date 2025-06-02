#include <iostream>
#include <vector>
#include <stack>
#include <algorithm> // For std::max

int main() {
    // Optimize C++ standard streams for competitive programming.
    // This unties cin/cout from stdio and prevents flushing of cout before cin.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n; // Read the number of elements in the sequence.

    std::vector<int> s(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> s[i]; // Read the sequence elements.
    }

    long long max_lucky_number = 0; // Initialize the maximum lucky number found so far.
                                    // The maximum possible value for s_i is 10^9.
                                    // The bitwise XOR of two numbers up to 10^9 will also fit within a 32-bit signed integer (int).
                                    // For example, 2^29 XOR (2^29 - 1) is (2^30 - 1), which is less than 2*10^9.
                                    // Using long long is a safe practice to avoid overflow issues, though int would suffice here.

    std::stack<int> st; // Monotonic stack to store indices of elements.
                        // The stack will maintain indices `j` such that `s[j]` values are in strictly decreasing order from bottom to top.
                        // This means `s[st.bottom()] > s[st.bottom()+1] > ... > s[st.top()]`.

    // Iterate through the sequence from left to right.
    for (int i = 0; i < n; ++i) {
        // Phase 1: Process elements smaller than s[i] that are currently on the stack.
        // While the stack is not empty and the element at the top of the stack (s[st.top()]) is smaller than the current element s[i]:
        // This condition implies that s[i] is the "next greater element" to the right for s[st.top()].
        // Let `j = st.top()`. When `s[j]` is popped, it means `s[i]` is the first element to the right of `s[j]` that is greater than `s[j]`.
        // Due to the monotonic property of the stack, all elements `s[k]` where `j < k < i` must be smaller than `s[j]`.
        // (If `s[k]` was greater than `s[j]`, `s[j]` would have been popped by `s[k]` earlier.
        // If `s[k]` was smaller than `s[j]`, it would have been pushed on top of `s[j]` and then popped by `s[i]` before `s[j]` was popped).
        // Therefore, for the range `s[j..i]`, `s[i]` is the maximum element and `s[j]` is the second maximum element.
        // We calculate their XOR and update `max_lucky_number`.
        while (!st.empty() && s[st.top()] < s[i]) {
            max_lucky_number = std::max(max_lucky_number, (long long)(s[st.top()] ^ s[i]));
            st.pop(); // Pop the index `j` as `s[j]` has found its "next greater element" to the right (`s[i]`).
        }

        // Phase 2: Process the element at the top of the stack (if any) that is greater than s[i].
        // If the stack is not empty after the above pops:
        // This means `s[st.top()]` is greater than `s[i]`.
        // Let `k = st.top()`. `s[k]` is the "previous greater element" to the left for `s[i]`.
        // All elements `s[x]` where `k < x < i` must be smaller than `s[i]` (because they were either popped by `s[i]` or were smaller than `s[i]` and pushed then popped).
        // Therefore, for the range `s[k..i]`, `s[k]` is the maximum element and `s[i]` is the second maximum element.
        // We calculate their XOR and update `max_lucky_number`.
        if (!st.empty()) {
            max_lucky_number = std::max(max_lucky_number, (long long)(s[st.top()] ^ s[i]));
        }

        // Phase 3: Push the current element's index onto the stack.
        // `s[i]` is now the new top of the stack, maintaining the decreasing order property.
        st.push(i);
    }

    std::cout << max_lucky_number << std::endl; // Print the final maximum lucky number found.

    return 0;
}
