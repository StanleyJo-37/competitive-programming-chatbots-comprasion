#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    string s, t;
    cin >> s >> t;

    // Precompute left and right arrays to store the earliest and latest positions
    // where characters of t appear in s.
    vector<int> left(m), right(m);

    // Compute left array: left[i] is the first occurrence of t[i] in s after left[i-1]
    for (int i = 0, j = 0; i < m; ++i) {
        while (j < n && s[j] != t[i]) ++j;
        left[i] = j++;
    }

    // Compute right array: right[i] is the last occurrence of t[i] in s before right[i+1]
    for (int i = m - 1, j = n - 1; i >= 0; --i) {
        while (j >= 0 && s[j] != t[i]) --j;
        right[i] = j--;
    }

    int max_width = 0;
    // The maximum width is the maximum difference between right[i+1] and left[i]
    for (int i = 0; i < m - 1; ++i) {
        max_width = max(max_width, right[i + 1] - left[i]);
    }

    cout << max_width << '\n';
    return 0;
}