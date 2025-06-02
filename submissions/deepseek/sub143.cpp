#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        long long N;
        cin >> N;
        if (N == 1) {
            cout << "1\n";
            continue;
        }
        // The longest subarray with positive bitwise AND must be all numbers sharing the same highest set bit.
        // The largest such subarray is [2^k, 2^{k+1} - 1], with length 2^k.
        long long k = 0;
        while ((1LL << (k + 1)) <= N) {
            k++;
        }
        long long lower = (1LL << k);
        long long upper = (1LL << (k + 1)) - 1;
        if (upper <= N) {
            cout << (1LL << k) << '\n';
        } else {
            cout << (N - lower + 1) << '\n';
        }
    }
    return 0;
}