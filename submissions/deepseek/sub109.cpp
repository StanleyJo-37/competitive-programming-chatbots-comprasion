#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;
    vector<int> b(n);
    for (int i = 0; i < n; ++i) {
        cin >> b[i];
    }

    // The minimal length is the sum of the differences between consecutive broken segments
    // minus the largest (k-1) differences, plus k (since each piece covers at least one segment)
    vector<int> diffs;
    for (int i = 1; i < n; ++i) {
        diffs.push_back(b[i] - b[i-1] - 1);
    }

    // Sort differences in descending order to pick the largest (k-1) gaps
    sort(diffs.begin(), diffs.end(), greater<int>());

    // Total segments covered is (b[n-1] - b[0] + 1)
    // Subtract the largest (k-1) gaps to minimize the total length
    long long total = b[n-1] - b[0] + 1;
    for (int i = 0; i < k - 1 && i < diffs.size(); ++i) {
        total -= diffs[i];
    }

    cout << total << '\n';
    return 0;
}