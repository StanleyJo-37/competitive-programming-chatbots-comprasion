#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Function to check if it's possible to select one number from each interval
// such that the minimum distance between any two selected numbers is at least 'd'
bool is_possible(const vector<pair<long long, long long>>& intervals, long long M, long long d) {
    int N = intervals.size();
    vector<long long> chosen(N); // chosen[i] is the selected number in interval i

    // Try all possible starting points in the first interval
    // Since the circle is symmetric, we can fix the first point at the leftmost possible
    // and check if the rest can be placed accordingly.
    // This is sufficient because the intervals are non-overlapping and ordered.
    long long start = intervals[0].first;
    chosen[0] = start;

    // Place each next point as early as possible, but at least 'd' away from the previous
    for (int i = 1; i < N; ++i) {
        // The earliest we can place the next point is either the left of the interval,
        // or at least 'd' away from the previous chosen point (modulo M)
        long long prev = chosen[i-1];
        long long min_pos = max(intervals[i].first, prev + d);
        if (min_pos > intervals[i].second) {
            // Can't place in this interval
            return false;
        }
        chosen[i] = min_pos;
    }

    // Now, check the circular constraint: the last and first chosen points must also be at least 'd' apart
    // The distance on the circle between chosen[0] and chosen[N-1] is:
    // min((chosen[0] - chosen[N-1] + M) % M, (chosen[N-1] - chosen[0] + M) % M)
    // But since we always go forward, we want (chosen[0] + M - chosen[N-1]) % M >= d
    // and (chosen[N-1] + M - chosen[0]) % M >= d
    // But since we always place forward, we only need to check the wrap-around:
    long long wrap_dist = (chosen[0] + M - chosen[N-1]) % M;
    if (wrap_dist < d) {
        // Try to shift the first point forward within its interval to increase the wrap distance
        // The maximum we can shift is intervals[0].second
        long long max_shift = intervals[0].second - chosen[0];
        long long needed_shift = d - wrap_dist;
        if (needed_shift > max_shift) {
            return false;
        }
        // Try shifting the first point and propagate the shift to the rest
        chosen[0] += needed_shift;
        for (int i = 1; i < N; ++i) {
            long long min_pos = max(intervals[i].first, chosen[i-1] + d);
            if (min_pos > intervals[i].second) {
                return false;
            }
            chosen[i] = min_pos;
        }
        wrap_dist = (chosen[0] + M - chosen[N-1]) % M;
        if (wrap_dist < d) {
            return false;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long M;
    int N;
    cin >> M >> N;
    vector<pair<long long, long long>> intervals(N);
    for (int i = 0; i < N; ++i) {
        cin >> intervals[i].first >> intervals[i].second;
    }

    // Binary search for the maximum possible minimum distance
    long long left = 1, right = M / N, answer = 1;
    // The maximum possible minimum distance is at most M / N (if intervals allow)
    while (left <= right) {
        long long mid = left + (right - left) / 2;
        if (is_possible(intervals, M, mid)) {
            answer = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    cout << answer << '\n';
    return 0;
}