#include <iostream>
#include <vector>
using namespace std;

int main() {
    int t;
    cin >> t; // Number of test cases
    while (t--) {
        int n;
        cin >> n; // Number of teams

        // We need to output n*(n-1)/2 results for each test case
        vector<int> res;

        // For each pair (i, j) with i < j, determine the result
        // The result is:
        // 1  : i beats j
        // -1 : j beats i
        // 0  : tie

        // The idea is to minimize the number of ties.
        // For even n, each team must have the same number of wins and losses, and 1 tie.
        // For odd n, each team can have (n-1)/2 wins and (n-1)/2 losses, and 0 ties.

        // For each i < j, we decide the result as follows:
        // For each team i, it will win against the next (n-1)/2 teams (in a circular manner),
        // lose to the previous (n-1)/2 teams, and tie with the remaining (if n is even).

        for (int i = 0; i < n; ++i) {
            for (int j = i+1; j < n; ++j) {
                int d = j - i;
                // For circularity, if d > n/2, then i should lose to j
                // For even n, if d == n/2, it's a tie
                if (n % 2 == 0 && d == n/2) {
                    res.push_back(0); // tie
                } else if (d < (n+1)/2) {
                    res.push_back(1); // i beats j
                } else {
                    res.push_back(-1); // j beats i
                }
            }
        }

        // Output the results for this test case
        for (size_t i = 0; i < res.size(); ++i) {
            cout << res[i];
            if (i + 1 != res.size()) cout << " ";
        }
        cout << endl;
    }
    return 0;
}