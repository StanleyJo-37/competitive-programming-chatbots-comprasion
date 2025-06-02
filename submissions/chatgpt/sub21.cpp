#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Structure to represent an interval
struct Interval {
    int a, b;
    // For sorting by end time
    bool operator<(const Interval& other) const {
        return b < other.b || (b == other.b && a < other.a);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int S;
    cin >> S;
    while (S--) {
        int n;
        cin >> n;
        vector<Interval> intervals(n);
        for (int i = 0; i < n; ++i) {
            cin >> intervals[i].a >> intervals[i].b;
        }

        // Sort intervals by end time (greedy principle)
        sort(intervals.begin(), intervals.end());

        // dp[i]: max subset size ending with interval i, with no three overlapping at a point
        // prev1[i]: index of the last interval before i that does not overlap with i
        // prev2[i]: index of the last interval before i that does not overlap with both i and prev1[i]
        vector<int> dp(n, 1); // At least one interval (itself)
        vector<int> prev1(n, -1), prev2(n, -1);

        // For efficient lookup, store the end times and their indices
        vector<pair<int, int>> ends; // (end, index)
        for (int i = 0; i < n; ++i) {
            ends.emplace_back(intervals[i].b, i);
        }

        // For each interval, find the last interval that ends before its start (for prev1)
        for (int i = 0; i < n; ++i) {
            // Binary search for prev1: last interval j < i with intervals[j].b < intervals[i].a
            int l = 0, r = i - 1, res = -1;
            while (l <= r) {
                int m = (l + r) / 2;
                if (intervals[m].b < intervals[i].a) {
                    res = m;
                    l = m + 1;
                } else {
                    r = m - 1;
                }
            }
            prev1[i] = res;

            // For prev2: find the last interval k < prev1[i] with intervals[k].b < intervals[prev1[i]].a
            if (prev1[i] != -1) {
                int l2 = 0, r2 = prev1[i] - 1, res2 = -1;
                while (l2 <= r2) {
                    int m2 = (l2 + r2) / 2;
                    if (intervals[m2].b < intervals[prev1[i]].a) {
                        res2 = m2;
                        l2 = m2 + 1;
                    } else {
                        r2 = m2 - 1;
                    }
                }
                prev2[i] = res2;
            }
        }

        int ans = 0;
        for (int i = 0; i < n; ++i) {
            // Option 1: take only this interval
            dp[i] = 1;
            // Option 2: take this and one previous non-overlapping interval
            if (prev1[i] != -1) {
                dp[i] = max(dp[i], dp[prev1[i]] + 1);
            }
            // Option 3: take this and two previous non-overlapping intervals (no three overlap at a point)
            if (prev2[i] != -1) {
                dp[i] = max(dp[i], dp[prev2[i]] + 2);
            }
            // Update answer
            if (dp[i] > ans) ans = dp[i];
        }

        cout << ans << '\n';
    }
    return 0;
}