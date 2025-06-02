#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int C;
        cin >> C;
        
        // Find the smallest d such that 2^d > C
        int d = 0;
        while ((1LL << d) <= C) {
            d++;
        }
        
        // The maximum product is achieved when A and B are as close as possible.
        // The optimal A and B are (2^(d-1) - 1 and (C ^ ((2^(d-1) - 1)).
        long long mask = (1LL << (d - 1)) - 1;
        long long A = mask;
        long long B = C ^ A;
        cout << A * B << '\n';
    }
    return 0;
}