#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    // Read input values
    int n, k;
    cin >> n >> k;
    vector<long long> a(n); // damage values
    for (int i = 0; i < n; ++i) cin >> a[i];
    string s;
    cin >> s;

    long long total_damage = 0;
    int i = 0;
    while (i < n) {
        // For each group of consecutive same button presses
        char current_char = s[i];
        vector<long long> group;
        int j = i;
        // Collect all consecutive hits with the same button
        while (j < n && s[j] == current_char) {
            group.push_back(a[j]);
            ++j;
        }
        // Sort the group in descending order to pick the largest damages
        sort(group.rbegin(), group.rend());
        // Add up to k largest damages from this group
        for (int t = 0; t < min(k, (int)group.size()); ++t) {
            total_damage += group[t];
        }
        // Move to the next group
        i = j;
    }

    cout << total_damage << endl;
    return 0;
}