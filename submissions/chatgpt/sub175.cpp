#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;
const ll MOD = 1000000007;

// Function to compute prefix sums modulo MOD
void compute_prefix_sum(const vector<ll>& arr, vector<ll>& prefix) {
    int n = arr.size();
    prefix.resize(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        prefix[i + 1] = (prefix[i] + arr[i]) % MOD;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;
    while (T--) {
        int p, q, r;
        cin >> p >> q >> r;
        vector<ll> A(p), B(q), C(r);
        for (int i = 0; i < p; ++i) cin >> A[i];
        for (int i = 0; i < q; ++i) cin >> B[i];
        for (int i = 0; i < r; ++i) cin >> C[i];

        // Sort arrays for binary search and prefix sum logic
        sort(A.begin(), A.end());
        sort(B.begin(), B.end());
        sort(C.begin(), C.end());

        // Compute prefix sums for A and C
        vector<ll> prefixA, prefixC;
        compute_prefix_sum(A, prefixA);
        compute_prefix_sum(C, prefixC);

        ll result = 0;

        // For each Y in B, find number of X in A with X <= Y, and Z in C with Z <= Y
        for (int i = 0; i < q; ++i) {
            ll Y = B[i];

            // Number of X in A with X <= Y
            ll cntA = upper_bound(A.begin(), A.end(), Y) - A.begin();
            // Number of Z in C with Z <= Y
            ll cntC = upper_bound(C.begin(), C.end(), Y) - C.begin();

            if (cntA == 0 || cntC == 0) continue; // No valid X or Z for this Y

            // Sum of X in A with X <= Y
            ll sumA = prefixA[cntA];
            // Sum of Z in C with Z <= Y
            ll sumC = prefixC[cntC];

            // The sum for this Y is:
            // sum over all X <= Y and Z <= Y of (X + Y) * (Y + Z)
            // = sum over X (X + Y) * sum over Z (Y + Z)
            // = (sumA + cntA * Y) * (sumC + cntC * Y)
            ll term1 = (sumA + cntA * Y % MOD) % MOD;
            ll term2 = (sumC + cntC * Y % MOD) % MOD;
            ll add = (term1 * term2) % MOD;
            result = (result + add) % MOD;
        }

        cout << result << '\n';
    }
    return 0;
}