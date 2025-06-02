#include <bits/stdc++.h>
using namespace std;

void solve() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n;
        scanf("%d", &n);
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            scanf("%d", &a[i]);
        }
        
        // The key observation is that if there exists at least one odd and one even number,
        // then any permutation can be achieved by adjacent swaps (since odd+even is odd).
        // Otherwise, the array must already be sorted.
        bool has_odd = false, has_even = false;
        for (int num : a) {
            if (num % 2 == 0) {
                has_even = true;
            } else {
                has_odd = true;
            }
            if (has_odd && has_even) break;
        }
        
        if (has_odd && has_even) {
            // If both odd and even exist, it's always possible to sort.
            printf("Yes\n");
        } else {
            // Otherwise, check if the array is already sorted.
            bool sorted = true;
            for (int i = 1; i < n; ++i) {
                if (a[i] < a[i-1]) {
                    sorted = false;
                    break;
                }
            }
            printf(sorted ? "Yes\n" : "No\n");
        }
    }
}

int main() {
    solve();
    return 0;
}