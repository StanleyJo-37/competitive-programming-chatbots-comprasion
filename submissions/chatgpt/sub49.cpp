#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n); // a[i]: the day after which tile i+1 is destroyed
    int max_a = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        if (a[i] > max_a) max_a = a[i];
    }

    int answer = 0;
    // For each day d from 1 up to max_a, check if walk is possible
    for (int day = 1; day <= max_a; ++day) {
        // Mark which tiles are undestroyed on this day
        vector<bool> ok(n, false);
        for (int i = 0; i < n; ++i) {
            if (a[i] >= day) ok[i] = true;
        }
        // If start or end tile is destroyed, break
        if (!ok[0] || !ok[n-1]) break;

        // BFS to check if we can reach from tile 1 to tile n
        vector<bool> visited(n, false);
        queue<int> q;
        q.push(0);
        visited[0] = true;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            // Try to move to u+1
            if (u+1 < n && ok[u+1] && !visited[u+1]) {
                visited[u+1] = true;
                q.push(u+1);
            }
            // Try to move to u+2
            if (u+2 < n && ok[u+2] && !visited[u+2]) {
                visited[u+2] = true;
                q.push(u+2);
            }
        }
        if (visited[n-1]) {
            ++answer;
        } else {
            break; // As soon as we can't reach, stop
        }
    }
    cout << answer << endl;
    return 0;
}