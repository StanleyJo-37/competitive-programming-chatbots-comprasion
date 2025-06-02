#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    // Fast IO
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;
    vector<int> b(n);
    for (int i = 0; i < n; ++i) {
        cin >> b[i];
    }

    // If k >= n, we can use one tape per broken segment, so total length is n
    if (k >= n) {
        cout << n << '\n';
        return 0;
    }

    // Calculate the gaps between consecutive broken segments
    vector<int> gaps;
    for (int i = 1; i < n; ++i) {
        // The gap is the number of unbroken segments between b[i-1] and b[i]
        // If b[i-1]=x, b[i]=y, then gap = y - x - 1
        gaps.push_back(b[i] - b[i-1] - 1);
    }

    // Sort the gaps in descending order to find the largest ones
    sort(gaps.rbegin(), gaps.rend());

    // We want to split the broken segments into k groups, so we can skip the (k-1) largest gaps
    // The total length of tape needed is:
    // (last broken - first broken + 1) - sum of (k-1) largest gaps
    long long total_length = b[n-1] - b[0] + 1;
    for (int i = 0; i < k-1 && i < (int)gaps.size(); ++i) {
        total_length -= gaps[i];
    }

    cout << total_length << '\n';
    return 0;
}