#include <vector>
#include <algorithm>

std::vector<int> sortByValueAndIndex(std::vector<int> array) {
    // Create a vector of pairs where each pair consists of (product, original value)
    std::vector<std::pair<int, int>> products;
    for (int i = 0; i < array.size(); ++i) {
        // Calculate product: value * (index + 1) since index starts at 1
        products.emplace_back(array[i] * (i + 1), array[i]);
    }
    
    // Sort the pairs based on the product (first element of the pair)
    std::sort(products.begin(), products.end(), 
        [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
            return a.first < b.first;
        });
    
    // Extract the sorted values from the pairs
    std::vector<int> result;
    for (const auto& p : products) {
        result.push_back(p.second);
    }
    
    return result;
}