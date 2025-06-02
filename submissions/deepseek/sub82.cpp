#include <bits/stdc++.h>
using namespace std;

struct Breakfast {
    int A, C, L, R;
};

bool compareByCost(const Breakfast &a, const Breakfast &b) {
    return a.C < b.C;
}

int solve() {
    int N;
    cin >> N;
    vector<Breakfast> breakfasts(N);
    for (int i = 0; i < N; ++i) {
        cin >> breakfasts[i].A >> breakfasts[i].C >> breakfasts[i].L >> breakfasts[i].R;
    }
    
    // Sort by cost to process in increasing order of cost
    sort(breakfasts.begin(), breakfasts.end(), compareByCost);
    
    int changes = 0;
    int prev_max = INT_MIN; // Tracks the maximum A_i of previous breakfasts that are not changed
    
    for (int i = 0; i < N; ++i) {
        int current_A = breakfasts[i].A;
        int L = breakfasts[i].L;
        int R = breakfasts[i].R;
        
        // The current breakfast must have A_i > prev_max to avoid being dominated
        // We try to find the smallest possible A_i in [L, R] that is > prev_max
        if (current_A > prev_max) {
            // No need to change, but update prev_max to current_A
            prev_max = current_A;
        } else {
            // Need to change A_i to something > prev_max, if possible
            if (R > prev_max) {
                // The best is to set A_i to prev_max + 1 (or as low as possible to minimize future changes)
                prev_max = prev_max + 1;
                changes++;
            } else {
                // Impossible to satisfy the condition
                return -1;
            }
        }
        
        // Ensure that the new A_i is within [L, R]
        if (prev_max < L || prev_max > R) {
            return -1;
        }
    }
    
    return changes;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    while (T--) {
        cout << solve() << '\n';
    }
    
    return 0;
}