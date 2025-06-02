#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        vector<int> B(2 * N);
        for (int i = 0; i < 2 * N; ++i) {
            cin >> B[i];
        }

        // Count frequency of each element in B
        map<int, int> freq;
        for (int x : B) freq[x]++;

        // For a valid A, the sorted A = [a1, a2, ..., aN] (distinct, sorted)
        // The medians of prefixes and suffixes are:
        // Prefixes: median of [a1], [a1,a2], ..., [a1,...,aN]
        // Suffixes: median of [aN], [aN-1,aN], ..., [a1,...,aN]
        // For odd k, median is at (k/2)th index (0-based) in sorted array
        // For even k, median is at (k/2-1)th index (0-based) in sorted array

        // Let's try to reconstruct A from B:
        // Since A is sorted and distinct, let's try to find the N elements
        // whose frequencies in B match the expected pattern.

        // For A = [a1, a2, ..., aN] (sorted, distinct)
        // The frequency of ai in B is:
        // - For ai at position i (0-based), its frequency is:
        //   freq(ai) = (i+1 >= N-i) ? (N-i) + (i+1) : (N-i) + (i+1)
        // But let's check the pattern for small N:
        // For N=3, A=[a1,a2,a3]:
        // Prefix medians: [a1], [a1,a2], [a1,a2,a3] => a1, a1, a2
        // Suffix medians: [a3], [a2,a3], [a1,a2,a3] => a3, a2, a2
        // So freq(a1)=2, freq(a2)=3, freq(a3)=1

        // For general N:
        // - The smallest element (a1) appears in prefix medians for k=1,2,...,N where median is a1
        //   That is, for k=1 (prefix of length 1), median is a1
        //   For k=2, median is a1 (since [a1,a2], median is a1)
        //   For k=3, median is a2 ([a1,a2,a3], median is a2)
        //   For k=4, median is a2 ([a1,a2,a3,a4], median is a2)
        //   For k=5, median is a3 ([a1,a2,a3,a4,a5], median is a3)
        //   So, for each ai, its frequency in B is:
        //   freq(ai) = min(i+1, N-i) + min(i+1, N-i)
        //   But from the pattern, for ai at position i (0-based):
        //   freq(ai) = min(i+1, N-i) + min(N-i, i+1)
        //   Actually, for ai at position i (0-based), freq(ai) = 2 * min(i+1, N-i)
        //   But for the middle element (if N is odd), it appears in both prefix and suffix medians at the same time, so freq(ai) = N if i == N/2

        // Let's build the expected frequency for each position:
        vector<int> expected_freq(N);
        for (int i = 0; i < N; ++i) {
            int left = i + 1;
            int right = N - i;
            expected_freq[i] = min(left, right) * 2;
        }
        if (N % 2 == 1) {
            // For the middle element, it is counted twice, so subtract 1
            expected_freq[N/2]--;
        }

        // Now, sort B and try to assign the expected frequencies
        sort(B.begin(), B.end());
        vector<int> A;
        int idx = 0;
        bool valid = true;
        for (int i = 0; i < N; ++i) {
            int cnt = 1;
            while (idx + cnt < 2*N && B[idx+cnt] == B[idx]) cnt++;
            if (cnt != expected_freq[i]) {
                valid = false;
                break;
            }
            A.push_back(B[idx]);
            idx += cnt;
        }
        if (!valid || idx != 2*N) {
            cout << -1 << '\n';
        } else {
            for (int i = 0; i < N; ++i) {
                cout << A[i] << (i+1==N ? '\n' : ' ');
            }
        }
    }
    return 0;
}