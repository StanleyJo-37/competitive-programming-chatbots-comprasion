#include <vector>
#include <set>
#include <algorithm>

using namespace std;

vector<int> arrayManip(const vector<int>& arr) {
    if (arr.empty()) return {};
    
    vector<int> result(arr.size(), -1);
    set<int> seen;
    
    // Traverse the array from right to left
    for (int i = arr.size() - 1; i >= 0; --i) {
        // Find the smallest element greater than arr[i] in the set
        auto it = seen.upper_bound(arr[i]);
        if (it != seen.end()) {
            result[i] = *it;
        }
        // Insert the current element into the set
        seen.insert(arr[i]);
    }
    
    return result;
}