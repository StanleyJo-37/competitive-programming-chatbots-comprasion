#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    // The graph G will have edges between elements that are compared and swapped during Bubble Sort.
    // The key observation is that the graph G is a comparability graph (specifically, a permutation graph).
    // In a permutation graph, the maximum independent set is equivalent to the longest increasing subsequence (LIS).
    // This is because no two elements in an increasing subsequence are swapped, hence no edges between them.
    // Therefore, the solution reduces to finding the length of the LIS of the permutation.

    vector<int> lis;
    for (int num : a) {
        auto it = lower_bound(lis.begin(), lis.end(), num);
        if (it == lis.end()) {
            lis.push_back(num);
        } else {
            *it = num;
        }
    }

    cout << lis.size() << '\n';
    return 0;
}