#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    // Fast IO
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    string s, t;
    cin >> s >> t;

    // left[i]: the earliest position in s where t[i] matches (0-based)
    vector<int> left(m);
    // right[i]: the latest position in s where t[i] matches (0-based)
    vector<int> right(m);

    // Find left[]: scan s from left to right, for each t[i], find first occurrence in order
    int idx = 0;
    for (int i = 0; i < n && idx < m; ++i) {
        if (s[i] == t[idx]) {
            left[idx] = i;
            ++idx;
        }
    }

    // Find right[]: scan s from right to left, for each t[i], find last occurrence in reverse order
    idx = m - 1;
    for (int i = n - 1; i >= 0 && idx >= 0; --i) {
        if (s[i] == t[idx]) {
            right[idx] = i;
            --idx;
        }
    }

    // The answer is the maximum difference between right[i+1] and left[i] for i in [0, m-2]
    int max_width = 1;
    for (int i = 0; i < m - 1; ++i) {
        // width between t[i] and t[i+1] is right[i+1] - left[i]
        int width = right[i+1] - left[i];
        if (width > max_width) max_width = width;
    }

    cout << max_width << '\n';
    return 0;
}