#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);

    // Read the array
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    // If array has less than 2 elements, can't swap
    if (n < 2) {
        cout << -1 << endl;
        return 0;
    }

    // Check if all elements are equal
    bool all_equal = true;
    for (int i = 1; i < n; ++i) {
        if (a[i] != a[0]) {
            all_equal = false;
            break;
        }
    }
    if (all_equal) {
        cout << -1 << endl;
        return 0;
    }

    // Check if array is sorted (non-decreasing or non-increasing)
    bool non_decreasing = true, non_increasing = true;
    for (int i = 1; i < n; ++i) {
        if (a[i] < a[i-1]) non_decreasing = false;
        if (a[i] > a[i-1]) non_increasing = false;
    }

    // If not sorted, any swap will not make it unsorted (already unsorted)
    if (!non_decreasing && !non_increasing) {
        cout << -1 << endl;
        return 0;
    }

    // Find two positions with different values to swap
    // This will always make the array unsorted if it was sorted before
    // (since swapping two different values in a sorted array will break the order)
    for (int i = 0; i < n; ++i) {
        for (int j = i+1; j < n; ++j) {
            if (a[i] != a[j]) {
                cout << i+1 << " " << j+1 << endl; // Output 1-based indices
                return 0;
            }
        }
    }

    // If no such pair found (should not reach here due to previous all_equal check)
    cout << -1 << endl;
    return 0;
}