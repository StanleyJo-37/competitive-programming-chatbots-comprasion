#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false); // Fast IO
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        vector<int> A(N);
        unordered_map<int, int> freq; // Frequency of each element

        for (int i = 0; i < N; ++i) {
            cin >> A[i];
            freq[A[i]]++;
        }

        // Find the maximum frequency (F(A)) and collect all frequencies
        int maxFreq = 0;
        vector<int> freqList;
        for (auto &p : freq) {
            freqList.push_back(p.second);
            if (p.second > maxFreq) maxFreq = p.second;
        }

        // If all elements are the same, after operation, we can split them into two values as evenly as possible
        if (freq.size() == 1) {
            // Split into two values: ceil(N/2) and floor(N/2)
            int minF = (N + 1) / 2;
            cout << minF << '\n';
            continue;
        }

        // Otherwise, try to minimize the maximum frequency after one operation
        // The best we can do is to reduce the highest frequency by moving some of its elements to another value
        // For each value with maxFreq, try to move k of its elements to another value (possibly a new value)
        // The minimum possible F(A) is max(maxFreq - k, secondMaxFreq + k), for 0 <= k <= freq[x]
        // But since we can move all of freq[x] to a new value, the best is to split freq[x] as evenly as possible

        // Find the two largest frequencies
        sort(freqList.begin(), freqList.end(), greater<int>());
        int f1 = freqList[0]; // largest frequency
        int f2 = freqList[1]; // second largest frequency

        // The optimal is to split f1 into two groups as evenly as possible
        // So, after operation, the two largest frequencies will be:
        // max(ceil(f1/2), f2)
        int minF = max((f1 + 1) / 2, f2);

        cout << minF << '\n';
    }
    return 0;
}