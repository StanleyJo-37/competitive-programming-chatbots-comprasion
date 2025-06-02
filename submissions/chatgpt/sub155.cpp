#include <iostream>
using namespace std;

// This function handles a single test case of the interactive problem.
void solve_case() {
    int n, k;
    cin >> n >> k; // Read n and k (k is always 2 in this version)
    int acc = 0;   // acc will keep track of the cumulative XOR of all previous queries

    // We can guarantee to find the password in at most n queries
    for (int i = 0; i < n; ++i) {
        // The query is (i ^ acc). This ensures that after each query,
        // the new password is always 0 if the original password was 0.
        // This is because after each query, the password is updated as:
        // new_password = old_password ^ (i ^ acc)
        // If old_password is 0, then new_password = i ^ acc
        // We set acc = acc ^ (i ^ acc) = i, so after i-th query, acc == i
        int query = i ^ acc;
        cout << query << endl;
        cout.flush();

        int r;
        cin >> r; // Read the response from the interactor

        if (r == 1) {
            // Correct guess, break out of the loop for this test case
            break;
        }
        if (r == -1) {
            // Invalid query or exceeded number of queries, exit immediately
            exit(0);
        }
        // Update acc for the next query
        acc ^= query;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t; // Read number of test cases
    while (t--) {
        solve_case();
    }
    return 0;
}