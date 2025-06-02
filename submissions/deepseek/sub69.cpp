#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    // Check if the array is already not sorted in either non-decreasing or non-increasing order
    bool is_non_decreasing = true;
    bool is_non_increasing = true;
    for (int i = 1; i < n; ++i) {
        if (a[i] < a[i-1]) is_non_decreasing = false;
        if (a[i] > a[i-1]) is_non_increasing = false;
    }

    // If the array is not sorted in any order, any swap of distinct elements will keep it unsorted
    if (!is_non_decreasing && !is_non_increasing) {
        // Find any two distinct elements to swap
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (a[i] != a[j]) {
                    cout << i + 1 << " " << j + 1 << endl;
                    return 0;
                }
            }
        }
        // All elements are the same, no possible swap
        cout << -1 << endl;
        return 0;
    }

    // If the array is sorted in some order, find a swap that breaks the order
    // Make a copy to check after swapping
    vector<int> original = a;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (a[i] != a[j]) {
                swap(a[i], a[j]);
                // Check if the array is no longer sorted in either order
                bool new_non_decreasing = true;
                bool new_non_increasing = true;
                for (int k = 1; k < n; ++k) {
                    if (a[k] < a[k-1]) new_non_decreasing = false;
                    if (a[k] > a[k-1]) new_non_increasing = false;
                }
                if (!new_non_decreasing && !new_non_increasing) {
                    cout << i + 1 << " " << j + 1 << endl;
                    return 0;
                }
                // Revert the swap
                swap(a[i], a[j]);
            }
        }
    }

    // No such swap found
    cout << -1 << endl;
    return 0;
}