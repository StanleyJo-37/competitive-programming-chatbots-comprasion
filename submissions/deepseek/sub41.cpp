#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
    int n, t, k;
    cin >> n >> t >> k;

    vector<long long> a(n), b(n), c(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i] >> b[i] >> c[i];
    }

    // We need to find the minimal number of trains such that for all hours up to t,
    // the number of people at each station does not exceed c_i.
    // The key observation is that for each station i, the number of people at hour h is:
    // a_i + h * b_i - sum of people taken by trains up to hour h.
    // The challenge is to ensure that this value never exceeds c_i at any hour h <= t.

    // Binary search the minimal number of trains needed.
    long long left = 0, right = 1e18, answer = 1e18;
    while (left <= right) {
        long long mid = (left + right) / 2;
        bool possible = true;

        // For each station, check if it's possible to distribute 'mid' trains over t hours
        // such that the station's capacity is not exceeded at any hour.
        for (int i = 0; i < n; ++i) {
            // The maximum people that can be at station i at any hour h is c_i.
            // The people at hour h is a_i + h * b_i - sum of taken people by hour h.
            // The sum of taken people by hour h must be >= a_i + h * b_i - c_i for all h <= t.
            // But also, the sum of taken people by hour h must be <= a_i + h * b_i (non-negative).
            // The total taken people by all trains is <= mid * k.
            // For station i, the minimal required sum of taken people by hour t is:
            // max(0, a_i + t * b_i - c_i)
            // But we also need to ensure that for every hour h <= t, the sum up to hour h is >= a_i + h * b_i - c_i.
            // The worst case is when h = t, because a_i + h * b_i increases with h.
            // So, the minimal required sum of taken people by hour t is max(0, a_i + t * b_i - c_i).
            // The total sum of taken people across all stations must be <= mid * k.
            // Additionally, for each station, the sum of taken people must be >= max(0, a_i + t * b_i - c_i).
            // But we also need to ensure that for every hour h < t, the sum up to hour h is >= a_i + h * b_i - c_i.
            // However, since the sum of taken people is non-decreasing, the worst case is at h = t.
            // So, the minimal required sum for station i is max(0, a_i + t * b_i - c_i).
            // The sum of all these minimal required sums must be <= mid * k.
            long long required = max(0LL, a[i] + t * b[i] - c[i]);
            if (required > mid * k) {
                possible = false;
                break;
            }
        }

        if (possible) {
            // Now, we need to ensure that for every station i and every hour h <= t,
            // the sum of taken people up to hour h is >= max(0, a_i + h * b_i - c_i).
            // To satisfy this, we need to distribute the trains such that the sum up to hour h
            // is at least the maximum of (a_i + h * b_i - c_i) over all stations i.
            // This is complex, but we can model it as follows:
            // For each hour h, the sum of trains up to hour h must be >= the maximum over all stations i of
            // ceil( (max(0, a_i + h * b_i - c_i)) / k ).
            // But since we have mid trains in total, we need to distribute them such that for each h,
            // the sum of trains up to hour h is >= the required for that h.
            // This is a scheduling problem where we need to assign trains to hours such that the prefix sums
            // are sufficient to cover the required for each hour.
            // We can compute the minimal required trains for each hour h as:
            // max over all stations i of ceil( max(0, a_i + h * b_i - c_i) / k )
            // Then, the sum of trains up to hour h must be >= this value for all h <= t.
            // The total sum of trains must be >= the value for h = t.
            // We need to check if mid is >= the maximum of the required trains for any hour h <= t.
            // But since we already checked that sum of required sums is <= mid * k, we need to ensure that
            // the distribution is possible.
            // The minimal number of trains is the maximum over h of ceil( (max over i of (a_i + h * b_i - c_i)) / k ).
            long long max_trains = 0;
            for (int h = 1; h <= t; ++h) {
                long long current_max = 0;
                for (int i = 0; i < n; ++i) {
                    long long value = max(0LL, a[i] + h * b[i] - c[i]);
                    current_max = max(current_max, (value + k - 1) / k);
                }
                max_trains = max(max_trains, current_max);
            }
            if (max_trains <= mid) {
                answer = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        } else {
            left = mid + 1;
        }
    }

    cout << answer << endl;

    return 0;
}