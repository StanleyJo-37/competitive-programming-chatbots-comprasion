#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, m, k;
    cin >> n >> m >> k;
    vector<long long> p(m);
    for (int i = 0; i < m; ++i) {
        cin >> p[i];
    }

    int res = 0;
    long long offset = 0; // Tracks the cumulative shift due to previous deletions
    int i = 0;
    while (i < m) {
        long long current = p[i] - offset; // Adjust for previous deletions
        long long page = (current - 1) / k; // Determine the current page (0-based)
        int j = i;
        // Find all elements in the same page after adjustment
        while (j < m && (p[j] - offset - 1) / k == page) {
            j++;
        }
        res++;
        offset += (j - i); // Increase offset by the number of deleted elements
        i = j;
    }
    cout << res << endl;
    return 0;
}