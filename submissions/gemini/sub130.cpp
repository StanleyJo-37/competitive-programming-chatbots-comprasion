#include <iostream> // Required for input/output operations (std::cin, std::cout, std::endl).
#include <vector>   // Not strictly necessary for this specific solution, but often useful in competitive programming.
#include <numeric>  // Not strictly necessary for this specific solution, but provides std::accumulate for XOR sums.

// Function to solve a single test case.
void solve() {
    int n;
    std::cin >> n; // Read the number of integers in the array 'a'.

    // The problem states:
    // 1. An initial array has n-1 integers. Let's call them o_1, o_2, ..., o_{n-1}.
    // 2. 'x' is defined as the bitwise XOR sum of these n-1 integers: x = o_1 ^ o_2 ^ ... ^ o_{n-1}.
    // 3. This 'x' is added to the array, making its length 'n'. The array now contains {o_1, o_2, ..., o_{n-1}, x}.
    // 4. This array is then shuffled to form the given array 'a'.
    //
    // Let's consider the bitwise XOR sum of all elements in the final array 'a'.
    // Since 'a' contains exactly {o_1, o_2, ..., o_{n-1}, x} (in some order),
    // the XOR sum of all elements in 'a' is (o_1 ^ o_2 ^ ... ^ o_{n-1}) ^ x.
    // From the definition of 'x' (step 2), we know that (o_1 ^ o_2 ^ ... ^ o_{n-1}) is equal to 'x'.
    // So, the XOR sum of all elements in 'a' becomes x ^ x.
    // A fundamental property of bitwise XOR is that any number XORed with itself results in 0 (Y ^ Y = 0).
    // Therefore, the XOR sum of all elements in the given array 'a' is always 0.
    //
    // Now, we need to find 'x'. We know that 'x' is one of the elements in the given array 'a'.
    // Let's assume a specific element a_k from the given array 'a' is the true value of 'x'.
    // By definition, 'x' is the XOR sum of the *other* n-1 elements (which are o_1, ..., o_{n-1}).
    // So, if a_k is 'x', then a_k must be equal to the XOR sum of all elements in 'a' *except* a_k.
    //
    // Let S_total be the XOR sum of all elements in 'a'. We established S_total = 0.
    // The XOR sum of all elements in 'a' *except* a_k can be expressed as S_total ^ a_k.
    // Since S_total = 0, this simplifies to 0 ^ a_k, which is just a_k.
    //
    // So, the condition "a_k is equal to the XOR sum of all elements in 'a' except a_k"
    // simplifies to "a_k is equal to a_k". This statement is always true for any a_k.
    //
    // This means that *every* element in the given array 'a' satisfies the property that it is equal to the XOR sum of the other n-1 elements.
    // The problem states: "If there are multiple possible values of x, you can output any of them."
    // Since every element in 'a' is a valid candidate for 'x' based on the problem's definition and properties,
    // we can simply output any element from the array 'a'. The simplest is to output the first element.

    int first_element;
    std::cin >> first_element; // Read the first element of the array 'a'.

    // Read and discard the remaining n-1 elements, as they are not needed for the solution.
    for (int i = 1; i < n; ++i) {
        int temp;
        std::cin >> temp;
    }

    std::cout << first_element << std::endl; // Output the first element as the value of 'x'.
}

int main() {
    // Optimize C++ standard streams for faster input/output.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams.
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads input.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t; // Read the number of test cases.
    while (t--) {  // Loop through each test case.
        solve();   // Call the solve function for the current test case.
    }
    return 0; // Indicate successful execution.
}
