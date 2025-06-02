#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

// Function to check if it's possible to place marks with at least 'd' distance apart
bool isPossible(ll d, const vector<pair<ll, ll>>& intervals, ll M) {
    ll prev = -1e18; // Initialize to negative infinity to handle the first interval
    int n = intervals.size();
    
    for (int i = 0; i < n; ++i) {
        ll L = intervals[i].first;
        ll R = intervals[i].second;
        
        // The earliest we can place the current mark is max(L, prev + d)
        ll current = max(L, prev + d);
        
        // If it's not possible to place within the interval, return false
        if (current > R) {
            return false;
        }
        
        prev = current;
    }
    
    // After placing all marks, check the circular condition (distance between first and last)
    // The distance between the first and last mark should also be at least 'd'
    // Since the circle wraps around, the distance is min(A1 - An + M, An - A1)
    // But since the intervals are non-overlapping and sorted, we can just check (A1 + M - An) >= d
    if (intervals.size() >= 2) {
        ll first_mark = max(intervals[0].first, intervals[0].first); // First mark is placed as left as possible
        first_mark = max(intervals[0].first, intervals[0].first); // Redundant, just for clarity
        // Recompute prev for the first interval (since prev is updated in the loop)
        prev = -1e18;
        for (int i = 0; i < n; ++i) {
            ll L = intervals[i].first;
            ll R = intervals[i].second;
            ll current = max(L, prev + d);
            prev = current;
        }
        ll wrap_distance = (prev - first_mark + M) % M;
        if (wrap_distance < d) {
            return false;
        }
    }
    
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll M;
    int N;
    cin >> M >> N;
    
    vector<pair<ll, ll>> intervals(N);
    for (int i = 0; i < N; ++i) {
        cin >> intervals[i].first >> intervals[i].second;
    }
    
    // Binary search for the maximum possible minimum distance
    ll left = 0;
    ll right = M;
    ll answer = 0;
    
    while (left <= right) {
        ll mid = left + (right - left) / 2;
        if (isPossible(mid, intervals, M)) {
            answer = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    cout << answer << endl;
    
    return 0;
}