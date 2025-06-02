#include <iostream>
#include <cmath>
#include <algorithm>

int main() {
    // Optimize C++ standard streams for faster input/output.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int T; // Declare variable for the number of test cases.
    std::cin >> T; // Read the number of test cases.
    while (T--) { // Loop through each test case.
        int C; // Declare variable for the input integer C.
        std::cin >> C; // Read the integer C.

        // Find the smallest integer d such that 2^d > C.
        // This is equivalent to finding the smallest power of 2 that is
        // strictly greater than C. This can be found by finding the
        // position of the most significant bit of C and adding 1,
        // or by using std::log2 and std::ceil, or by simply finding
        // the smallest power of 2 that is >= C, and if it's equal to C,
        // then the next power of 2. A more direct way is to find the
        // smallest power of 2 that is >= C, and then if C is itself a power
        // of 2, we need the next power of 2.
        // A simple way is to find the smallest power of 2, say 2^d, such that
        // 2^d > C. This d is ceil(log2(C + 1)) if C is not a power of 2.
        // If C is a power of 2, say 2^k, then d = k + 1.
        // Let's find 2^d as the smallest power of 2 strictly greater than C.
        // We can start with power_of_2 = 1 and keep doubling it until it's > C.
        long long power_of_2 = 1;
        while (power_of_2 <= C) {
            power_of_2 <<= 1; // Left shift by 1 is equivalent to multiplying by 2.
        }

        // We are looking for pairs (A, B) such that A, B < 2^d and A XOR B = C.
        // We want to maximize A * B.
        // The condition A XOR B = C implies that for each bit position:
        // If the i-th bit of C is 0, then the i-th bits of A and B must be the same (both 0 or both 1).
        // If the i-th bit of C is 1, then the i-th bits of A and B must be different (one 0, one 1).

        // To maximize A * B, A and B should be as close as possible to each other.
        // Consider the bits from most significant to least significant.
        // Let X = 2^d - 1. This is a number with all bits set up to the (d-1)-th bit.
        // A and B must be less than 2^d, meaning their d-th bit (0-indexed) must be 0.
        // All other bits are free to be set to maximize product.
        // The sum A + B = (A XOR B) + 2 * (A AND B) = C + 2 * (A AND B).
        // To maximize A * B for a fixed sum S = A + B, A and B should be as close as possible,
        // i.e., A approx S/2 and B approx S/2.
        // So we want to maximize C + 2 * (A AND B). This means we want to maximize (A AND B).
        // (A AND B) will have 1s where both A and B have 1s.
        // If C's i-th bit is 0, then A_i = B_i. We can choose A_i = B_i = 1 to maximize (A AND B).
        // If C's i-th bit is 1, then A_i != B_i. In this case, A_i AND B_i must be 0.

        // So, A AND B will have 1s at all positions where C has a 0 bit.
        // Let's construct a target value, say P, for A and B.
        // We want A and B to be approximately (2^d - 1) / 2.
        // A simple greedy approach:
        // Try to make A and B as close to (power_of_2 - 1) / 2 as possible.
        // The values A and B are bounded by 2^d - 1.
        // Consider A_prime = A and B_prime = B.
        // A_prime + B_prime = (power_of_2 - 1).
        // A_prime = (power_of_2 - 1) - B_prime.
        // ( (power_of_2 - 1) - B_prime ) XOR B_prime = C.
        // This is not immediately useful.

        // Let's observe the structure. We have 2^d - 1 as the maximum possible value for A or B.
        // The maximum product A*B happens when A and B are close to (2^d - 1) / 2.
        // Let M = power_of_2 - 1. This is a number with d ones: 11...1 (d times).
        // We know A XOR B = C.
        // Let A = P. Then B = C XOR P.
        // We need to pick P such that P < 2^d and (C XOR P) < 2^d.
        // And we want to maximize P * (C XOR P).

        // If we set A = (power_of_2 - 1) - C, then B = C XOR ((power_of_2 - 1) - C).
        // This does not directly relate to A XOR B = C.

        // Let's think about the bit positions.
        // For each bit position i:
        // If C_i = 1: A_i != B_i. One is 0, one is 1. To make A and B close, we want roughly half to be 1 and half to be 0 for both A and B.
        // If C_i = 0: A_i = B_i. Both are 0 or both are 1. To maximize sum (and thus product by making them close), we want them to be 1.

        // Consider the value `mask = power_of_2 - 1`. This is a number with all `d` bits set to 1.
        // The optimal A and B will satisfy A XOR B = C.
        // And A AND B should be maximized for positions where C has 0.
        // Consider A = X and B = X XOR C.
        // We want to maximize X * (X XOR C).
        // The maximum possible value for A or B is `power_of_2 - 1`.
        // So, A and B must have 0 at the `d`-th bit position (0-indexed).
        // This means `C` must also have 0 at the `d`-th bit position, which is true because `C < 2^d`.

        // Let's try to construct A and B.
        // If we choose A = (power_of_2 - 1) XOR K for some K, and B = K for example.
        // No, this is not directly useful.

        // Let's try constructing A and B greedily.
        // To maximize A * B, A and B should be as close as possible to (power_of_2 - 1) / 2.
        // Let S = (power_of_2 - 1). This is the maximum value A or B can take.
        // We want A + B to be as close to S as possible, while maintaining A XOR B = C.
        // We know A + B = (A XOR B) + 2 * (A AND B) = C + 2 * (A AND B).
        // To maximize A * B, we want to maximize A + B. This means we want to maximize A AND B.
        // For bits where C_i = 1: A_i and B_i must be different, so A_i AND B_i = 0.
        // For bits where C_i = 0: A_i and B_i must be the same. To maximize A AND B, we set A_i = B_i = 1.
        // So, the optimal (A AND B) will have 1s at exactly those positions where C has a 0 bit.
        // This means (A AND B) = (~C) & (power_of_2 - 1). Let's call this `and_mask`.
        // `and_mask = ( (~C) & (power_of_2 - 1) )`.
        // The desired sum A + B = C + 2 * `and_mask`.
        // Let S_target = C + 2 * `and_mask`.
        // We want to find A and B such that A + B = S_target, A XOR B = C, A, B < power_of_2, and A * B is maximized.
        // Given A + B = S_target and A - B = some_value.
        // A = (S_target + (A-B))/2 and B = (S_target - (A-B))/2.
        // To maximize A * B, we want (A-B) to be as small as possible. This means A and B are close.
        // With A XOR B = C and A AND B = and_mask, we have A = C XOR B.
        // A = C + 2 * and_mask - B.
        // (C + 2 * and_mask - B) XOR B = C.
        // This is getting complicated.

        // A simpler observation for A XOR B = C.
        // If we choose A = (power_of_2 - 1 - C)/2 and B = (power_of_2 - 1 + C)/2.
        // These values are not guaranteed to satisfy A XOR B = C.

        // Key insight: To maximize A * B subject to A XOR B = C and A, B < 2^d,
        // we should try to make A and B as close as possible to `(2^d - 1) / 2`.
        // Let `mask = (power_of_2 - 1)`.
        // This `mask` has `d` bits set to 1.
        // The value `power_of_2 - 1` is the largest number that can be represented with `d` bits.
        // Consider A = (power_of_2 - 1) - K and B = K for some K.
        // ( (power_of_2 - 1) - K ) XOR K = C.
        // This simplifies to (power_of_2 - 1) XOR (2K) = C (if we consider a different K).
        // This is based on a property of XOR and complement: if X is all 1s (like power_of_2 - 1),
        // then X XOR Y = ~Y.
        // So we want (~K) XOR K = C. This is impossible unless K is 0.
        // The property is `(mask) XOR x = (~x) & mask` assuming `x < power_of_2`.
        // So we need `(~A) & mask = B` and `(~B) & mask = A`.
        // If we set A = (power_of_2 - 1) - B.
        // Then ((power_of_2 - 1) - B) XOR B = C.
        // Let `X = power_of_2 - 1`.
        // We need (X - B) XOR B = C.
        // This means for each bit `i`:
        // If `X_i` is 1 (which it always is), then `(1 - B_i) XOR B_i = C_i`.
        // If `B_i = 0`, then `(1 - 0) XOR 0 = 1 XOR 0 = 1`. So `C_i = 1`.
        // If `B_i = 1`, then `(1 - 1) XOR 1 = 0 XOR 1 = 1`. So `C_i = 1`.
        // This implies `C_i` must be 1 for all bits up to `d-1`.
        // This means `C` itself must be `power_of_2 - 1`.
        // This is not generally true.

        // So the "trick" or "observation" is related to the specific structure.
        // The optimal pair A, B will be constructed as follows:
        // A = (power_of_2 - 1) - X
        // B = X
        // Such that (A XOR B) = C.
        // Then ((power_of_2 - 1) - X) XOR X = C.
        // This property `(mask - X) XOR X = C` is equivalent to `mask ^ X ^ X = C` for certain values.
        // This is usually related to `mask ^ X = ~X`.
        // (power_of_2 - 1 - X) XOR X = C.
        // Let `max_val = power_of_2 - 1`.
        // We can rewrite A = `max_val ^ Y` and B = `Y`.
        // Then `(max_val ^ Y) ^ Y = C`
        // `max_val = C`.
        // This happens only if C is `2^d - 1`.
        // Example: C = 13 (1101). d = 4. power_of_2 = 16. max_val = 15 (1111).
        // If C = 15, then A and B are 0 and 15, or 1 and 14, etc.
        // Here A = 7 (0111) and B = 8 (1000). A XOR B = 15. Product = 56.
        // A = 0 and B = 15 => 0. A = 1 and B = 14 => 14. A = 2 and B = 13 => 26. A = 3 and B = 12 => 36.
        // A = 4 and B = 11 => 44. A = 5 and B = 10 => 50. A = 6 and B = 9 => 54. A = 7 and B = 8 => 56.

        // The problem states A, B < 2^d.
        // When A XOR B = C, and A, B are close to `2^d/2`,
        // this implies A and B are "mirror images" around `2^d/2`.
        // The strategy is to find an A such that A XOR C is B, and A and B are close.
        // The sum A + B = C + 2 * (A AND B).
        // To maximize A * B, for a fixed C, we need to maximize A AND B.
        // A AND B has 1s only where A_i = 1 and B_i = 1.
        // If C_i = 1, then A_i != B_i, so A_i AND B_i = 0.
        // If C_i = 0, then A_i = B_i. To maximize A AND B, we set A_i = B_i = 1.
        // So A AND B should ideally be `(~C) & (power_of_2 - 1)`.
        // Let `AND_target = (~C) & (power_of_2 - 1)`.
        // Then A + B = C + 2 * AND_target. Let `Sum_target = C + 2 * AND_target`.
        // We want to find A and B such that A + B = Sum_target and A XOR B = C.
        // With A + B = Sum_target and A XOR B = C, we know A and B are solutions to:
        // x^2 - Sum_target * x + (A * B) = 0.
        // To maximize A * B, for a fixed sum, A and B should be as close as possible.
        // So A is approximately Sum_target / 2, and B is approximately Sum_target / 2.
        // Let `mid = Sum_target / 2`.
        // We can try to construct A and B starting from `mid`.
        // This is essentially equivalent to finding the A that yields the maximum product.
        // The problem can be reduced to this:
        // Find `k` such that `(k XOR C)` is close to `k`, and both are less than `2^d`.
        // This is equivalent to finding `x` such that `x * (C XOR x)` is maximized.
        // Let `x = (power_of_2 - 1) / 2`. This is typically not an integer.
        // More precisely, let `x = (power_of_2 / 2) - 1`. This value represents 011...1 (d-1 times).
        // Or `x = power_of_2 / 2`. This represents 100...0.

        // The maximum product is always achieved when A and B are such that
        // A + B = `power_of_2 - 1` and A XOR B = C.
        // This can be shown as follows:
        // We want to maximize A * B subject to A XOR B = C and A, B < 2^d.
        // A + B = C + 2 * (A AND B).
        // To maximize A * B, for a fixed XOR sum, we want to maximize A AND B.
        // A AND B bits are 1 only if A_i = 1 and B_i = 1.
        // If C_i = 1, then A_i != B_i, so A_i AND B_i must be 0.
        // If C_i = 0, then A_i = B_i. To maximize A AND B, we should set A_i = B_i = 1.
        // So, the maximum possible value for A AND B is `mask_for_and = (~C) & (power_of_2 - 1)`.
        // Let's call `opt_and = (~C) & (power_of_2 - 1)`.
        // So, `A + B = C + 2 * opt_and`.
        // The maximum product is achieved when A and B are as close as possible.
        // The required sum is `C + 2 * ((~C) & (power_of_2 - 1))`.
        // Notice that `C + 2 * ((~C) & (power_of_2 - 1))` is always equal to `power_of_2 - 1`.
        // Proof:
        // Let `mask = power_of_2 - 1`.
        // `C + 2 * ((~C) & mask) = C + 2 * (~C_masked)`
        // Consider a bit `i`:
        // If `C_i = 0`: then `(~C_i) & 1 = 1`. So, `0 + 2 * 1 = 2`. This is `10` in binary.
        // But what we want is `mask_i = 1`.
        // This formula `A + B = C + 2 * (A AND B)` implies that if `C_i = 0`, then `A_i = B_i`.
        // To get `A_i + B_i = 1`, we need `A_i=0, B_i=1` or `A_i=1, B_i=0`. This is impossible.
        // The sum `A+B` is formed bitwise by `A_i+B_i`.
        // If `A_i=0, B_i=0`, then `A_i+B_i=0`. `(A XOR B)_i = 0`. `(A AND B)_i = 0`.
        // If `A_i=0, B_i=1`, then `A_i+B_i=1`. `(A XOR B)_i = 1`. `(A AND B)_i = 0`.
        // If `A_i=1, B_i=0`, then `A_i+B_i=1`. `(A XOR B)_i = 1`. `(A AND B)_i = 0`.
        // If `A_i=1, B_i=1`, then `A_i+B_i=2`. `(A XOR B)_i = 0`. `(A AND B)_i = 1`.
        // This is always true modulo carry.
        // What we are interested in is `(A+B)` where no carries are involved.
        // The sum A + B is not necessarily `power_of_2 - 1`.

        // The critical observation for this type of problem:
        // The maximum product A * B given A XOR B = C and A, B < 2^d
        // is obtained when A and B are values such that A XOR B = C AND A + B = (power_of_2 - 1).
        // This means A = ( (power_of_2 - 1) + C ) / 2
        // and B = ( (power_of_2 - 1) - C ) / 2
        // Let's verify this.
        // Let `S = power_of_2 - 1`.
        // Let `A_cand = (S + C) / 2` and `B_cand = (S - C) / 2`.
        // First check `A_cand XOR B_cand = C`:
        // `A_cand XOR B_cand = ((S + C) / 2) XOR ((S - C) / 2)`.
        // If `S` has all bits 1 up to `d-1` (i.e. `S = 2^d - 1`), then `S + C` and `S - C`
        // will have the same parity (both even or both odd) if `S` and `C` have different parity.
        // `S` is odd.
        // If `C` is odd, then `S+C` is even, `S-C` is even. Divisible by 2.
        // If `C` is even, then `S+C` is odd, `S-C` is odd. Not divisible by 2.
        // This formula `A=(S+C)/2` and `B=(S-C)/2` only works if S and C have same parity.
        // S = `power_of_2 - 1`.
        // `power_of_2` is always even (for d >= 1). So `power_of_2 - 1` is always odd.
        // So for this to work, C must be odd.
        // Example C = 10 (even). power_of_2 = 16. S = 15 (odd).
        // (15 + 10) / 2 = 25/2 (not integer).
        // This means the formula `A = (S+C)/2`, `B = (S-C)/2` is not universally applicable.

        // The correct approach is:
        // The problem asks for A, B < 2^d such that A XOR B = C and A * B is maximized.
        // This means A and B should be as close as possible.
        // Consider `k = power_of_2 - 1`.
        // The candidate values for A and B should be symmetric around `k / 2`.
        // Let `val_A = (power_of_2 - 1) ^ C`.
        // This would mean if `C=0`, `val_A = power_of_2 - 1`.
        // Then `B = val_A XOR C = (power_of_2 - 1) XOR C XOR C = power_of_2 - 1`.
        // So A = `power_of_2 - 1` and B = `power_of_2 - 1`.
        // This pair gives `(power_of_2 - 1) XOR (power_of_2 - 1) = 0`, which is C.
        // The product is `(power_of_2 - 1) * (power_of_2 - 1)`.
        // This is the correct solution for C = 0.
        // Example: C=0. power_of_2 is 1 (for d=0, technically C=0 is handled by `d=1` so `power_of_2=2`).
        // If C=0, d=1. power_of_2 = 2. A, B < 2. A XOR B = 0.
        // (A,B) = (0,0) or (1,1). Max product is 1*1 = 1.
        // Our formula: `(power_of_2 - 1) * (power_of_2 - 1) = (2-1) * (2-1) = 1*1 = 1`. This holds.

        // The general approach for A XOR B = C:
        // The numbers A and B are chosen such that they satisfy A XOR B = C.
        // To maximize A * B, A and B should be "centered" around `(power_of_2 - 1) / 2`.
        // Specifically, consider `A = (power_of_2 - 1) - x` and `B = x`.
        // Their XOR sum is `( (power_of_2 - 1) - x ) XOR x`.
        // This equals C.
        // When `power_of_2 - 1` has all bits set (11...1), then `(power_of_2 - 1) - x` is equivalent to `(~x) & (power_of_2 - 1)`.
        // So we need `( (~x) & (power_of_2 - 1) ) XOR x = C`.
        // This is `(~x_d) XOR x = C` (where `x_d` means `x` masked to `d` bits).
        // Let `S = power_of_2 - 1`.
        // The pair `(A, B)` that maximizes `A * B` for `A XOR B = C` and `A, B < 2^d` is:
        // `A = (power_of_2 - 1) ^ X`
        // `B = X`
        // where `X` is chosen such that `((power_of_2 - 1) ^ X) ^ X = C`.
        // This equation reduces to `power_of_2 - 1 = C`.
        // This means this particular choice of A and B works only if `C` is exactly `2^d - 1`.
        // If `C = 2^d - 1`, then we want to find `A` and `B` such that `A XOR B = 2^d - 1`.
        // In this case, `A = (power_of_2 - 1) / 2` and `B = (power_of_2 - 1) / 2` plus/minus small value.
        // For C = `2^d - 1`, it means all `d` bits of C are 1.
        // This implies that for each bit position `i`, `A_i != B_i`.
        // To maximize A * B, A and B should be as close as possible.
        // So `A` should be `011...1` and `B` should be `100...0`.
        // That is, `A = (2^d / 2) - 1` and `B = 2^d / 2`.
        // For example, C = 15 (1111). d = 4. power_of_2 = 16.
        // A = 7 (0111). B = 8 (1000). A XOR B = 15. Product = 56.

        // The property is that for any `C`, the maximum product is achieved for `A` and `B` such that
        // `A | B = power_of_2 - 1` (all bits below `power_of_2` set).
        // This comes from `A XOR B = C` and `A AND B = X`.
        // `A + B = C + 2X`.
        // `A | B = (A XOR B) + (A AND B) = C + X`.
        // We want `A | B` to be `power_of_2 - 1`. This requires `X = (power_of_2 - 1) - C`.
        // This is `X = (~C) & (power_of_2 - 1)`. This is the same `and_mask` as before.
        // This is correct because if `C_i = 0`, then `A_i = B_i`. We want `A_i = B_i = 1` for `X_i = 1`.
        // If `C_i = 1`, then `A_i != B_i`. We want `X_i = 0`.
        // So, if we choose `A AND B = ((~C) & (power_of_2 - 1))`, then `A | B = C + ((~C) & (power_of_2 - 1))`.
        // Let `S = power_of_2 - 1`.
        // Then `C + ((~C) & S)` is equal to `S`.
        // This is because for each bit `i`:
        // If `C_i = 0`: `0 + ((~0)_i & S_i) = 0 + (1 & 1) = 1`. Which is `S_i`.
        // If `C_i = 1`: `1 + ((~1)_i & S_i) = 1 + (0 & 1) = 1`. Which is `S_i`.
        // So indeed `A | B = power_of_2 - 1`.
        // Now we have `A XOR B = C` and `A | B = power_of_2 - 1`.
        // We need to find `A` and `B` that satisfy these conditions and maximize `A * B`.
        // These two equations uniquely determine A and B.
        // A XOR B = C
        // A | B = S
        // From `A | B = S`, for each bit `i`:
        // if `S_i = 0`, then `A_i = 0` and `B_i = 0`.
        // if `S_i = 1`, then `A_i = 1` or `B_i = 1` or both are 1.
        // We know `S = power_of_2 - 1`, so all bits of `S` are 1 up to `d-1`.
        // So for `i < d`, `S_i = 1`. This implies `A_i` or `B_i` must be 1.
        // From `A XOR B = C`:
        // If `C_i = 0`, then `A_i = B_i`. Since `S_i = 1`, `A_i` or `B_i` must be 1.
        // So `A_i = B_i = 1`.
        // If `C_i = 1`, then `A_i != B_i`. Since `S_i = 1`, one is 0 and one is 1.
        // In summary, for bits `i < d`:
        // If `C_i = 0`, then `A_i = 1, B_i = 1`.
        // If `C_i = 1`, then `A_i = 0, B_i = 1` or `A_i = 1, B_i = 0`.
        // We want to make `A` and `B` as close as possible.
        // One way is to set `A = power_of_2 - 1` and `B = C`.
        // This does not satisfy A XOR B = C in general.
        // It has to be `A = X` and `B = C XOR X`.
        // And `X | (C XOR X) = power_of_2 - 1`.
        // The final solution usually revolves around this:
        // The optimal pair $(A, B)$ is $A = (2^d - 1) / 2$ and $B = (2^d - 1) / 2$ XOR C.
        // This doesn't make sense.

        // The correct approach is:
        // Find $d$ such that $2^d > C$. Let $K = 2^d - 1$.
        // If $C = K$, then $A$ and $B$ must have different bits at all positions where $K$ has a $1$.
        // To maximize $A \cdot B$, we choose $A = K/2$ and $B = K/2 + 1$ (if $K$ is odd) or $A = K/2$ and $B = K/2$ (if $K$ is even).
        // Since $K = 2^d - 1$, $K$ is always odd (for $d \geq 1$).
        // So, for $C = 2^d - 1$, the optimal $A = (2^d - 1)/2$ (integer division) and $B = (2^d - 1)/2 + 1$.
        // This means $A = 2^{d-1} - 1$ and $B = 2^{d-1}$.
        // Example: C = 13 (1101). $d=4$. $2^d = 16$. $K = 15 (1111)$.
        // In this case $C \ne K$.
        // A sample explanation says A = 10 (1010) and B = 7 (0111) for C=13. Product = 70.
        // A XOR B = 10 XOR 7 = 13.
        // Notice that A = 10 and B = 7. A + B = 17. A | B = 15. (A & B) = 2.
        // C + 2 * (A & B) = 13 + 2 * 2 = 17. This confirms A + B.
        // Also A | B = 15 (1111). This is $2^d - 1$.
        // This is a key insight: $A | B = 2^d - 1$.
        // If $A | B = 2^d - 1$ and $A XOR B = C$, then
        // $A = ((2^d - 1) - C)/2 + C$
        // $B = ((2^d - 1) - C)/2$
        // This is still not quite right.

        // The trick is to realize that the maximum product will be achieved when A and B have `power_of_2 - 1` as their bitwise OR.
        // So we need to find A and B such that:
        // 1. A XOR B = C
        // 2. A | B = (power_of_2 - 1)
        // 3. A * B is maximized (A and B are as close as possible).
        // From (1) and (2):
        // (A XOR B) + (A AND B) = A | B
        // C + (A AND B) = (power_of_2 - 1)
        // So, A AND B = (power_of_2 - 1) - C.
        // Let `AND_val = (power_of_2 - 1) - C`.
        // We now have two equations:
        // A XOR B = C
        // A AND B = AND_val
        // We also know A + B = (A XOR B) + 2 * (A AND B)
        // A + B = C + 2 * AND_val
        // A + B = C + 2 * ((power_of_2 - 1) - C)
        // A + B = C + 2 * (power_of_2 - 1) - 2 * C
        // A + B = 2 * (power_of_2 - 1) - C.
        // This sum `A+B` is fixed. To maximize A * B for a fixed A+B, A and B must be as close as possible.
        // Let S_target = 2 * (power_of_2 - 1) - C.
        // We have `A + B = S_target` and `A XOR B = C`.
        // To satisfy `A XOR B = C`, we need to determine the bits of A and B.
        // For each bit position `i`:
        // If `C_i = 0`: then `A_i = B_i`.
        // If `C_i = 1`: then `A_i != B_i`.
        // For `A | B = power_of_2 - 1`, implies for bits up to `d-1`, `A_i` or `B_i` must be 1.
        // If `C_i = 0`, then `A_i = B_i`. Since `A_i | B_i` must be 1, both must be 1. (`A_i=1, B_i=1`)
        // If `C_i = 1`, then `A_i != B_i`. Since `A_i | B_i` must be 1, one is 0 and one is 1. (`A_i=0, B_i=1` or `A_i=1, B_i=0`)
        // This uniquely determines A and B.
        // Let's call the constructed `A_prime` and `B_prime`.
        // Initialize `A_prime = 0`, `B_prime = 0`.
        // Iterate bits from `d-1` down to `0`.
        // For bit `i`:
        // If `(C >> i) & 1` is 0 (C_i is 0):
        // Then `A_i = B_i`. From `A | B = power_of_2 - 1` we know `A_i | B_i = 1`.
        // So `A_i = 1` and `B_i = 1`.
        // Set `A_prime |= (1LL << i)`, `B_prime |= (1LL << i)`.
        // If `(C >> i) & 1` is 1 (C_i is 1):
        // Then `A_i != B_i`. From `A | B = power_of_2 - 1` we know `A_i | B_i = 1`.
        // So one is 0 and one is 1. To make A and B as close as possible, we want them to "balance" out.
        // We can assign `A_i = 1, B_i = 0` or `A_i = 0, B_i = 1`.
        // To make A and B close, for higher bits, we want to try to make their values follow `S_target/2`.
        // This is the point where the `(power_of_2 - 1)` / 2 strategy comes in.
        // We know `A + B = 2 * (power_of_2 - 1) - C`.
        // Let `S_sum = 2 * (power_of_2 - 1) - C`.
        // We want A and B such that `A + B = S_sum` and `A XOR B = C`.
        // These two conditions uniquely determine `A` and `B` as:
        // `A = (S_sum + C) / 2`
        // `B = (S_sum - C) / 2`
        // Let's check this again:
        // `A = (2 * (power_of_2 - 1) - C + C) / 2 = 2 * (power_of_2 - 1) / 2 = power_of_2 - 1`.
        // `B = (2 * (power_of_2 - 1) - C - C) / 2 = (2 * (power_of_2 - 1) - 2 * C) / 2 = (power_of_2 - 1) - C`.
        // So the proposed solution for A and B are `power_of_2 - 1` and `(power_of_2 - 1) - C`.
        // Let's call these `A_opt = power_of_2 - 1` and `B_opt = (power_of_2 - 1) - C`.
        // Check `A_opt XOR B_opt = C`:
        // `(power_of_2 - 1) XOR ((power_of_2 - 1) - C)`.
        // Let `mask = power_of_2 - 1`.
        // `mask XOR (mask - C)`.
        // This is generally not C. For example, `mask = 15 (1111)`. `C = 13 (1101)`.
        // `A_opt = 15`. `B_opt = 15 - 13 = 2 (0010)`.
        // `A_opt XOR B_opt = 15 XOR 2 = 1111 XOR 0010 = 1101 = 13 = C`. This actually works!
        // This is a known identity in bitwise operations: `X XOR (X - Y) = Y` if `Y` is a subset of bits of `X`.
        // More generally, `X XOR (X - Y)` is complicated.
        // However, if `X` is `2^k - 1` (all bits set), then `X - Y` is `~Y` in terms of lowest `k` bits.
        // So `X XOR (X - Y)` becomes `X XOR (~Y_k)` where `Y_k` is `Y` masked to `k` bits.
        // Here `mask = power_of_2 - 1`. If `C < power_of_2`, then `(mask - C)` is `(~C) & mask`.
        // `mask XOR ( (mask - C) )`
        // `mask XOR ( (~C) & mask )`.
        // Let `A = mask`, `B = (~C) & mask`.
        // A XOR B = `mask XOR ((~C) & mask)`.
        // This simplifies. For each bit `i` up to `d-1`:
        // If `C_i = 0`: `(mask_i XOR (~C_i & mask_i)) = (1 XOR (1 & 1)) = (1 XOR 1) = 0`.
        // If `C_i = 1`: `(mask_i XOR (~C_i & mask_i)) = (1 XOR (0 & 1)) = (1 XOR 0) = 1`.
        // This means `mask XOR ( (mask - C) )` is indeed `C`!
        // This happens because for `x < 2^d`, `(2^d - 1) - x` is equivalent to `~x` considering only the lowest `d` bits.
        // So if `A = (2^d - 1)` and `B = (2^d - 1) - C`, then `A \oplus B = (2^d - 1) \oplus ((2^d - 1) - C)`.
        // Let `M = 2^d - 1`. Then $A = M$, $B = M - C$.
        // $A \oplus B = M \oplus (M - C)$.
        // For a bit $i$:
        // If $C_i = 0$: $M_i = 1$. $(M-C)_i$ will also be $1$ because subtracting $C$ won't flip $M_i$ if $C_i=0$ (assuming no borrows from higher bits affect this bit in $M-C$).
        // Actually, $M - C$ is equivalent to bitwise NOT $C$ if $C$ is considered within $d$ bits.
        // $M - C = (\sim C) \& M$.
        // So we need $M \oplus ((\sim C) \& M) = C$.
        // Let's confirm for each bit $i$:
        // If $C_i = 0$: `M_i = 1`. `((\sim C) \& M)_i = (1 \& 1) = 1`.
        // So the XOR is `1 \oplus 1 = 0`. This is $C_i$. Correct.
        // If $C_i = 1$: `M_i = 1`. `((\sim C) \& M)_i = (0 \& 1) = 0`.
        // So the XOR is `1 \oplus 0 = 1`. This is $C_i$. Correct.
        // So, the pair `A = (power_of_2 - 1)` and `B = (power_of_2 - 1) - C` indeed satisfies `A XOR B = C`.
        // And they are both less than `2^d`.
        // `A = power_of_2 - 1 < power_of_2`.
        // `B = (power_of_2 - 1) - C`. Since `C >= 1`, `B < power_of_2 - 1`, so `B < power_of_2`.
        // This pair maximizes the product. Why?
        // Because `A` is the largest possible value `(power_of_2 - 1)`
        // and `B = (power_of_2 - 1) - C`.
        // This pair represents a specific choice.
        // The problem is that A and B should be as close as possible.
        // The values `A = power_of_2 - 1` and `B = (power_of_2 - 1) - C` are not necessarily close.
        // For example, if C = 1 (0001). power_of_2 = 2. `A = 1`, `B = 0`. `1 XOR 0 = 1`. Product = 0.
        // But for C=1, $d=1$. $2^d=2$. $(A,B)$ such that $A,B < 2$. $A \oplus B = 1$.
        // Only $(A,B) = (0,1)$ or $(1,0)$. Max product is $0 \cdot 1 = 0$. This works for C=1.

        // Example: C = 13. d = 4. power_of_2 = 16. `power_of_2 - 1 = 15`.
        // Candidate A = 15. Candidate B = 15 - 13 = 2.
        // Product = 15 * 2 = 30.
        // Sample output for C=13 is 70. Our result 30 is wrong.
        // This implies my choice of `A = power_of_2 - 1` and `B = (power_of_2 - 1) - C` is incorrect.

        // The values that maximize `A * B` with `A XOR B = C` and `A, B < 2^d` are
        // `A = ((power_of_2 - 1) - C) / 2 + C`
        // `B = ((power_of_2 - 1) - C) / 2`
        // Let `X = (power_of_2 - 1) - C`.
        // These are `A = X/2 + C` and `B = X/2`.
        // This needs `X` to be even.
        // `power_of_2 - 1` is always odd.
        // If `C` is odd, then `X = (odd - odd)` is even. So `X/2` is an integer.
        // If `C` is even, then `X = (odd - even)` is odd. So `X/2` is not an integer.
        // So this formula only works if C is odd.
        // Example C = 13 (odd). power_of_2 = 16. `power_of_2 - 1 = 15`.
        // `X = 15 - 13 = 2`. `X/2 = 1`.
        // `A = 1 + 13 = 14`. `B = 1`.
        // `A XOR B = 14 XOR 1 = 1110 XOR 0001 = 1111 = 15`. Not 13. This is wrong.

        // The formula for A and B must come from:
        // A + B = S_target
        // A XOR B = C
        // Where S_target is chosen to maximize A * B.
        // The value `power_of_2 - 1` is denoted as `M`.
        // The problem is a known result. For `A \oplus B = C` and `A, B < 2^d`, where $2^d$ is the smallest power of 2 greater than $C$.
        // The optimal A and B are such that their bitwise OR is `2^d - 1`.
        // So `A | B = 2^d - 1`.
        // As derived earlier, `A AND B = (2^d - 1) - C`.
        // Now we have:
        // `A + B = (A XOR B) + 2 * (A AND B) = C + 2 * ((2^d - 1) - C)`
        // `A + B = C + 2 * (2^d - 1) - 2 * C = 2 * (2^d - 1) - C`.
        // Let `Sum_val = 2 * (power_of_2 - 1) - C`.
        // We have `A + B = Sum_val` and `A XOR B = C`.
        // We know that `A + B` and `A XOR B` determine A and B.
        // `A = (Sum_val + C) / 2`
        // `B = (Sum_val - C) / 2`
        // Substituting `Sum_val`:
        // `A = (2 * (power_of_2 - 1) - C + C) / 2 = (2 * (power_of_2 - 1)) / 2 = power_of_2 - 1`.
        // `B = (2 * (power_of_2 - 1) - C - C) / 2 = (2 * (power_of_2 - 1) - 2 * C) / 2 = (power_of_2 - 1) - C`.
        // This is exactly the pair that gave 30 for C=13. Still wrong.

        // The problem states `A, B < 2^d`. This means A and B have their MSB at position `d-1` or lower.
        // The actual solution for this problem is:
        // `A = (power_of_2 - 1) / 2`
        // `B = C XOR A`
        // Let `M = power_of_2 - 1`. This value has all d bits set to 1.
        // The specific problem states `A, B < 2^d`.
        // The solution comes from recognizing that `A = M / 2` and `B = (M / 2) ^ C`
        // gives the maximum product *if* `A` and `B` are restricted to specific forms.
        // But the common trick for `A XOR B = C` is to make `A` and `B` as close as possible.
        // If `C` is of the form `2^k - 1`, then `A = 2^{k-1} - 1` and `B = 2^{k-1}`.
        // Example: C = 13 (1101). $d=4$. $2^d = 16$. `power_of_2 - 1 = 15`.
        // Let's try `A = (power_of_2 - 1) / 2 = 15 / 2 = 7` (integer division).
        // Then `B = C XOR A = 13 XOR 7 = 1101 XOR 0111 = 1010 = 10`.
        // So for C=13, `A=7, B=10`.
        // Both are less than 16.
        // Product = 7 * 10 = 70. This matches the sample output!

        // Example: C = 10 (1010). $d=4$. $2^d = 16$. `power_of_2 - 1 = 15`.
        // `A = (power_of_2 - 1) / 2 = 15 / 2 = 7`.
        // `B = C XOR A = 10 XOR 7 = 1010 XOR 0111 = 1101 = 13`.
        // So for C=10, `A=7, B=13`.
        // Both are less than 16.
        // Product = 7 * 13 = 91. This matches the sample output!

        // This seems to be the correct "greedy" or "constructive" solution.
        // Let's formalize why `A = (power_of_2 - 1) / 2` is chosen.
        // Let `max_val = power_of_2 - 1`.
        // The numbers `A` and `B` need to be less than `2^d`.
        // This implies their `d`-th bit must be 0.
        // This means `A` and `B` can have at most `d` bits (from 0 to d-1).
        // `max_val` is `11...1` (`d` times).
        // `max_val / 2` is `011...1` (`d-1` times, then a 0 at the end from division).
        // `max_val / 2` is the largest number `X` such that `2X <= max_val`.
        // It tries to pick A as close to `max_val / 2` as possible.
        // For integer division, `(2^d - 1) / 2` is `2^{d-1} - 1`.
        // This is `011...1` (d-1 ones).
        // Let `A_chosen = (power_of_2 - 1) / 2`.
        // Then `B_chosen = C XOR A_chosen`.
        // We need to ensure `B_chosen < power_of_2`.
        // `A_chosen = 2^{d-1} - 1`. This number has the `d-1` bit as 0, and all bits from `d-2` down to 0 are 1.
        // For `C XOR A_chosen`:
        // The `d-1`-th bit of `A_chosen` is `0`.
        // If `C_{d-1}` is 0: `(C_{d-1} XOR A_{d-1}) = (0 XOR 0) = 0`. So `B_{d-1}` is 0.
        // If `C_{d-1}` is 1: `(C_{d-1} XOR A_{d-1}) = (1 XOR 0) = 1`. So `B_{d-1}` is 1.
        // If `C_{d-1}` is 1, then `B_chosen` would have its `d-1` bit set to 1.
        // Is it possible for `B_chosen >= power_of_2`?
        // `B_chosen = C XOR A_chosen`.
        // Since `A_chosen = 2^{d-1} - 1`, it has all bits 0 up to `d-2` as 1, and `d-1` bit as 0.
        // `C` can have its `d-1` bit as 0 or 1.
        // If `C_{d-1}` is 1, then `C >= 2^{d-1}`.
        // Then `B_chosen` will have `(d-1)`-th bit as 1 because `A_chosen` has it as 0.
        // If `C_{d-1}` is 0, then `B_chosen` will have `(d-1)`-th bit as 0.
        // Since `C < 2^d`, C has at most `d` bits (0 to `d-1`).
        // `A_chosen = 2^{d-1} - 1` also has at most `d` bits.
        // The XOR `C XOR A_chosen` will also have at most `d` bits.
        // So `B_chosen` will naturally be less than `2^d`.
        // The choice `A = (power_of_2 - 1) / 2` is a good candidate because it makes A approximately `2^{d-1}`.
        // And `B = C XOR A` is then symmetric around `2^{d-1}`.
        // This is a known pattern for maximizing product under XOR constraints.
        // The largest product is achieved when A and B are symmetric around `2^{d-1}` (the midpoint of `0` to `2^d - 1`).
        // Specifically, pick `A = X` and `B = X XOR C`.
        // To make `X` and `X XOR C` as close as possible, while `X < 2^d` and `X XOR C < 2^d`.
        // The best `X` is approximately `(power_of_2 / 2)`.
        // More accurately, the closest values for A and B would be around `(power_of_2 - 1) / 2`.
        // Let `X = (power_of_2 - 1) / 2`. (integer division).
        // Let `A = X`. Then `B = C XOR X`.
        // The result is `A * B`.

        long long val_A = (power_of_2 - 1) / 2; // Calculate A using integer division.
        long long val_B = C ^ val_A;           // Calculate B using XOR.

        long long max_product = val_A * val_B; // Calculate the product.

        std::cout << max_product << std::endl; // Print the maximum product.
    }
    return 0; // Indicate successful execution.
}