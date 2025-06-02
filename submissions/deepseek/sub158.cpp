#include <bits/stdc++.h>
using namespace std;

void solve() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int N;
        scanf("%d", &N);
        string A, B;
        cin >> A >> B;
        
        // The operation is equivalent to swapping adjacent bits if they are different.
        // The key observation is that the parity of the number of '1's in A and B must be the same,
        // and the first bit must match because the first bit can never be changed by any operation.
        if (A[0] != B[0]) {
            printf("NO\n");
            continue;
        }
        
        int a_ones = count(A.begin(), A.end(), '1');
        int b_ones = count(B.begin(), B.end(), '1');
        
        // If the number of '1's in A and B have the same parity, and the first bits match, it's possible.
        // Also, if B is all zeros, then A must be all zeros (since operations can't change the total parity).
        if ((a_ones % 2) == (b_ones % 2) || (b_ones == 0 && a_ones == 0)) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
}

int main() {
    solve();
    return 0;
}