#include <iostream>
using namespace std;

typedef long long ll;

int main() {
    // Read input values
    int A, B, C, D;
    cin >> A >> B >> C >> D;

    ll ans = 0;

    // For each possible y in [B, C]
    for (int y = B; y <= C; ++y) {
        // For each possible x in [A, B]
        // x <= y always holds since x in [A, B] and y in [B, C]
        // For each x, z must satisfy:
        //   z >= y (since y <= z)
        //   z <= D
        //   z < x + y (triangle inequality: x + y > z)
        // So, z in [y, min(D, x + y - 1)]
        // For each y, we can process all x in [A, B] and sum up the valid z's

        // For x in [A, B]
        // For each x, the valid z's are from max(y, y) to min(D, x + y - 1)
        // So, for x in [A, B], z in [y, min(D, x + y - 1)]
        // The number of such z's is max(0, min(D, x + y - 1) - y + 1)

        // We can process x in [A, B] efficiently:
        // For a fixed y, for x in [A, B]:
        //   z_max = min(D, x + y - 1)
        //   z_min = y
        //   count = max(0, z_max - z_min + 1)

        // For x in [A, B], x + y - 1 increases as x increases
        // For x such that x + y - 1 <= D, z_max = x + y - 1
        // For x such that x + y - 1 > D, z_max = D

        // So, for x in [A, B], x + y - 1 <= D
        // => x <= D - y + 1
        int x1 = max(A, y - (y - A)); // A
        int x2 = min(B, D - y + 1);

        if (x1 <= x2) {
            // For x in [x1, x2], z_max = x + y - 1
            // For each x, number of z's: (x + y - 1) - y + 1 = x
            // So, sum over x in [x1, x2] of x
            ll cnt = (ll)(x2 - x1 + 1);
            ll sum_x = (ll)(x1 + x2) * cnt / 2;
            ans += sum_x;
        }

        // For x in [x2+1, B], z_max = D
        if (x2 + 1 <= B) {
            // For x in [x2+1, B], number of z's: D - y + 1
            ll cnt = (ll)(B - (x2 + 1) + 1);
            if (D - y + 1 > 0)
                ans += cnt * (D - y + 1);
        }
    }

    // Output the answer
    cout << ans << endl;
    return 0;
}