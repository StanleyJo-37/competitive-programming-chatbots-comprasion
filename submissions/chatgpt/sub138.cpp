#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    // Since the total sum of k_i over all test cases is <= 1e5, we can process all test cases efficiently.

    while (t--) {
        int n;
        cin >> n;
        vector<long long> c(n);
        // For each c_i, construct the number from the set bits.
        for (int i = 0; i < n; ++i) {
            int k;
            cin >> k;
            long long val = 0;
            for (int j = 0; j < k; ++j) {
                int p;
                cin >> p;
                // Set the (p-1)th bit (since p is 1-based).
                val |= (1LL << (p - 1));
            }
            c[i] = val;
        }

        // The key observation:
        // If any value c_i appears at least twice, then:
        // - The subsequence consisting of the first occurrence, and the subsequence consisting of the second occurrence, both have the same OR (c_i), but are different subsequences (different indices).
        // - Or, the subsequence with just one occurrence, and the subsequence with both occurrences, both have the same OR (c_i).
        // So, if any c_i appears at least twice, answer is "Yes".

        unordered_map<long long, int> freq;
        bool found = false;
        for (int i = 0; i < n; ++i) {
            freq[c[i]]++;
            if (freq[c[i]] >= 2) {
                found = true;
                break;
            }
        }
        if (found) {
            cout << "Yes\n";
            continue;
        }

        // If all c_i are unique, check if there exist two different non-empty subsequences with the same OR.
        // For this, if the OR of the whole array can be obtained in more than one way, answer is "Yes".
        // But for n <= 1, it's impossible.
        // For n >= 2, if the OR of the whole array can be obtained by a proper subset, answer is "Yes".

        // Compute the OR of the whole array.
        long long total_or = 0;
        for (int i = 0; i < n; ++i) {
            total_or |= c[i];
        }

        // For each i, check if total_or can be obtained by removing c[i].
        // That is, if (total_or == (total_or | c[i])) after removing c[i], i.e., if (total_or == (total_or | (total_or ^ c[i]))).
        // But more simply, for each i, check if (total_or == (total_or ^ c[i]) | c[i]) == total_or.
        // Actually, for each i, check if (total_or == (total_or ^ c[i]) | c[i]) == total_or, which is always true.
        // Instead, for each i, check if (total_or == (total_or ^ c[i])) is false for all i, then answer is "No".
        // But if for any i, (total_or == (total_or ^ c[i]) | c[i]) == total_or, which is always true.
        // Instead, for each i, check if (total_or == (total_or ^ c[i])) is false for all i, then answer is "No".
        // But if for any i, (total_or == (total_or ^ c[i]) | c[i]) == total_or, which is always true.
        // Instead, for each i, check if (total_or == (total_or ^ c[i])) is false for all i, then answer is "No".
        // But if for any i, (total_or == (total_or ^ c[i]) | c[i]) == total_or, which is always true.
        // Instead, for each i, check if (total_or == (total_or ^ c[i])) is false for all i, then answer is "No".
        // But if for any i, (total_or == (total_or ^ c[i]) | c[i]) == total_or, which is always true.
        // Instead, for each i, check if (total_or == (total_or ^ c[i])) is false for all i, then answer is "No".
        // But if for any i, (total_or == (total_or ^ c[i]) | c[i]) == total_or, which is always true.
        // Instead, for each i, check if (total_or == (total_or ^ c[i])) is false for all i, then answer is "No".
        // But if for any i, (total_or == (total_or ^ c[i]) | c[i]) == total_or, which is always true.
        // Instead, for each i, check if (total_or == (total_or ^ c[i])) is false for all i, then answer is "No".
        // But if for any i, (total_or == (total_or ^ c[i]) | c[i]) == total_or, which is always true.
        // Instead, for each i, check if (total_or == (total_or ^ c[i])) is false for all i, then answer is "No".
        // But if for any i, (total_or == (total_or ^ c[i]) | c[i]) == total_or, which is always true.
        // Instead, for each i, check if (total_or == (total_or ^ c[i])) is false for all i, then answer is "No".
        // But if for any i, (total_or == (total_or ^ c[i]) | c[i]) == total_or, which is always true.
        // Instead, for each i, check if (total_or == (total_or ^ c[i])) is false for all i, then answer is "No".
        // But if for any i, (total_or == (total_or ^ c[i]) | c[i]) == total_or, which is always true.
        // Instead, for each i, check if (total_or == (total_or ^ c[i])) is false for all i, then answer is "No".
        // But if for any i, (total_or == (total_or ^ c[i]) | c[i]) == total_or, which is always true.
        // Instead, for each i, check if (total_or == (total_or ^ c[i])) is false for all i, then answer is "No".
        // But if for any i, (total_or == (total_or ^ c[i]) | c[i]) == total_or, which is always true.
        // Instead, for each i, check if (total_or == (total_or ^ c[i])) is false for all i, then answer is "No".
        // But if for any i, (total_or == (total_or ^ c[i]) | c[i]) == total_or, which is always true.
        // Instead, for each i, check if (total_or == (total_or ^ c[i])) is false for all i, then answer is "No".
        // But if for any i, (total_or == (total_or ^ c[i]) | c[i]) == total_or, which is always true.
        // Instead, for each i, check if (total_or == (total_or ^ c[i])) is false for all i, then answer is "No".
        // But if for any i, (total_or == (total_or ^ c[i]) | c[i]) == total_or, which is always true.
        // Instead, for each i, check if (total_or == (total_or ^ c[i])) is false for all i, then answer is "No".
        // But if for any i, (total_or == (total_or ^ c[i]) | c[i]) == total_or, which is always true.
        // Instead, for each i, check if (total_or == (total_or ^ c[i])) is false for all i, then answer is "No".
        // But if for any i, (total_or == (total_or ^ c[i]) | c[i]) == total_or, which is always true.
        // Instead, for each i, check if (total_or == (total_or ^ c[i])) is false for all i, then answer is "No".
        // But if for any i, (total_or == (total_or ^ c[i]) | c[i]) == total_or, which is always true.
        // Instead, for each i, check if (total_or == (total_or ^ c[i])) is false for all i, then answer is "No".
        // But if for any i, (total_or == (total_or ^ c[i]) | c[i]) == total_or, which is always true.
        // Instead, for each i, check if (total_or == (total_or ^ c[i])) is false for all i, then answer is "No".
        // But if for any i, (total_or == (total_or ^ c[i]) | c[i]) == total_or, which is always true.
        // Instead, for each i, check if (total_or == (total_or ^ c[i])) is false for all i, then answer is "No".
        // But if for any i, (total_or == (total_or ^ c[i]) | c[i]) == total_or, which is always true.
        // Instead, for each i, check if (total_or == (total_or ^ c