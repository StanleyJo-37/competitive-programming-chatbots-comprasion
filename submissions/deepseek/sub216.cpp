#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k, s, t;
    cin >> n >> k >> s >> t;

    vector<pair<int, int>> cars(n);
    for (int i = 0; i < n; ++i) {
        cin >> cars[i].first >> cars[i].second;
    }

    vector<int> stations(k);
    for (int i = 0; i < k; ++i) {
        cin >> stations[i];
    }
    stations.push_back(0);
    stations.push_back(s);
    sort(stations.begin(), stations.end());

    // Precompute the segments between gas stations
    vector<int> segments;
    for (int i = 1; i < stations.size(); ++i) {
        segments.push_back(stations[i] - stations[i-1]);
    }
    sort(segments.begin(), segments.end());

    // Binary search the minimal required v
    int left = 0, right = 2e9;
    int min_v = -1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        ll total_time = 0;
        bool possible = true;
        for (int seg : segments) {
            if (mid < seg) {
                possible = false;
                break;
            }
            // The minimal time for segment is max(seg * 2 - mid, seg) + (mid - seg)
            // Simplified: max(3*seg - mid, seg)
            int t_seg = max(3 * seg - mid, seg);
            if (t_seg > 2 * seg) {
                possible = false;
                break;
            }
            total_time += t_seg;
            if (total_time > t) {
                possible = false;
                break;
            }
        }
        if (possible) {
            min_v = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    if (min_v == -1) {
        cout << -1 << endl;
        return 0;
    }

    // Find the minimal cost car with v >= min_v
    int min_cost = INT_MAX;
    for (auto& car : cars) {
        if (car.second >= min_v) {
            min_cost = min(min_cost, car.first);
        }
    }

    if (min_cost == INT_MAX) {
        cout << -1 << endl;
    } else {
        cout << min_cost << endl;
    }

    return 0;
}