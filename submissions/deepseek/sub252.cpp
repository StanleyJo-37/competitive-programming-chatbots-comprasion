#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    long long A, B, C, D;
    cin >> A >> B >> C >> D;
    
    // The triangle inequality must hold: x + y > z, x + z > y, y + z > x.
    // Given the constraints A <= x <= B <= y <= C <= z <= D, the only relevant condition is x + y > z.
    // We need to count all triplets (x, y, z) where x <= y <= z and x + y > z.
    
    long long res = 0;
    
    // Iterate over all possible z in [C, D].
    // For each z, find the number of (x, y) pairs where x <= y, x in [A, B], y in [B, C], and x + y > z.
    // The minimal x + y is A + B, and the maximal is B + C.
    // For a given z, the condition x + y > z implies y > z - x.
    // Since y >= max(B, z - x + 1) and y <= C, we need to find the range of y for each x.
    
    // Instead of iterating over x and y, we can precompute prefix sums.
    // For each z, the number of valid (x, y) pairs is sum_{x=A}^{B} max(0, C - max(B, z - x + 1) + 1).
    
    // To optimize, we can split the problem into two parts:
    // 1. For x <= z - C: y must be >= z - x + 1. But since y <= C, this is only possible if z - x + 1 <= C.
    // 2. For x > z - C: y can be any in [B, C], since x + y >= x + B > z (if x + B > z).
    
    // The boundary x0 is the smallest x where x + C > z, i.e., x > z - C.
    // For x <= x0, y must be >= z - x + 1 and <= C.
    // For x > x0, y can be any in [B, C].
    
    for (long long z = C; z <= D; ++z) {
        long long min_sum = z + 1; // x + y > z => x + y >= z + 1
        
        // The minimal x is A, maximal is B.
        // The minimal y is B, maximal is C.
        
        // The total possible pairs (x, y) is sum_{x=A}^{B} [C - max(B, min_sum - x) + 1] if max(B, min_sum - x) <= C.
        
        // Let's find the range of x where min_sum - x >= B => x <= min_sum - B.
        // For x <= min_sum - B: y must be >= min_sum - x and <= C.
        // For x > min_sum - B: y must be >= B and <= C.
        
        long long x_low = A;
        long long x_high = B;
        
        // Split into two intervals:
        // 1. x <= min_sum - B: y >= min_sum - x and y <= C.
        //    The number of y's is C - (min_sum - x) + 1 = C - min_sum + x + 1, if min_sum - x <= C.
        //    Also, min_sum - x >= B => x <= min_sum - B.
        //    So, x must be >= max(A, min_sum - C) because min_sum - x <= C => x >= min_sum - C.
        long long a = max(x_low, min_sum - C);
        long long b = min(x_high, min_sum - B);
        
        if (a <= b) {
            // Sum_{x=a to b} (C - (min_sum - x) + 1) = Sum (C - min_sum + x + 1)
            // = (C - min_sum + 1) * (b - a + 1) + Sum_{x=a to b} x
            long long cnt = b - a + 1;
            long long sum_x = (a + b) * cnt / 2;
            res += (C - min_sum + 1) * cnt + sum_x;
        }
        
        // 2. x > min_sum - B: y >= B and y <= C.
        //    The number of y's is C - B + 1, if x + B > z (which is true since x > min_sum - B => x + B > min_sum - B + B = min_sum = z + 1 > z).
        long long c = max(x_low, min_sum - B + 1);
        long long d = x_high;
        
        if (c <= d) {
            res += (d - c + 1) * (C - B + 1);
        }
    }
    
    cout << res << endl;
    return 0;
}