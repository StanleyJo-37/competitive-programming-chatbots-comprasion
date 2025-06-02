#include <bits/stdc++.h>
using namespace std;

// Fast input/output
ios_base::sync_with_stdio(false);
cin.tie(nullptr);

// Function to process each test case
void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> pos(n + 1); // pos[x] = position of value x in a (1-based)
    vector<int> cnt(n + 1, 0); // count of each value in a

    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        cnt[a[i]]++;
        pos[a[i]] = i;
    }

    // If a is not a permutation, then k=1 is not happy
    bool is_perm = true;
    for (int i = 1; i <= n; ++i) {
        if (cnt[i] != 1) {
            is_perm = false;
            break;
        }
    }

    // For k=n, the k-compression is always [min(a)], which is a permutation iff a contains all numbers 1..n
    // But for k=n, b=[min(a)] and min(a) must be 1, and n=1, so always happy if n=1

    // We want to find for each k, if the k-compression is a permutation of length n-k+1

    // The key observation:
    // For k=n, the only window is the whole array, so b=[min(a)].
    // For k=1, b=a, so b is a permutation iff a is a permutation.
    // For k from 1 to n, the k-compression is a permutation iff for all windows of length k, the minimums are all distinct and cover 1..n-k+1.

    // But that's too slow. Instead, we can use the following:
    // The only way for k-compression to be a permutation is if the minimum in each window is unique and covers all values from 1 to n-k+1.

    // Let's process the minimal segment that contains all values from 1 to n
    // For each value x from 1 to n, we know its position in a (pos[x])
    // The minimal segment that contains all values from 1 to n is from min(pos[1..n]) to max(pos[1..n])
    // For k=n, the only window is the whole array, so always happy if a is a permutation

    // Let's process the answer for all k in O(n) time

    // We will use two pointers to maintain the minimal segment that contains all values from 1 to x
    int l = n, r = -1;
    vector<char> ans(n, '0');

    // For k=n, always happy if a is a permutation
    if (is_perm) ans[n - 1] = '1';

    // For k=1, happy iff a is a permutation
    if (is_perm) ans[0] = '1';

    // Now, for k from n down to 2, we check if the segment containing all values from 1 to x is of length x
    // That is, for x from 1 to n, we update l and r to min/max(pos[x]), and if r-l+1 == x, then for k=n-x+1, the k-compression is a permutation
    l = n, r = -1;
    vector<int> where(n + 1);
    for (int i = 0; i < n; ++i) where[a[i]] = i;
    for (int x = 1; x <= n; ++x) {
        l = min(l, where[x]);
        r = max(r, where[x]);
        if (r - l + 1 == x) {
            // For k = n - x + 1, the k-compression is a permutation
            ans[n - x] = '1';
        }
    }

    // Output the answer
    for (char c : ans) cout << c;
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}