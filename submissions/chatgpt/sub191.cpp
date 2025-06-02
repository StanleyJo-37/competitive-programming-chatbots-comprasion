#include <iostream>
#include <vector>
#include <algorithm>

// Function to sort the array by value * (index+1)
std::vector<int> sortByValueAndIndex(const std::vector<int>& arr) {
    // Pair each element with its product (value * (index+1))
    std::vector<std::pair<int, int>> products;
    for (size_t i = 0; i < arr.size(); ++i) {
        // Store pair: (product, value)
        products.emplace_back(arr[i] * (i + 1), arr[i]);
    }
    // Sort by product (ascending)
    std::sort(products.begin(), products.end());
    // Extract sorted values
    std::vector<int> result;
    for (const auto& p : products) {
        result.push_back(p.second);
    }
    return result;
}

int main() {
    // Read input from standard input
    std::vector<int> arr;
    int x;
    // Read until end of input (e.g., EOF or newline)
    while (std::cin >> x) {
        arr.push_back(x);
        if (std::cin.peek() == '\n' || std::cin.peek() == EOF) break;
    }
    // Sort the array as per the problem statement
    std::vector<int> sortedArr = sortByValueAndIndex(arr);
    // Output the sorted array
    for (size_t i = 0; i < sortedArr.size(); ++i) {
        if (i > 0) std::cout << " ";
        std::cout << sortedArr[i];
    }
    std::cout << std::endl;
    return 0;
}