#include <bits/stdc++.h>
using namespace std;

bool solve(int u, int v) {
    // Edge case: if u > v, it's impossible to reach v from u
    if (u > v) return false;
    // If u == v, always possible (no move needed)
    if (u == v) return true;
    
    int u_bits = 0, v_bits = 0;
    // Count the number of set bits in u and v
    for (int i = 0; i < 30; ++i) {
        if (u & (1 << i)) u_bits++;
        if (v & (1 << i)) v_bits++;
        // At any point, if the number of set bits in u is less than in v up to the same bit, it's impossible
        if (u_bits < v_bits) return false;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int q;
    cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;
        cout << (solve(u, v) ? "YES" : "NO") << '\n';
    }
    return 0;
}