#include <bits/stdc++.h>
using namespace std;

void solve() {
    int N;
    cin >> N;
    vector<int> B(2 * N);
    for (int i = 0; i < 2 * N; ++i) {
        cin >> B[i];
    }
    
    // The smallest and largest elements in A must appear exactly once in B.
    // The rest must appear exactly twice (once in prefix medians and once in suffix medians).
    // Also, the first N elements of B must be non-decreasing (prefix medians) and the last N must be non-increasing (suffix medians).
    // The first N elements should be the medians of the prefixes of A, and the last N should be the medians of the suffixes of A.
    // The first N elements should be the first N elements of B sorted, and the last N should be the last N elements of B sorted in reverse.
    // The first N and last N must be symmetric in a way that the first N's last element is the same as the last N's first element (the median of the full array).
    
    // Check if the first N elements are non-decreasing and the last N are non-increasing.
    bool valid = true;
    for (int i = 1; i < N; ++i) {
        if (B[i] < B[i-1]) {
            valid = false;
            break;
        }
    }
    for (int i = N + 1; i < 2 * N; ++i) {
        if (B[i] > B[i-1]) {
            valid = false;
            break;
        }
    }
    if (!valid) {
        cout << -1 << "\n";
        return;
    }
    
    // The median of the full array (A's median) must be the same in both prefix and suffix parts.
    if (B[N-1] != B[N]) {
        cout << -1 << "\n";
        return;
    }
    
    // The first N elements (prefix medians) must be the same as the last N elements (suffix medians) when reversed.
    // Also, the first N-1 elements should be <= the median, and the last N-1 elements should be >= the median.
    for (int i = 0; i < N; ++i) {
        if (B[i] != B[2*N - 1 - i]) {
            valid = false;
            break;
        }
    }
    if (!valid) {
        cout << -1 << "\n";
        return;
    }
    
    // Now, construct A. The smallest element in A is B[0], and the largest is B[2*N-1].
    // The middle element is B[N-1] (or B[N]).
    // The elements in A must be distinct and sorted.
    // The prefix medians are the first N elements of B, and the suffix medians are the last N elements.
    // The first N elements of B should be the medians of the prefixes of A, which means:
    // For odd-length prefixes, the median is the middle element.
    // For even-length prefixes, the median is the left middle element.
    // So, the first N elements of B should be the medians of A[0..0], A[0..1], ..., A[0..N-1].
    // Similarly, the last N elements of B should be the medians of A[N-1..N-1], A[N-2..N-1], ..., A[0..N-1].
    
    // To construct A, we can observe that the first N elements of B must contain all elements of A except the largest,
    // and the last N elements must contain all elements of A except the smallest.
    // The smallest element in A is B[0], and the largest is B[2*N-1].
    // The middle element is B[N-1].
    // The other elements must appear exactly twice in B (once in prefix and once in suffix).
    
    map<int, int> freq;
    for (int num : B) {
        freq[num]++;
    }
    
    vector<int> A;
    A.push_back(B[0]); // The smallest element in A.
    for (auto it = freq.begin(); it != freq.end(); ++it) {
        if (it->first == B[0] || it->first == B[2*N - 1]) {
            if (it->second != 1) {
                cout << -1 << "\n";
                return;
            }
        } else {
            if (it->second != 2) {
                cout << -1 << "\n";
                return;
            }
            A.push_back(it->first);
        }
    }
    A.push_back(B[2*N - 1]); // The largest element in A.
    
    // Now, verify that the constructed A's prefix and suffix medians match B.
    // Check prefix medians.
    for (int i = 1; i <= N; ++i) {
        int median;
        if (i % 2 == 1) {
            median = A[i / 2];
        } else {
            median = A[i / 2 - 1];
        }
        if (median != B[i - 1]) {
            cout << -1 << "\n";
            return;
        }
    }
    
    // Check suffix medians.
    for (int i = 1; i <= N; ++i) {
        int len = i;
        int median;
        if (len % 2 == 1) {
            median = A[N - 1 - (len / 2)];
        } else {
            median = A[N - 1 - (len / 2 - 1)];
        }
        if (median != B[2*N - i]) {
            cout << -1 << "\n";
            return;
        }
    }
    
    // Output A.
    for (int num : A) {
        cout << num << " ";
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    
    return 0;
}