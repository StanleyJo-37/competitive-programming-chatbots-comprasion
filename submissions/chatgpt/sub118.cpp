#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Read input
    int n, a, b, k;
    cin >> n >> a >> b >> k;
    vector<int> r(n);
    for (int i = 0; i < n; ++i) {
        cin >> r[i];
    }

    // Count frequency of each rating
    unordered_map<int, int> freq;
    for (int x : r) {
        ++freq[x];
    }

    // Use map to keep ratings sorted (ascending order)
    map<int, int> rating_count;
    for (auto &p : freq) {
        rating_count[p.first] = p.second;
    }

    long long ans = 0;

    // For each possible lower rating, try to form teams with higher rating = k * lower rating
    for (auto it = rating_count.begin(); it != rating_count.end(); ++it) {
        int r1 = it->first;
        int r2 = r1 * k;
        // If r2 exists in the map
        if (rating_count.count(r2)) {
            // Number of teams is limited by available a-sets of r1 and b-sets of r2
            int teams_a = it->second / a;
            int teams_b = rating_count[r2] / b;
            int teams = min(teams_a, teams_b);
            if (teams > 0) {
                // Use up the players for these teams
                it->second -= teams * a;
                rating_count[r2] -= teams * b;
                ans += teams;
            }
        }
    }

    cout << ans << '\n';
    return 0;
}