#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    // Store each team's (problems solved, penalty time)
    vector<pair<int, int>> teams(n);
    for (int i = 0; i < n; ++i) {
        cin >> teams[i].first >> teams[i].second;
    }

    // Sort teams: more problems solved first, then less penalty time
    sort(teams.begin(), teams.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        if (a.first != b.first)
            return a.first > b.first;
        return a.second < b.second;
    });

    // Find the (problems solved, penalty time) for the k-th place (1-based index)
    pair<int, int> kth_team = teams[k - 1];

    // Count how many teams have the same (problems solved, penalty time) as the k-th team
    int count = 0;
    for (int i = 0; i < n; ++i) {
        if (teams[i] == kth_team)
            ++count;
    }

    cout << count << endl;
    return 0;
}