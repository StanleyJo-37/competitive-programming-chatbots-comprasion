#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        string S;
        cin >> S;
        int n = S.size();
        long long beauty = 0;

        // We need to find all substrings where cnt0 = cnt1^2.
        // Let's denote delta = cnt1^2 - cnt0.
        // We need delta = 0 for a substring to be special.
        // We can use a prefix sum approach to track the cumulative cnt1 and cnt0.
        // For any substring from i to j, cnt1 = prefix1[j] - prefix1[i-1], similarly for cnt0.
        // So, delta = (prefix1[j] - prefix1[i-1])^2 - (prefix0[j] - prefix0[i-1]).
        // Rearranged: prefix0[j] - prefix1[j]^2 = prefix0[i-1] - prefix1[i-1]^2.
        // We can use a hashmap to count the occurrences of (prefix0[k] - prefix1[k]^2) for all k.

        unordered_map<long long, int> freq;
        freq[0] = 1; // Base case: empty prefix
        int prefix1 = 0, prefix0 = 0;

        for (char c : S) {
            if (c == '1') {
                prefix1++;
            } else {
                prefix0++;
            }
            long long key = prefix0 - (long long)prefix1 * prefix1;
            beauty += freq[key];
            freq[key]++;
        }

        cout << beauty << '\n';
    }

    return 0;
}