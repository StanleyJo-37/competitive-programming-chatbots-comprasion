#include <vector>      // Required for std::vector
#include <algorithm>   // Required for std::sort
#include <utility>     // Required for std::pair

// Function to sort an array of integers by the product of its value and 1-based index.
// The sorting order is ascending based on this product.
// If products are equal, the original values are used as a tie-breaker (default std::pair behavior).
std::vector<int> sortByValueAndIndex(std::vector<int> arr) {
    // Create a temporary vector to store pairs of (product, original_value).
    // The product can potentially be large (value * index), so `long long` is used for `product`
    // to prevent overflow, as `int` values can be up to 2*10^9 and indices can be large.
    // The original value itself remains an `int`.
    std::vector<std::pair<long long, int>> product_value_pairs;

    // Iterate through the input array to calculate the product for each element.
    // The problem specifies that the index starts at 1, not 0.
    // So, for an element at 0-based index `i`, its 1-based index is `i + 1`.
    for (int i = 0; i < arr.size(); ++i) {
        // Calculate the product: value * (1-based index).
        // Cast arr[i] to long long before multiplication to ensure the product is calculated
        // using long long arithmetic, preventing intermediate overflow if arr[i] is large.
        long long current_product = static_cast<long long>(arr[i]) * (i + 1);
        
        // Store the calculated product and the original value as a pair.
        product_value_pairs.push_back({current_product, arr[i]});
    }

    // Sort the vector of pairs.
    // `std::pair` has a default comparison operator that sorts first by the `first` element
    // (which is our calculated product) in ascending order.
    // If `first` elements are equal, it then sorts by the `second` element (original value).
    // This fulfills the ascending sort requirement.
    std::sort(product_value_pairs.begin(), product_value_pairs.end());

    // Create the result vector to store the sorted original values.
    // Reserve memory to avoid multiple reallocations, improving efficiency,
    // as the final size is known.
    std::vector<int> result;
    result.reserve(arr.size());

    // Populate the result vector by extracting the original values (second element of the pair)
    // from the now sorted `product_value_pairs`.
    for (const auto& p : product_value_pairs) {
        result.push_back(p.second);
    }

    // Return the sorted array.
    return result;
}