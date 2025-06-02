#include <vector>   // Required for std::vector
#include <algorithm> // Required for std::max

// Function to add two polynomials.
// Polynomials are represented as std::vector<int>, where the element at index `i`
// is the coefficient of x^i. For example, `[a0, a1, a2]` represents `a0 + a1*x + a2*x^2`.
//
// Parameters:
//   p1: The first polynomial as a constant reference to a vector of integers.
//   p2: The second polynomial as a constant reference to a vector of integers.
//
// Returns:
//   A new std::vector<int> representing the sum of the two input polynomials.
std::vector<int> poly_add(const std::vector<int>& p1, const std::vector<int>& p2) {
    // Determine the maximum length between the two input polynomial vectors.
    // This maximum length will define the initial size of our result vector,
    // ensuring it can hold coefficients up to the highest degree present in either polynomial.
    size_t max_len = std::max(p1.size(), p2.size());

    // Initialize the result polynomial vector with `max_len` elements, all set to zero.
    // This vector will store the sum of the coefficients.
    std::vector<int> result(max_len, 0);

    // Iterate through the coefficients of the first polynomial (`p1`).
    // For each coefficient, add it to the corresponding term in the `result` polynomial.
    // If `p1` is shorter than `max_len`, this loop will only process its existing terms.
    for (size_t i = 0; i < p1.size(); ++i) {
        result[i] += p1[i];
    }

    // Iterate through the coefficients of the second polynomial (`p2`).
    // For each coefficient, add it to the corresponding term in the `result` polynomial.
    // This correctly handles cases where `p2` is longer than `p1`, or vice-versa,
    // by adding to the already accumulated sums from `p1`.
    for (size_t i = 0; i < p2.size(); ++i) {
        result[i] += p2[i];
    }

    // After summing, the `result` vector might contain trailing zeros (e.g., `[5, 0, 0]` for `5`).
    // To represent the polynomial in its canonical form (e.g., `[5]` for `5`),
    // we remove these trailing zeros, unless the polynomial is simply `[0]`.
    // The loop continues as long as the vector has more than one element AND the last element is zero.
    while (result.size() > 1 && result.back() == 0) {
        // Remove the last element (trailing zero).
        result.pop_back();
    }

    // Return the resulting polynomial in its canonical form.
    return result;
}