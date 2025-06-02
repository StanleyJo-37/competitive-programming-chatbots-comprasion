#include <iostream>
#include <vector>
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
        vector<long long> heights(n); // To store the chosen heights for each slice
        long long total_width = 0; // To store the sum of widths

        for (int i = 0; i < n; ++i) {
            long long a, b;
            cin >> a >> b;
            // For each slice, we can rotate it, so we choose the smaller as width, larger as height
            if (a < b) {
                total_width += a;
                heights[i] = b;
            } else {
                total_width += b;
                heights[i] = a;
            }
        }

        // The minimum possible perimeter is:
        // 2 * (total_width + max_height)
        // - All slices are placed side by side, with their bottom on the x-axis, and all heights are maximized (so the shape is connected vertically).
        // - The only way to connect all slices is to align their bottoms, and the only way to minimize the perimeter is to minimize the total width and maximize the height (since the top will be at the max height).
        long long max_height = *max_element(heights.begin(), heights.end());
        long long perimeter = 2 * (total_width + max_height);
        cout << perimeter << '\n';
    }
    return 0;
}