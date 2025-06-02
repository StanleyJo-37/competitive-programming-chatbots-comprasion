#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

// Function to check if a car with fuel tank capacity 'v' can finish the trip in at most 't' minutes
bool can_finish(const vector<int>& segs, int v, int t) {
    long long total_time = 0;
    for (int d : segs) {
        // If the segment is longer than the tank can handle even in normal mode, impossible
        if (d > v) return false;
        // If the tank can handle the segment in accelerated mode (2 liters/km), i.e. v >= 2*d
        if (v >= 2 * d) {
            // All in accelerated mode: 1 min/km
            total_time += d;
        } else {
            // Let x = amount of distance in accelerated mode (2 liters/km)
            // and (d-x) in normal mode (1 liter/km)
            // v = 2*x + (d-x)*1 = x + d
            // So, x = v - d
            int x = v - d;
            // x >= 0, so v >= d
            // Accelerated: x km, 1 min/km
            // Normal: (d-x) km, 2 min/km
            total_time += x * 1LL + (d - x) * 2LL;
        }
        if (total_time > t) return false; // Early exit if already over time
    }
    return total_time <= t;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k, s, t;
    cin >> n >> k >> s >> t;

    vector<pair<int, int>> cars(n); // {price, capacity}
    for (int i = 0; i < n; ++i) {
        cin >> cars[i].first >> cars[i].second;
    }

    vector<int> gas(k);
    for (int i = 0; i < k; ++i) {
        cin >> gas[i];
    }

    // Add start (0) and end (s) to gas stations, then sort
    gas.push_back(0);
    gas.push_back(s);
    sort(gas.begin(), gas.end());

    // Compute all segment lengths between consecutive gas stations
    vector<int> segs;
    for (int i = 1; i < (int)gas.size(); ++i) {
        segs.push_back(gas[i] - gas[i-1]);
    }

    // Find the minimum required tank capacity to even consider (max segment)
    int min_v = *max_element(segs.begin(), segs.end());

    // For all cars with v >= min_v, check if they can finish in time
    int answer = -1;
    for (const auto& car : cars) {
        int price = car.first, v = car.second;
        if (v < min_v) continue; // Can't even make the longest segment
        if (can_finish(segs, v, t)) {
            if (answer == -1 || price < answer) answer = price;
        }
    }

    cout << answer << '\n';
    return 0;
}