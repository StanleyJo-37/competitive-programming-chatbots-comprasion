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

    int max_len = 1; // At least one problem is always valid
    int current_len = 1;

    // We use a sliding window approach to find the longest valid segment
    for (int left = 0, right = 1; right < n; ++right) {
        if (a[right] <= 2 * a[right - 1]) {
            current_len++;
            max_len = max(max_len, current_len);
        } else {
            left = right;
            current_len = 1;
        }
    }

    cout << max_len << endl;
    return 0;
}