#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    // The walk is possible until the minimum of:
    // 1. The earliest day any of the tiles 1 or n is destroyed (since the walk starts at 1 and ends at n).
    // 2. The earliest day when the path from 1 to n is blocked due to intermediate tiles being destroyed.
    // We need to find the maximum day 'd' such that for all days <= 'd', the path exists.
    // The answer is the minimum of the above two conditions.

    // The maximum possible day is the minimum of a[0] and a[n-1] (tiles 1 and n).
    // But we also need to ensure that the path exists for all days <= 'd'.
    // So, for each day 'd' from 1 upwards, check if:
    // 1. a[0] >= d and a[n-1] >= d.
    // 2. There exists a path from 1 to n where all tiles in the path have a[i] >= d.

    // To optimize, we can binary search the maximum 'd' that satisfies both conditions.
    // The answer will be the maximum such 'd'.

    int left = 1;
    int right = min(a[0], a[n-1]);
    int answer = 0;

    while (left <= right) {
        int mid = (left + right) / 2;
        bool pathExists = false;

        // Check if there's a path from 1 to n with all a[i] >= mid.
        // We can use a simple DP approach or greedy.
        // Here, we use a greedy approach to check reachability.
        vector<bool> reachable(n, false);
        reachable[0] = (a[0] >= mid);
        for (int i = 1; i < n; ++i) {
            if (a[i] < mid) continue;
            if (i >= 1 && reachable[i-1]) reachable[i] = true;
            if (i >= 2 && reachable[i-2]) reachable[i] = true;
        }

        if (reachable[n-1]) {
            answer = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    cout << answer << endl;
    return 0;
}