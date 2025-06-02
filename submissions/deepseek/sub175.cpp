#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MOD = 1000000007;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    while (T--) {
        int p, q, r;
        cin >> p >> q >> r;
        
        vector<ll> A(p), B(q), C(r);
        for (int i = 0; i < p; ++i) cin >> A[i];
        for (int i = 0; i < q; ++i) cin >> B[i];
        for (int i = 0; i < r; ++i) cin >> C[i];
        
        // Sort arrays for binary search and prefix sums
        sort(A.begin(), A.end());
        sort(B.begin(), B.end());
        sort(C.begin(), C.end());
        
        // Precompute prefix sums for A and C
        vector<ll> prefixA(p + 1, 0), prefixC(r + 1, 0);
        for (int i = 0; i < p; ++i) prefixA[i + 1] = (prefixA[i] + A[i]) % MOD;
        for (int i = 0; i < r; ++i) prefixC[i + 1] = (prefixC[i] + C[i]) % MOD;
        
        ll total = 0;
        
        for (ll y : B) {
            // Count X <= y in A: xCount = number of elements <= y in A
            auto itA = upper_bound(A.begin(), A.end(), y);
            int xCount = itA - A.begin();
            if (xCount == 0) continue; // No X <= y
            
            // Sum of X where X <= y: xSum = prefixA[xCount]
            ll xSum = prefixA[xCount];
            
            // Count Z <= y in C: zCount = number of elements <= y in C
            auto itC = upper_bound(C.begin(), C.end(), y);
            int zCount = itC - C.begin();
            if (zCount == 0) continue; // No Z <= y
            
            // Sum of Z where Z <= y: zSum = prefixC[zCount]
            ll zSum = prefixC[zCount];
            
            // Compute the contribution for this Y:
            // (X + Y) * (Y + Z) = X*Y + X*Z + Y^2 + Y*Z
            // Sum over all X and Z: 
            // = Y * xSum * zCount + xSum * zSum + Y^2 * xCount * zCount + Y * xCount * zSum
            ll term1 = (y % MOD) * xSum % MOD;
            term1 = term1 * zCount % MOD;
            
            ll term2 = xSum * zSum % MOD;
            
            ll ySq = (y % MOD) * (y % MOD) % MOD;
            ll term3 = ySq * xCount % MOD;
            term3 = term3 * zCount % MOD;
            
            ll term4 = (y % MOD) * xCount % MOD;
            term4 = term4 * zSum % MOD;
            
            ll contribution = (term1 + term2 + term3 + term4) % MOD;
            total = (total + contribution) % MOD;
        }
        
        cout << total << "\n";
    }
    
    return 0;
}