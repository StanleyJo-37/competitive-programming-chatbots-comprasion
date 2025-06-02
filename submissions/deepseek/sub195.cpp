#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<pair<int, int>> cheeses(n);
    long long total_width = 0;
    int max_height = 0;
    
    for (int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        // For each cheese, we can choose to rotate it or not.
        // To minimize perimeter, we should maximize the height contribution.
        // So, for each cheese, take the smaller dimension as height (since perimeter is 2*(total_width + max_height)).
        // But wait, no: the perimeter is 2*(total_width + sum of max heights in vertical segments).
        // Actually, the perimeter is 2*(total_width + max_height), because all cheeses are stacked vertically.
        // So, to minimize perimeter, we need to minimize (total_width + max_height).
        // So, for each cheese, we take min(a, b) as one side and max(a, b) as the other.
        // Then, total_width is sum of all max(a_i, b_i) (if placed horizontally) or sum of min(a_i, b_i) (if placed vertically).
        // But since they must be connected and bottom on x-axis, the arrangement is a horizontal line of cheeses.
        // So, total_width is sum of widths (max(a_i, b_i) or min(a_i, b_i)), and max_height is the maximum of the other dimension.
        // To minimize (sum_width + max_height), for each cheese, we choose to take min(a_i, b_i) as height and max(a_i, b_i) as width, or vice versa.
        // The optimal is to take for each cheese, the larger dimension as width (to minimize max height, since sum of widths is fixed if we take larger as width).
        // Wait, no: sum of widths is minimized if we take the smaller dimension as width, but max height is larger.
        // So, the optimal is to take for each cheese, the smaller dimension as height (to minimize max height), and the larger as width.
        // Then, sum_width = sum of max(a_i, b_i), and max_height = max of min(a_i, b_i).
        int width = max(a, b);
        int height = min(a, b);
        cheeses[i] = {width, height};
        total_width += width;
        max_height = max(max_height, height);
    }
    // The perimeter is 2*(total_width + max_height).
    cout << 2 * (total_width + max_height) << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}