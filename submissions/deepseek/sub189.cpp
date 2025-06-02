#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> s(n);
    for (int i = 0; i < n; ++i) {
        cin >> s[i];
    }

    // Create a copy of the original array and sort it to find the two largest elements
    vector<int> sorted_s = s;
    sort(sorted_s.begin(), sorted_s.end());
    int max1 = sorted_s[n - 1]; // Largest element
    int max2 = sorted_s[n - 2]; // Second largest element

    for (int i = 0; i < n; ++i) {
        // If current element is the largest, the next largest is max2
        if (s[i] == max1) {
            cout << s[i] - max2 << " ";
        } else {
            cout << s[i] - max1 << " ";
        }
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}