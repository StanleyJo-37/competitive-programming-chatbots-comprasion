#include <vector>
#include <algorithm>

std::vector<int> or_arrays(const std::vector<int>& arr1, const std::vector<int>& arr2, int o = 0) {
    std::vector<int> result;
    size_t max_size = std::max(arr1.size(), arr2.size());
    
    for (size_t i = 0; i < max_size; ++i) {
        int val1 = (i < arr1.size()) ? arr1[i] : o;
        int val2 = (i < arr2.size()) ? arr2[i] : o;
        result.push_back(val1 | val2);
    }
    
    return result;
}