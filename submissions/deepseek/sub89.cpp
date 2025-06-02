#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<pair<int, int>> rows(n); // {width, original index}
    for (int i = 0; i < n; ++i) {
        cin >> rows[i].first;
        rows[i].second = i + 1; // 1-based index
    }

    // Sort rows by width to efficiently find the smallest available for introverts
    sort(rows.begin(), rows.end());

    string passengers;
    cin >> passengers;

    priority_queue<pair<int, int>> extrovert_candidates; // max-heap for extroverts
    vector<int> result;
    int introvert_ptr = 0; // pointer to the next smallest available row for introverts

    for (char c : passengers) {
        if (c == '0') {
            // Introvert: pick the smallest available row
            int row = rows[introvert_ptr].second;
            result.push_back(row);
            // Push to heap for extroverts (as negative to simulate min-heap, but we use max-heap)
            extrovert_candidates.push({rows[introvert_ptr].first, row});
            introvert_ptr++;
        } else {
            // Extrovert: pick the largest available row with one person
            auto top = extrovert_candidates.top();
            extrovert_candidates.pop();
            result.push_back(top.second);
        }
    }

    for (int i = 0; i < result.size(); ++i) {
        cout << result[i] << " ";
    }
    cout << "\n";

    return 0;
}