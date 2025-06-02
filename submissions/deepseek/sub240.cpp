#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    int max_len = 0;
    unordered_map<int, int> freq;
    int left = 0;

    for (int right = 0; right < n; ++right) {
        freq[a[right]]++;

        // Ensure the window has at most two distinct values with difference <= 1
        while (freq.size() > 2) {
            if (--freq[a[left]] == 0) {
                freq.erase(a[left]);
            }
            left++;
        }

        // Check if the current window is valid (max - min <= 1)
        if (freq.size() == 2) {
            auto min_max = minmax_element(freq.begin(), freq.end(),
                [](const pair<int, int>& p1, const pair<int, int>& p2) {
                    return p1.first < p2.first;
                });
            if (min_max.second->first - min_max.first->first > 1) {
                continue; // Window invalid, skip updating max_len
            }
        }

        max_len = max(max_len, right - left + 1);
    }

    cout << max_len << endl;
    return 0;
}