#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Function to check if an array is beautiful (not ugly)
bool is_beautiful(const vector<int>& arr) {
    int sum = 0;
    for (int i = 0; i < arr.size(); ++i) {
        if (arr[i] == sum) return false; // If any element equals the sum of all previous, it's ugly
        sum += arr[i];
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        int total = 0;
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
            total += a[i];
        }

        // If all elements are the same, it's impossible to make it beautiful
        bool all_same = true;
        for (int i = 1; i < n; ++i) {
            if (a[i] != a[0]) {
                all_same = false;
                break;
            }
        }
        if (all_same) {
            cout << "NO\n";
            continue;
        }

        // Try to make a beautiful array by sorting in descending order
        sort(a.rbegin(), a.rend());

        // If the descending order is beautiful, print it
        if (is_beautiful(a)) {
            cout << "YES\n";
            for (int i = 0; i < n; ++i) {
                cout << a[i] << (i + 1 == n ? '\n' : ' ');
            }
            continue;
        }

        // If not, try to swap adjacent elements to avoid ugly property
        // (This is a rare case, but let's handle it for completeness)
        bool found = false;
        for (int i = 1; i < n; ++i) {
            swap(a[i], a[i-1]);
            if (is_beautiful(a)) {
                cout << "YES\n";
                for (int j = 0; j < n; ++j) {
                    cout << a[j] << (j + 1 == n ? '\n' : ' ');
                }
                found = true;
                break;
            }
            swap(a[i], a[i-1]); // swap back if not beautiful
        }
        if (!found) {
            cout << "NO\n";
        }
    }
    return 0;
}