#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    // To find a point (x, y) that belongs to exactly k squares,
    // we can use the fact that a point (x, y) belongs to square i iff:
    // 0 <= x <= ai and 0 <= y <= ai

    // The set of all possible x and y coordinates that are interesting
    // are 0 and all ai, because the boundaries of the squares are at these points.
    // So, we can try all pairs (x, y) where x and y are in {0, a1, ..., an}
    // and check for each such pair how many squares it belongs to.

    // Collect all possible x and y values (0 and all ai)
    vector<long long> coords = {0};
    for (int i = 0; i < n; ++i) coords.push_back(a[i]);
    // Remove duplicates just in case (though ai are distinct, but 0 may be repeated)
    sort(coords.begin(), coords.end());
    coords.erase(unique(coords.begin(), coords.end()), coords.end());

    // Try all pairs (x, y) from coords
    for (size_t i = 0; i < coords.size(); ++i) {
        for (size_t j = 0; j < coords.size(); ++j) {
            long long x = coords[i], y = coords[j];
            int cnt = 0;
            // For each square, check if (x, y) is inside or on the boundary
            for (int t = 0; t < n; ++t) {
                if (0 <= x && x <= a[t] && 0 <= y && y <= a[t]) ++cnt;
            }
            if (cnt == k) {
                cout << x << " " << y << endl;
                return 0;
            }
        }
    }

    // If no such point found, print -1
    cout << -1 << endl;
    return 0;
}