#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    // Read input array
    for (int i = 0; i < n; ++i) cin >> a[i];

    // Map to store the indices of each value in a
    map<int, vector<int>> value_indices;
    for (int i = 0; i < n; ++i) {
        value_indices[a[i]].push_back(i);
    }

    // If any value occurs more than k times, it's impossible to color
    for (auto &p : value_indices) {
        if ((int)p.second.size() > k) {
            cout << "NO" << endl;
            return 0;
        }
    }

    // Prepare the answer array
    vector<int> color(n, 0);
    // To distribute colors, we will collect all indices and assign colors in round robin
    vector<pair<int, int>> all_indices; // (value, index)
    for (auto &p : value_indices) {
        for (int idx : p.second) {
            all_indices.push_back({p.first, idx});
        }
    }

    // Assign colors in round robin fashion
    int current_color = 1;
    for (auto &p : all_indices) {
        color[p.second] = current_color;
        current_color++;
        if (current_color > k) current_color = 1;
    }

    // Check that all colors are used at least once
    vector<bool> used(k + 1, false);
    for (int i = 0; i < n; ++i) {
        used[color[i]] = true;
    }
    for (int i = 1; i <= k; ++i) {
        if (!used[i]) {
            cout << "NO" << endl;
            return 0;
        }
    }

    // Output the answer
    cout << "YES" << endl;
    for (int i = 0; i < n; ++i) {
        cout << color[i] << " ";
    }
    cout << endl;
    return 0;
}