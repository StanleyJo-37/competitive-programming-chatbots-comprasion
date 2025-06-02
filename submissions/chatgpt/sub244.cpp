#include <iostream>
#include <vector>
#include <set>
using namespace std;

// This problem can be solved efficiently by observing that the "hardness" is
// always 1 + the maximum number of consecutive 'in circulation' coins (X) at the end of the row.
// This is because, after each pass, all X's at the end are already in place and will not move anymore.
// So, the number of passes needed is 1 + (number of X's not at the end).
// We can maintain the set of positions of X's and always check the largest suffix of X's at the end.

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i];
        --p[i]; // convert to 0-based index
    }

    // Initially, all coins are out of circulation, so hardness is 1
    vector<int> ans;
    ans.reserve(n + 1);
    ans.push_back(1);

    // We use a set to keep track of positions of coins in circulation (X)
    set<int> in_circulation;

    // We also keep track of the length of the suffix of X's at the end
    int suffix = 0;

    // For each step, we add a new X at position p[i]
    for (int i = 0; i < n; ++i) {
        in_circulation.insert(p[i]);
        // Update the suffix: check if the last coin is X, then the one before, etc.
        // Since only one coin is added at a time, we can increment suffix if p[i] == n-1-suffix
        while (in_circulation.count(n - 1 - suffix)) {
            ++suffix;
        }
        // The hardness is 1 + (number of X's not at the end) = 1 + (total X's - suffix)
        ans.push_back(1 + (int)in_circulation.size() - suffix);
    }

    // Output the answer
    for (int i = 0; i <= n; ++i) {
        cout << ans[i] << (i == n ? '\n' : ' ');
    }
    return 0;
}