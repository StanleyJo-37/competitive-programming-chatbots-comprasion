#include <vector>
#include <algorithm>

using namespace std;

int findDeletedNumber(vector<int> arr, vector<int> mixedArr) {
    // If the original array is empty, return 0 (no deletion possible)
    if (arr.empty()) {
        return 0;
    }

    // Sort the mixed array to facilitate comparison
    sort(mixedArr.begin(), mixedArr.end());

    // Iterate through both arrays to find the missing number
    for (size_t i = 0; i < arr.size(); ++i) {
        // If we've reached the end of the mixed array, the missing number is the last element of the original array
        if (i >= mixedArr.size()) {
            return arr.back();
        }
        // If the current elements don't match, the missing number is found
        if (arr[i] != mixedArr[i]) {
            return arr[i];
        }
    }

    // If all elements match, no number was deleted
    return 0;
}