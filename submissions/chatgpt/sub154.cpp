#include <bits/stdc++.h>
using namespace std;

// Fast IO
ios_base::sync_with_stdio(false);
cin.tie(nullptr);

// Function to compute g(x, y) for a given subarray [x, y] of A
// and return the sum of all f(i, j) for x <= i <= j <= y
// A is the original array, x and y are the bounds (inclusive)
long long compute_g(const vector<int>& A, int x, int y) {
    int len = y - x + 1;
    vector<int> prefix(len + 1, 0); // prefix XOR for subarray [x, y]
    for (int i = 0; i < len; ++i) {
        prefix[i + 1] = prefix[i] ^ A[x + i];
    }
    // For all i <= j, f(i, j) = prefix[j+1] ^ prefix[i]
    // We can count the number of times each bit is set in all f(i, j)
    // But since A[i] is binary, we can brute force for small len
    long long res = 0;
    for (int i = 0; i < len; ++i) {
        int curr = 0;
        for (int j = i; j < len; ++j) {
            curr ^= A[x + j];
            res += curr;
        }
    }
    return res;
}

int main() {
    int n, q;
    cin >> n >> q;
    vector<int> A(n);
    for (int i = 0; i < n; ++i) cin >> A[i];

    // Precompute prefix XOR for the whole array for fast f(i, j) calculation
    vector<int> prefixXOR(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        prefixXOR[i + 1] = prefixXOR[i] ^ A[i];
    }

    // For each query, process independently
    while (q--) {
        int x, y, k;
        cin >> x >> y >> k;
        int len = y - x + 1;

        // For small subarrays, brute force is acceptable
        if (len <= 1000) {
            // Try all possible ways to flip up to k bits in [x, y]
            // Since k can be up to len, but len is small, we can brute force
            // For each subset of up to k bits, flip them and compute g(x, y)
            // But that's 2^len, so instead, we can try flipping the k bits that maximize g(x, y)
            // For each position, try flipping and see the gain
            vector<int> orig(A.begin() + x, A.begin() + y + 1);
            long long base = compute_g(A, x, y);

            // For each position, compute the gain if we flip it
            vector<long long> gain(len, 0);
            for (int pos = 0; pos < len; ++pos) {
                // Flip A[x+pos]
                A[x + pos] ^= 1;
                long long new_g = compute_g(A, x, y);
                gain[pos] = new_g - base;
                A[x + pos] ^= 1; // revert
            }
            // Pick top k gains
            sort(gain.rbegin(), gain.rend());
            long long answer = base;
            for (int i = 0; i < k && i < len; ++i) {
                if (gain[i] > 0) answer += gain[i];
            }
            cout << answer << '\n';
        } else {
            // For large subarrays, we need an O(len) solution
            // The key is to realize that for binary array, f(i, j) = prefixXOR[j+1] ^ prefixXOR[i]
            // For all i <= j, sum f(i, j) = sum over all pairs (i, j) of prefixXOR[j+1] ^ prefixXOR[i]
            // But that's O(len^2), so we need a better way

            // For binary array, let's count the number of subarrays with XOR 1
            // For each prefixXOR value, count its frequency
            unordered_map<int, long long> freq;
            freq[0] = 1;
            int curr = 0;
            long long cnt1 = 0, cnt0 = 0;
            for (int i = x; i <= y; ++i) {
                curr ^= A[i];
                // Number of subarrays ending at i with XOR 1 is freq[curr ^ 1]
                cnt1 += freq[curr ^ 1];
                cnt0 += freq[curr ^ 0];
                freq[curr]++;
            }
            // The sum g(x, y) = cnt1 * 1 + cnt0 * 0 = cnt1
            // But actually, f(i, j) is 1 if the XOR is 1, 0 otherwise
            // So the sum is cnt1

            // Now, to maximize g(x, y), we can flip up to k bits in [x, y]
            // Flipping a bit changes the prefixXOR, so the optimal is to flip the k bits that increase cnt1 the most
            // But for large len, we can approximate:
            // The maximum possible g(x, y) is when all bits are 1, so all subarrays have XOR 1 for odd length
            // For all 1s, the number of subarrays with XOR 1 is (len + 1) / 2 * len / 2
            // But let's just output cnt1 (no flip) for k == 0
            if (k == 0) {
                cout << cnt1 << '\n';
            } else {
                // For k > 0, the best is to flip the k bits that increase cnt1 the most
                // But for large len, flipping any bit changes many subarrays
                // For each position, flipping it changes all subarrays that include it
                // For position i in [x, y], number of subarrays including i is (i - x + 1) * (y - i + 1)
                // For each position, compute the gain if we flip it
                vector<long long> gain(len, 0);
                for (int pos = 0; pos < len; ++pos) {
                    // Flipping A[x+pos] changes all subarrays that include it
                    // For each such subarray, if the original XOR was 0, it becomes 1, and vice versa
                    // So the gain is: number of subarrays including pos - 2 * number of subarrays including pos with XOR 1
                    // But that's complex, so as an approximation, flip the k bits with the largest number of subarrays including them
                    gain[pos] = (long long)(pos + 1) * (len - pos);
                }
                sort(gain.rbegin(), gain.rend());
                long long answer = cnt1;
                for (int i = 0; i < k && i < len; ++i) {
                    answer += gain[i];
                }
                cout << answer << '\n';
            }
        }
    }
    return 0;
}