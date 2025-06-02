#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

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

        // The goal is to maximize the sum of (A_i + i) mod 2 for each i.
        // (A_i + i) mod 2 is equivalent to (A_i mod 2 + i mod 2) mod 2.
        // To maximize the sum, we need as many terms as possible where (A_i mod 2 + i mod 2) mod 2 = 1.
        // This happens when A_i mod 2 != i mod 2.
        // So, we need to pair even A_i with odd i and odd A_i with even i.
        // The maximum possible sum is min(count_odd_A, count_even_indices) + min(count_even_A, count_odd_indices).
        // Where count_even_indices = N / 2, count_odd_indices = (N + 1) / 2.

        int count_odd_A = 0;
        for (int num : A) {
            if (num % 2 != 0) {
                count_odd_A++;
            }
        }
        int count_even_A = N - count_odd_A;
        int count_odd_indices = (N + 1) / 2;
        int count_even_indices = N / 2;

        int max_sum = min(count_odd_A, count_even_indices) + min(count_even_A, count_odd_indices);
        cout << max_sum << '\n';
    }

    return 0;
}