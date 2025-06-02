#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Function to compute minimum removals to make S dense
int minRemovalsToDense(const string& S) {
    int N = S.size();
    // dp[i][j]: min removals to make S[i..j] dense
    // But since dense can only be empty or (X), we only need to check if S is of the form (X)
    // So, we can use a greedy approach:
    // Try to find the longest prefix of the form (X), i.e., S = '(' + dense + ')'
    // For each possible dense substring, check if S = '(' + X + ')', where X is dense
    // But since only one layer of wrapping is allowed, the only possible dense substrings are:
    // - empty string
    // - (dense)
    // So, the only way to make S dense is to remove brackets to make it of the form (((...)))
    // i.e., a sequence of k '(' followed by k ')'
    // So, for each possible k, check if S can be converted to k '(' + k ')'
    // The minimum removals is N - 2*k, where k is the maximum number of matching pairs that can be nested

    // Count the maximum number of nested pairs
    int maxNest = 0, curNest = 0;
    for (char c : S) {
        if (c == '(') {
            curNest++;
            if (curNest > maxNest) maxNest = curNest;
        } else {
            if (curNest > 0) curNest--;
        }
    }

    // Now, to maximize the number of nested pairs, we need to find the maximum k such that
    // we can select k '(' and k ')' to form (((...)))
    // Let's use a two pointer approach to find the maximum k
    int left = 0, right = N - 1;
    int k = 0;
    while (left < right) {
        // Find next '(' from left
        while (left < N && S[left] != '(') left++;
        // Find next ')' from right
        while (right >= 0 && S[right] != ')') right--;
        if (left < right) {
            k++;
            left++;
            right--;
        }
    }
    // The minimum removals is N - 2*k
    return N - 2 * k;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        string S;
        cin >> S;
        // Output the minimum number of removals for this test case
        cout << minRemovalsToDense(S) << '\n';
    }
    return 0;
}