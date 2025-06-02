#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

// For each test case, we use DP to track the minimal and maximal possible endpoint
// after placing all segments, and the minimal and maximal coverage interval.
// dp[i][0] = minimal endpoint after i segments
// dp[i][1] = maximal endpoint after i segments
// minL[i] = minimal leftmost point covered after i segments
// maxR[i] = maximal rightmost point covered after i segments

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int &x : a) cin >> x;

        // At each step, we keep two states:
        // (endpoint, leftmost, rightmost) for both possible directions
        // dp[0]: endpoint if we go right at this step
        // dp[1]: endpoint if we go left at this step
        // For each, we also track the leftmost and rightmost covered point

        // For the first segment, it starts at 0, ends at a[0]
        // So two possible states: [0, a[0]] (endpoint at a[0]) or [0, -a[0]] (endpoint at -a[0])
        // But since the first segment must start at 0, only [0, a[0]] is valid
        // So we initialize only one state

        // Each state: (endpoint, leftmost, rightmost)
        struct State {
            int endpoint;
            int leftmost;
            int rightmost;
        };

        vector<State> curr, next;
        curr.push_back({a[0], 0, a[0]});

        for (int i = 1; i < n; ++i) {
            next.clear();
            for (const State &s : curr) {
                // Place segment to the right: [s.endpoint, s.endpoint + a[i]]
                int new_end = s.endpoint + a[i];
                int l = min(s.leftmost, s.endpoint);
                int r = max(s.rightmost, s.endpoint + a[i]);
                next.push_back({new_end, l, r});

                // Place segment to the left: [s.endpoint - a[i], s.endpoint]
                new_end = s.endpoint - a[i];
                l = min(s.leftmost, s.endpoint - a[i]);
                r = max(s.rightmost, s.endpoint);
                next.push_back({new_end, l, r});
            }
            // To avoid exponential growth, we only keep the best state for each endpoint
            // For each possible endpoint, keep only the state with minimal coverage length
            // Since endpoints can be negative, use a map or sort and unique
            // But since a[i] <= 1000 and n <= 1e4, endpoints are in reasonable range
            // So we can use a map for deduplication
            // But to optimize, we can keep only two states: one with minimal endpoint, one with maximal endpoint
            // Because the minimal coverage will be achieved at one of these two
            State min_state = next[0], max_state = next[0];
            for (const State &s : next) {
                if (s.endpoint < min_state.endpoint ||
                    (s.endpoint == min_state.endpoint && (s.rightmost - s.leftmost) < (min_state.rightmost - min_state.leftmost)))
                    min_state = s;
                if (s.endpoint > max_state.endpoint ||
                    (s.endpoint == max_state.endpoint && (s.rightmost - s.leftmost) < (max_state.rightmost - max_state.leftmost)))
                    max_state = s;
            }
            curr.clear();
            curr.push_back(min_state);
            if (min_state.endpoint != max_state.endpoint)
                curr.push_back(max_state);
        }

        // The answer is the minimal coverage among all possible final states
        int ans = INT_MAX;
        for (const State &s : curr) {
            ans = min(ans, s.rightmost - s.leftmost);
        }
        cout << ans << '\n';
    }
    return 0;
}