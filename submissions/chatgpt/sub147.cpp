#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false); // Fast IO
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int C;
        cin >> C;

        // Find the smallest d such that 2^d > C
        int d = 0;
        while ((1 << d) <= C) ++d;

        // The maximum value for A and B is less than 2^d
        // We want to maximize A * B where A ^ B == C, 0 <= A, B < 2^d

        // The optimal way is to set A as large as possible under the constraints,
        // and B = A ^ C. But both must be < 2^d.

        // To maximize A * B, we can try to set the higher bits of A to 1 where C has 0,
        // and lower bits to 0 where C has 1, to maximize both A and B.

        // Let's construct A as follows:
        // For each bit from d-1 to 0:
        //   - If C has 0 at this bit, set A's bit to 1 (so B's bit is 1^0=1)
        //   - If C has 1 at this bit, set A's bit to 0 (so B's bit is 0^1=1)
        // This way, both A and B have 1 at all positions where C has 0, and at positions where C has 1, one is 1 and the other is 0.

        // But to maximize the product, we can split the bits: for each bit where C has 1, assign it to A or B, and for bits where C has 0, set both A and B to 1.

        // The best is to set A = (1 << (d-1)) - 1, and B = A ^ C, or vice versa.
        // But let's formalize:
        // Let x = 0, for i = d-1 to 0:
        //   - if (C >> i) & 1 == 0: set x's bit i to 1
        //   - else: do nothing
        // So x = (1 << d) - 1 - C

        // So, A = x, B = x ^ C = (1 << d) - 1 - C ^ C = (1 << d) - 1 - C + C - 2*(x & C)
        // But actually, just try A = x, B = x ^ C

        int x = (1 << d) - 1 - C;
        int A = x;
        int B = x ^ C;
        // Both A and B are < 2^d, and A ^ B == C

        cout << 1LL * A * B << '\n';
    }
    return 0;
}