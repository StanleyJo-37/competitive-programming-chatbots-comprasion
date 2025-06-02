#include <bits/stdc++.h>
using namespace std;

// For fast input/output
ios_base::sync_with_stdio(false);
cin.tie(NULL);

// Main function
int main() {
    int T;
    cin >> T;
    while (T--) {
        int N, M;
        cin >> N >> M;
        vector<int> H(N);
        for (int i = 0; i < N; ++i) cin >> H[i];

        // For each stone, store the list of visible stones (indices)
        vector<vector<int>> visible(N);

        // For each stone, use a monotonic stack to find visible stones to the right
        // visible[i] will contain all j > i such that stone j is visible from i
        for (int i = 0; i < N; ++i) {
            int maxh = H[i];
            // Use a stack to keep track of the highest stone so far
            // We only need to check stones to the right of i
            int curr_max = H[i];
            for (int j = i + 1; j < N; ++j) {
                // If all previous stones between i and j are less than H[j], then H[j] is visible
                if (curr_max < H[j]) {
                    visible[i].push_back(j);
                    curr_max = H[j];
                }
            }
        }

        // For each query, we need to find the intersection of visible[A-1] and visible[B-1]
        // Since the lists are sorted, we can use two pointers to find the intersection efficiently
        while (M--) {
            int A, B;
            cin >> A >> B;
            --A; --B; // Convert to 0-based index

            // Use two pointers to find intersection
            int cnt = 0;
            int i = 0, j = 0;
            vector<int>& va = visible[A];
            vector<int>& vb = visible[B];
            while (i < va.size() && j < vb.size()) {
                if (va[i] == vb[j]) {
                    ++cnt;
                    ++i; ++j;
                } else if (va[i] < vb[j]) {
                    ++i;
                } else {
                    ++j;
                }
            }
            cout << cnt << '\n';
        }
    }
    return 0;
}