#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, a, b, k;
    cin >> n >> a >> b >> k;
    vector<int> r(n);
    for (int i = 0; i < n; ++i) {
        cin >> r[i];
    }

    // Sort the ratings to process them in order
    sort(r.begin(), r.end());

    // Use a map to count occurrences of each rating
    unordered_map<int, int> count;
    for (int num : r) {
        count[num]++;
    }

    int teams = 0;
    // Iterate through each unique rating in sorted order
    for (int num : r) {
        if (count[num] == 0) continue; // Skip if already processed

        int target = num * k;
        if (target != num && count.find(target) != count.end()) {
            // Calculate how many teams can be formed with current num and target
            int possible = min(count[num] / a, count[target] / b);
            teams += possible;
            // Subtract the used players
            count[num] -= possible * a;
            count[target] -= possible * b;
        }
    }

    cout << teams << '\n';
    return 0;
}