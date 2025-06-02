#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false); // Fast IO
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        string lids;
        cin >> lids;
        vector<int> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];

        // covered[i] = true if box i is covered after optimal lid moves
        vector<bool> covered(n, false);

        // We process from right to left, greedily moving each lid to the left if possible
        for (int i = n - 1; i >= 0; --i) {
            if (lids[i] == '1') {
                // If possible, move the lid to the left (i-1), else keep it at i
                if (i > 0 && !covered[i-1]) {
                    covered[i-1] = true;
                } else {
                    covered[i] = true;
                }
            }
        }

        // Sum up the magazines in covered boxes
        long long ans = 0;
        for (int i = 0; i < n; ++i) {
            if (covered[i]) ans += a[i];
        }
        cout << ans << '\n';
    }
    return 0;
}