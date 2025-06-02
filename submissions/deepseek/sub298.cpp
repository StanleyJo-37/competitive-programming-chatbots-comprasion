#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int INF = 1e9;

struct Event {
    int t, l, r, type; // type: 0 for start, 1 for end
    bool operator<(const Event& other) const {
        if (t != other.t) return t < other.t;
        return type < other.type;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, x;
    cin >> n >> x;
    vector<Event> events;

    for (int i = 0; i < n; ++i) {
        int tl, tr, l, r;
        cin >> tl >> tr >> l >> r;
        // Convert the curse into intervals where the person cannot be at time t
        // The person is safe if at time t, his position is <= l-1 or >= r+1
        // So the forbidden intervals are (l-1, r+1) at time (tl-1, tr+1)
        events.push_back({tl - 1, l - 1, r + 1, 0});
        events.push_back({tr + 1, l - 1, r + 1, 1});
    }

    sort(events.begin(), events.end());

    set<pii> forbidden; // {l, r}
    forbidden.insert({-INF, -INF});
    forbidden.insert({INF, INF});

    vector<pair<int, pii>> intervals; // {time, {l, r}}
    int prev_time = 0;

    for (const auto& e : events) {
        if (e.t != prev_time) {
            // Collect all forbidden intervals at prev_time
            auto it = forbidden.begin();
            ++it; // skip the dummy
            while (it->first != INF) {
                intervals.emplace_back(prev_time, *it);
                ++it;
            }
            prev_time = e.t;
        }
        if (e.type == 0) {
            forbidden.insert({e.l, e.r});
        } else {
            forbidden.erase({e.l, e.r});
        }
    }

    // Now, we need to find the minimal energy to avoid all intervals
    // The person starts at x at time 0
    // We can model this as a DP problem where we track the safe positions over time
    // intervals are sorted by time

    // We'll represent the safe positions as a set of intervals, and update them as we process each time interval
    set<pii> safe;
    safe.insert({-INF, INF});
    ll cost = 0;

    auto get_min_move = [&](int pos, const set<pii>& s) {
        auto it = s.upper_bound({pos, INF});
        --it;
        if (it->first <= pos && pos <= it->second) {
            return 0;
        }
        int min_dist = INF;
        if (it->second < pos) {
            min_dist = min(min_dist, pos - it->second);
        }
        ++it;
        if (it->first > pos) {
            min_dist = min(min_dist, it->first - pos);
        }
        return min_dist;
    };

    int current_time = 0;
    int current_pos = x;

    for (const auto& interval : intervals) {
        int t = interval.first;
        int l = interval.second.first;
        int r = interval.second.second;

        if (t <= current_time) continue;

        // The person moves from current_time to t-1, so at time t-1, the position is current_pos + (t-1 - current_time)
        int new_pos = current_pos + (t - 1 - current_time);
        current_time = t - 1;

        // Check if the current position is safe
        auto it = safe.upper_bound({new_pos, INF});
        --it;
        if (!(it->first <= new_pos && new_pos <= it->second)) {
            // Need to move to the nearest safe position
            int min_dist = INF;
            if (it->second < new_pos) {
                min_dist = min(min_dist, new_pos - it->second);
            }
            ++it;
            if (it->first > new_pos) {
                min_dist = min(min_dist, it->first - new_pos);
            }
            cost += min_dist;
            if (it->second < new_pos) {
                --it;
                new_pos = it->second;
            } else {
                new_pos = it->first;
            }
        }

        // Now, update the safe intervals by removing (l, r)
        set<pii> new_safe;
        for (const auto& s : safe) {
            if (s.second <= l || s.first >= r) {
                new_safe.insert(s);
            } else {
                if (s.first < l) {
                    new_safe.insert({s.first, l});
                }
                if (s.second > r) {
                    new_safe.insert({r, s.second});
                }
            }
        }
        safe = new_safe;

        // Update current_time to t
        current_time = t;
        current_pos = new_pos;
    }

    // After all intervals, check if the final position is safe
    int final_pos = current_pos + (1000000 - current_time);
    auto it = safe.upper_bound({final_pos, INF});
    --it;
    if (!(it->first <= final_pos && final_pos <= it->second)) {
        int min_dist = INF;
        if (it->second < final_pos) {
            min_dist = min(min_dist, final_pos - it->second);
        }
        ++it;
        if (it->first > final_pos) {
            min_dist = min(min_dist, it->first - final_pos);
        }
        cost += min_dist;
    }

    cout << cost << endl;

    return 0;
}