#include <bits/stdc++.h>
using namespace std;

/*
 * The key observation here is that the condition Ai⊕...⊕Aj-1 = Aj⊕...⊕Ak
 * can be rewritten using the property of XOR: a ⊕ a = 0.
 * Let prefix[i] = A1 ⊕ A2 ⊕ ... ⊕ Ai.
 * Then, the condition becomes prefix[j-1] ⊕ prefix[i-1] = prefix[k] ⊕ prefix[j-1].
 * Simplifying, we get prefix[i-1] = prefix[k].
 * So, for any i and k where prefix[i-1] == prefix[k], all j in (i, k] will satisfy the condition.
 * The number of valid j's for such (i, k) pairs is (k - i).
 * 
 * To efficiently count all such pairs, we can use a hash map to store the frequency and sum of indices
 * for each prefix value. For each prefix[k], if it has occurred before, the number of new valid triples
 * is (count[prefix[k]] * k - sum[prefix[k]]).
 */
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        vector<int> A(N);
        for (int i = 0; i < N; ++i) {
            cin >> A[i];
        }
        
        unordered_map<int, long long> count, sum;
        int prefix = 0;
        long long result = 0;
        count[0] = 1; // prefix[0] = 0
        sum[0] = 0;    // sum of indices where prefix occurs (here index 0)
        
        for (int k = 1; k <= N; ++k) {
            prefix ^= A[k-1];
            if (count.find(prefix) != count.end()) {
                result += count[prefix] * (k - 1) - sum[prefix];
            }
            count[prefix]++;
            sum[prefix] += k;
        }
        
        cout << result << '\n';
    }
    
    return 0;
}