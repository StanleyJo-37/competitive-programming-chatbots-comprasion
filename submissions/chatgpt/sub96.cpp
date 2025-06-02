#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false); // Fast IO
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        // Read empty line before each test case (if present)
        // (In competitive programming, usually handled by reading line by line, but here we can ignore extra newlines)
        // So, we just proceed to read the test case.

        int k, n, m;
        cin >> k >> n >> m;
        vector<int> a(n), b(m);
        for (int i = 0; i < n; ++i) cin >> a[i];
        for (int i = 0; i < m; ++i) cin >> b[i];

        int i = 0, j = 0; // pointers for a and b
        int lines = k; // current number of lines in the file
        vector<int> res; // result sequence

        // We use a greedy two-pointer approach:
        // At each step, if either a[i] or b[j] is 0, we process that first (since adding a line increases lines and is always valid).
        // Otherwise, we process the first valid change (a[i] or b[j]) whose value <= lines.
        // If neither is possible, the sequence is invalid.

        while (i < n || j < m) {
            bool progress = false;
            // If Monocarp's next action is to add a line, do it
            if (i < n && a[i] == 0) {
                res.push_back(0);
                ++lines;
                ++i;
                progress = true;
            }
            // If Polycarp's next action is to add a line, do it
            else if (j < m && b[j] == 0) {
                res.push_back(0);
                ++lines;
                ++j;
                progress = true;
            }
            // If Monocarp's next action is to change a line that exists, do it
            else if (i < n && a[i] <= lines && a[i] > 0) {
                res.push_back(a[i]);
                ++i;
                progress = true;
            }
            // If Polycarp's next action is to change a line that exists, do it
            else if (j < m && b[j] <= lines && b[j] > 0) {
                res.push_back(b[j]);
                ++j;
                progress = true;
            }
            // If no progress can be made, the sequence is invalid
            if (!progress) {
                res.clear();
                res.push_back(-1);
                break;
            }
        }

        // Output the result for this test case
        for (size_t idx = 0; idx < res.size(); ++idx) {
            if (idx > 0) cout << ' ';
            cout << res[idx];
        }
        cout << '\n';
    }
    return 0;
}