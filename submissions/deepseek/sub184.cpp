#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 5;

int N, M;
int H[MAXN];
vector<int> visibleFrom[MAXN]; // For each i, stores all j > i visible from i
vector<int> queriesFor[MAXN];  // For each i, stores query indices where i is A or B
int ans[MAXN];                 // Stores answers for each query
int A[MAXN], B[MAXN];          // Stores queries

// Monotonic stack to compute visible stones for each position
void preprocess() {
    stack<int> st;
    for (int i = N; i >= 1; --i) {
        while (!st.empty() && H[i] >= H[st.top()]) {
            st.pop();
        }
        if (!st.empty()) {
            visibleFrom[i].push_back(st.top());
            // Now, check if there are more elements visible beyond st.top()
            // We need to find all j > i where H[j] > max(H[i+1..j-1])
            // Using the stack, we can find the next greater elements in order
            int last = st.top();
            while (!st.empty() && H[i] >= H[st.top()]) {
                st.pop();
            }
            if (!st.empty()) {
                visibleFrom[i].push_back(st.top());
            }
            st.push(last); // Restore the previous top
        } else {
            // No element to the right is taller, so only the last stone if it's taller
            if (i < N && H[N] > H[i]) {
                visibleFrom[i].push_back(N);
            }
        }
        st.push(i);
    }

    // Correct approach: For each i, find all j > i where H[j] > max(H[i+1..j-1])
    // This can be done using a monotonic stack from right to left
    for (int i = 1; i <= N; ++i) {
        visibleFrom[i].clear();
    }
    st = stack<int>();
    for (int i = N; i >= 1; --i) {
        while (!st.empty() && H[i] >= H[st.top()]) {
            st.pop();
        }
        if (!st.empty()) {
            visibleFrom[i].push_back(st.top());
        }
        st.push(i);
    }
}

// Binary search to find the number of common elements between two sorted lists
int countCommon(const vector<int>& a, const vector<int>& b) {
    int i = 0, j = 0;
    int common = 0;
    while (i < a.size() && j < b.size()) {
        if (a[i] == b[j]) {
            ++common;
            ++i;
            ++j;
        } else if (a[i] < b[j]) {
            ++i;
        } else {
            ++j;
        }
    }
    return common;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        cin >> N >> M;
        for (int i = 1; i <= N; ++i) {
            cin >> H[i];
            visibleFrom[i].clear();
            queriesFor[i].clear();
        }

        // Preprocess visibleFrom for each i
        stack<int> st;
        for (int i = N; i >= 1; --i) {
            while (!st.empty() && H[i] >= H[st.top()]) {
                st.pop();
            }
            if (!st.empty()) {
                visibleFrom[i].push_back(st.top());
            }
            st.push(i);
        }

        // For each i, collect all j > i where H[j] > max(H[i+1..j-1])
        // We need to traverse and collect all such j's
        for (int i = 1; i <= N; ++i) {
            visibleFrom[i].clear();
            int maxSoFar = 0;
            for (int j = i + 1; j <= N; ++j) {
                if (j == i + 1) {
                    maxSoFar = H[j - 1];
                } else {
                    maxSoFar = max(maxSoFar, H[j - 1]);
                }
                if (H[j] > maxSoFar) {
                    visibleFrom[i].push_back(j);
                }
            }
        }

        // Process queries
        for (int q = 0; q < M; ++q) {
            int a, b;
            cin >> a >> b;
            // Ensure a and b are in order for easier processing
            if (a > b) swap(a, b);
            // The common visible stones are those visible from both a and b, and are > max(a, b)
            vector<int> &va = visibleFrom[a];
            vector<int> &vb = visibleFrom[b];
            int common = 0;
            // Since both va and vb are in increasing order, we can merge
            int i = 0, j = 0;
            while (i < va.size() && j < vb.size()) {
                if (va[i] == vb[j]) {
                    ++common;
                    ++i;
                    ++j;
                } else if (va[i] < vb[j]) {
                    ++i;
                } else {
                    ++j;
                }
            }
            cout << common << '\n';
        }
    }

    return 0;
}