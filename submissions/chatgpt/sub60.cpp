#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false); // Fast IO
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;
    vector<int> roots(N);
    for (int i = 0; i < N; ++i) {
        cin >> roots[i];
    }

    // Sort the roots for binary search
    sort(roots.begin(), roots.end());

    while (Q--) {
        int x;
        cin >> x;

        // Use binary search to check if x is a root
        if (binary_search(roots.begin(), roots.end(), x)) {
            cout << "0\n";
            continue;
        }

        // Count number of roots less than x using lower_bound
        // lower_bound returns iterator to first element >= x
        // So, number of roots less than x is (it - roots.begin())
        int cnt = lower_bound(roots.begin(), roots.end(), x) - roots.begin();

        // If number of negative terms is even, product is positive, else negative
        if ((N - cnt) % 2 == 0) {
            cout << "POSITIVE\n";
        } else {
            cout << "NEGATIVE\n";
        }
    }
    return 0;
}