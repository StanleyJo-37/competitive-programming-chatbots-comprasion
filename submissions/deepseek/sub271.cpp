#include <vector>
#include <algorithm>

std::vector<int> poly_add(const std::vector<int> &a, const std::vector<int> &b) {
    // Determine the maximum size between the two polynomials
    size_t max_size = std::max(a.size(), b.size());
    std::vector<int> result(max_size, 0); // Initialize result with zeros
    
    // Add coefficients from polynomial 'a'
    for (size_t i = 0; i < a.size(); ++i) {
        result[i] += a[i];
    }
    
    // Add coefficients from polynomial 'b'
    for (size_t i = 0; i < b.size(); ++i) {
        result[i] += b[i];
    }
    
    return result;
}