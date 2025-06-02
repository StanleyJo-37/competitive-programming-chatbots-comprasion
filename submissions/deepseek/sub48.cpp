#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<pair<int, int>> left, right;

    for (int i = 0; i < n; ++i) {
        int x, a;
        cin >> x >> a;
        if (x < 0) {
            left.emplace_back(-x, a); // Store left trees as positive for easy sorting
        } else {
            right.emplace_back(x, a);
        }
    }

    // Sort left trees in ascending order (original positions are -x)
    sort(left.begin(), left.end());
    // Sort right trees in ascending order
    sort(right.begin(), right.end());

    int res = 0;
    int m = min(left.size(), right.size());

    // Collect apples from the closest trees first, alternating directions
    for (int i = 0; i < m; ++i) {
        res += left[i].second + right[i].second;
    }

    // If there's an extra tree on either side, add its apples
    if (left.size() > right.size()) {
        res += left[m].second;
    } else if (right.size() > left.size()) {
        res += right[m].second;
    }

    cout << res << endl;
    return 0;
}