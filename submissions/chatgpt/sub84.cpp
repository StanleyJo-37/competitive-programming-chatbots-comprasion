#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t; // Number of test cases

    while (t--) {
        int n, m, k;
        cin >> n >> m >> k;
        string a, b;
        cin >> a >> b;

        // Sort both strings to get smallest lexicographical order
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());

        int i = 0, j = 0; // Pointers for a and b
        int cnt_a = 0, cnt_b = 0; // Consecutive picks from a and b
        string c; // Result string

        // Continue until either a or b is exhausted
        while (i < n && j < m) {
            // If we can pick from a and (either haven't reached k from a or b's char is bigger)
            if ((a[i] < b[j] && cnt_a < k) || cnt_b == k) {
                c += a[i];
                i++;
                cnt_a++;
                cnt_b = 0; // Reset b's consecutive count
            } else {
                // Otherwise, pick from b
                c += b[j];
                j++;
                cnt_b++;
                cnt_a = 0; // Reset a's consecutive count
            }
        }

        cout << c << '\n';
    }

    return 0;
}