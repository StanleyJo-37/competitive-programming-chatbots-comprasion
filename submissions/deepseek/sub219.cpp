#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) cin >> b[i];

    vector<int> left_min(n, -1), right_min(n, n); // For b's min ranges
    vector<int> left_max(n, -1), right_max(n, n);  // For a's max ranges

    stack<int> s;

    // Compute left_min for b (previous smaller elements)
    for (int i = 0; i < n; ++i) {
        while (!s.empty() && b[s.top()] >= b[i]) s.pop();
        if (!s.empty()) left_min[i] = s.top();
        s.push(i);
    }
    while (!s.empty()) s.pop();

    // Compute right_min for b (next smaller elements)
    for (int i = n - 1; i >= 0; --i) {
        while (!s.empty() && b[s.top()] > b[i]) s.pop();
        if (!s.empty()) right_min[i] = s.top();
        s.push(i);
    }
    while (!s.empty()) s.pop();

    // Compute left_max for a (previous larger elements)
    for (int i = 0; i < n; ++i) {
        while (!s.empty() && a[s.top()] <= a[i]) s.pop();
        if (!s.empty()) left_max[i] = s.top();
        s.push(i);
    }
    while (!s.empty()) s.pop();

    // Compute right_max for a (next larger or equal elements)
    for (int i = n - 1; i >= 0; --i) {
        while (!s.empty() && a[s.top()] < a[i]) s.pop();
        if (!s.empty()) right_max[i] = s.top();
        s.push(i);
    }

    long long res = 0;

    for (int i = 0; i < n; ++i) {
        // For each i, find the range where a[i] is the max in a and b[i] is the min in b
        // Then, the number of intervals is (i - l + 1) * (r - i + 1) where l and r are the bounds
        // But we need to find the intersection of the two ranges
        int l1 = left_max[i] + 1;
        int r1 = right_max[i] - 1;
        int l2 = left_min[i] + 1;
        int r2 = right_min[i] - 1;

        int l = max(l1, l2);
        int r = min(r1, r2);
        if (l <= i && i <= r && a[i] == b[i]) {
            res += (long long)(i - l + 1) * (r - i + 1);
        }
    }

    cout << res << '\n';

    return 0;
}