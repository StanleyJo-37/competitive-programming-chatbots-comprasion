#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i];
    }
    
    // To check if the permutation is valid, we need to ensure that for each position i,
    // the next element (i+1) is either to the right of i or in a position that could have been chosen
    // by the generator's rules. The key observation is that the permutation must be a sequence of
    // increasing runs where each run's next element is either immediately to the right or
    // the next element is the smallest possible in the remaining positions.
    // Essentially, the permutation must be decomposable into a series of rightmost or leftmost choices.
    
    // The main idea is to check for each element x, the next element x+1 must be either to the right of x
    // or in a position that could have been chosen by the generator's rules (i.e., x+1 must be in a position
    // that was a candidate for maximum count at the time of placement).
    // However, a simpler approach is to check that for each x, the position of x+1 is either to the right of x
    // or all elements between x and x+1 are larger than x.
    
    vector<int> pos(n + 1);
    for (int i = 0; i < n; ++i) {
        pos[p[i]] = i;
    }
    
    for (int i = 1; i < n; ++i) {
        if (pos[i + 1] < pos[i] && (i + 1 > n || p[pos[i] + 1] > i + 1)) {
            cout << "No\n";
            return;
        }
    }
    cout << "Yes\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}