#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false); // Fast IO
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int &x : a) cin >> x;

        // The key observation:
        // Each swap flips the direction of both involved friends.
        // To have all directions right at the end, each friend must be swapped even number of times.
        // Swapping is only possible between adjacent friends.
        // This means: the parity (even/odd) of the position of each number in the original and sorted array must match.
        // If not, it's impossible.

        vector<int> b = a; // Copy of a
        sort(b.begin(), b.end()); // Sorted array

        // For each parity (even/odd index), count the occurrences of each number
        // We use two maps for each parity, but since values are up to 1e5, we use arrays for speed.
        // cnt_a[0][x] = count of x at even indices in a
        // cnt_a[1][x] = count of x at odd indices in a
        // Similarly for cnt_b

        // Since a_i <= 1e5, we can use arrays of size 1e5+1
        const int MAXV = 100005;
        vector<int> cnt_a_even(MAXV, 0), cnt_a_odd(MAXV, 0);
        vector<int> cnt_b_even(MAXV, 0), cnt_b_odd(MAXV, 0);

        for (int i = 0; i < n; ++i) {
            if (i % 2 == 0)
                cnt_a_even[a[i]]++;
            else
                cnt_a_odd[a[i]]++;
        }
        for (int i = 0; i < n; ++i) {
            if (i % 2 == 0)
                cnt_b_even[b[i]]++;
            else
                cnt_b_odd[b[i]]++;
        }

        // Now, for each value, the count at even and odd positions must match between a and b
        bool possible = true;
        for (int v = 1; v < MAXV; ++v) {
            if (cnt_a_even[v] != cnt_b_even[v] || cnt_a_odd[v] != cnt_b_odd[v]) {
                possible = false;
                break;
            }
        }

        cout << (possible ? "YES" : "NO") << '\n';
    }
    return 0;
}