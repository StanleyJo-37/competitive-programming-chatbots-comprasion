#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    // First, check if it's possible to color the array.
    // For each color, we need at least one unique element.
    // So, no element can appear more than k times.
    unordered_map<int, int> freq;
    for (int num : a) {
        freq[num]++;
        if (freq[num] > k) {
            cout << "NO" << endl;
            return 0;
        }
    }

    // Now, assign colors. We can sort the array and assign colors in a round-robin fashion.
    vector<pair<int, int>> indexed_a;
    for (int i = 0; i < n; ++i) {
        indexed_a.emplace_back(a[i], i);
    }
    // Sort by value to ensure same values are grouped together.
    sort(indexed_a.begin(), indexed_a.end());

    vector<int> color(n);
    int current_color = 1;
    for (int i = 0; i < n; ++i) {
        color[indexed_a[i].second] = current_color;
        current_color = current_color % k + 1; // Cycle through 1..k
    }

    cout << "YES" << endl;
    for (int c : color) {
        cout << c << " ";
    }
    cout << endl;

    return 0;
}