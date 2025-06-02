#include <bits/stdc++.h>
using namespace std;

// Structure to represent a curse event
struct Curse {
    int tl, tr, l, r;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    int x;
    cin >> x;

    vector<Curse> curses(n);
    for (int i = 0; i < n; ++i) {
        cin >> curses[i].tl >> curses[i].tr >> curses[i].l >> curses[i].r;
    }

    // Collect all relevant time points: start and end of each curse
    vector<int> times;
    times.push_back(0); // initial time
    for (int i = 0; i < n; ++i) {
        times.push_back(curses[i].tl);
        times.push_back(curses[i].tr);
    }
    sort(times.begin(), times.end());
    times.erase(unique(times.begin(), times.end()), times.end());
    int m = times.size();

    // For each time, collect the forbidden intervals (cursed intervals)
    vector<vector<pair<double, double>>> forbidden(m);
    for (int i = 0; i < n; ++i) {
        // For each curse, mark its interval at its active times
        for (int j = 0; j < m; ++j) {
            if (times[j] > curses[i].tl && times[j] < curses[i].tr) {
                forbidden[j].emplace_back(curses[i].l, curses[i].r);
            }
        }
    }

    // For each time, compute the allowed intervals (complement of forbidden)
    vector<vector<pair<double, double>>> allowed(m);
    for (int i = 0; i < m; ++i) {
        // Merge forbidden intervals
        auto &forb = forbidden[i];
        sort(forb.begin(), forb.end());
        vector<pair<double, double>> merged;
        for (auto &p : forb) {
            if (merged.empty() || merged.back().second < p.first) {
                merged.push_back(p);
            } else {
                merged.back().second = max(merged.back().second, p.second);
            }
        }
        // Now, build allowed intervals as complement in [1, 1e6]
        double L = 1, R = 1e6;
        double prev = L;
        for (auto &p : merged) {
            if (prev < p.first) {
                allowed[i].emplace_back(prev, p.first);
            }
            prev = max(prev, p.second);
        }
        if (prev < R + 1e-8) {
            allowed[i].emplace_back(prev, R + 1e-8);
        }
    }

    // DP: for each time, for each allowed interval, store minimal energy to reach any point in that interval
    // We only need to store for each interval the minimal energy to reach its left and right endpoints
    // dp[i][j][0] = minimal energy to reach left endpoint of j-th allowed interval at i-th time
    // dp[i][j][1] = minimal energy to reach right endpoint of j-th allowed interval at i-th time
    vector<vector<array<double, 2>>> dp(m);

    // At time 0, the person is at x, so only need to move to an allowed interval if x is not in any
    for (int j = 0; j < (int)allowed[0].size(); ++j) {
        double l = allowed[0][j].first, r = allowed[0][j].second;
        // If x is in [l, r), no energy needed to stay
        if (x >= l && x < r) {
            dp[0].push_back({0.0, 0.0});
        } else {
            // Otherwise, need to move to l or r
            dp[0].push_back({abs(x - l), abs(x - (r - 1e-8))});
        }
    }

    // For each time step
    for (int i = 1; i < m; ++i) {
        double dt = times[i] - times[i - 1];
        // For each allowed interval at this time
        dp[i].resize(allowed[i].size(), {1e18, 1e18});
        for (int j = 0; j < (int)allowed[i].size(); ++j) {
            double l2 = allowed[i][j].first, r2 = allowed[i][j].second;
            // The person moves at speed 1, so at time times[i], his coordinate is x + times[i]
            // We can only move him at times[i], so we need to consider moving from any allowed interval at previous time
            for (int k = 0; k < (int)allowed[i - 1].size(); ++k) {
                double l1 = allowed[i - 1][k].first, r1 = allowed[i - 1][k].second;
                // At previous time, the person could be at l1 or r1
                for (int s1 = 0; s1 < 2; ++s1) {
                    double pos1 = (s1 == 0 ? l1 : r1 - 1e-8);
                    double pos1_next = pos1 + dt; // position at current time if not moved
                    // If pos1_next is in [l2, r2), we can stay without moving
                    if (pos1_next >= l2 && pos1_next < r2) {
                        // No move needed
                        dp[i][j][0] = min(dp[i][j][0], dp[i - 1][k][s1]);
                        dp[i][j][1] = min(dp[i][j][1], dp[i - 1][k][s1]);
                    }
                    // Otherwise, we can move at times[i] to l2 or r2-1e-8, but must not cross any forbidden interval
                    // Since all forbidden intervals are at this time, and movement is at a single time, we can move directly
                    // Move to l2
                    dp[i][j][0] = min(dp[i][j][0], dp[i - 1][k][s1] + abs(pos1_next - l2));
                    // Move to r2-1e-8
                    dp[i][j][1] = min(dp[i][j][1], dp[i - 1][k][s1] + abs(pos1_next - (r2 - 1e-8)));
                }
            }
        }
    }

    // The answer is the minimal energy at the last time, over all allowed intervals
    double ans = 1e18;
    for (int j = 0; j < (int)allowed[m - 1].size(); ++j) {
        ans = min(ans, dp[m - 1][j][0]);
        ans = min(ans, dp[m - 1][j][1]);
    }

    // Output the answer, rounded up to the nearest integer
    cout << (long long)(ceil(ans - 1e-8)) << '\n';
    return 0;
}