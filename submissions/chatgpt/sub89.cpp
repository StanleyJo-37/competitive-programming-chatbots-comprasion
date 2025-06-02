#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<pair<int, int>> widths(n); // (width, row_index)
    for (int i = 0; i < n; ++i) {
        int w;
        cin >> w;
        widths[i] = {w, i + 1}; // store 1-based index
    }

    // Sort by width for easy access to smallest/largest
    sort(widths.begin(), widths.end());

    // Set of empty rows: (width, row_index), sorted by width ascending
    set<pair<int, int>> empty_rows;
    for (auto &p : widths) empty_rows.insert(p);

    // Set of half-occupied rows: (width, row_index), sorted by width ascending
    set<pair<int, int>> half_rows;

    string s;
    cin >> s;
    vector<int> result;
    for (char c : s) {
        if (c == '0') {
            // Introvert: pick the empty row with smallest width
            auto it = empty_rows.begin();
            int row = it->second;
            result.push_back(row);
            // Move this row to half-occupied
            half_rows.insert(*it);
            empty_rows.erase(it);
        } else {
            // Extrovert: pick the half-occupied row with largest width
            auto it = prev(half_rows.end());
            int row = it->second;
            result.push_back(row);
            // Now this row is fully occupied, remove from half_rows
            half_rows.erase(it);
        }
    }

    // Output the result
    for (int i = 0; i < (int)result.size(); ++i) {
        cout << result[i];
        if (i + 1 < (int)result.size()) cout << ' ';
    }
    cout << '\n';
    return 0;
}