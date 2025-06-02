#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<pair<int, int>> teams(n); // Stores (problems, penalty) for each team

    for (int i = 0; i < n; ++i) {
        cin >> teams[i].first >> teams[i].second;
    }

    // Custom comparator to sort teams in descending order of problems, then ascending penalty
    auto cmp = [](const pair<int, int>& a, const pair<int, int>& b) {
        if (a.first != b.first) {
            return a.first > b.first; // More problems come first
        } else {
            return a.second < b.second; // If same problems, lower penalty comes first
        }
    };

    sort(teams.begin(), teams.end(), cmp);

    // The k-th team is at index k-1 (0-based)
    pair<int, int> kth_team = teams[k - 1];
    int count = 0;

    // Count all teams with same problems and penalty as the k-th team
    for (const auto& team : teams) {
        if (team == kth_team) {
            ++count;
        }
    }

    cout << count << endl;
    return 0;
}