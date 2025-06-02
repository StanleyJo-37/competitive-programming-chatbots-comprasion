#include <iostream>
#include <numeric>
#include <vector>

// Function to calculate prefix XOR sum up to n-1
long long prefix_xor_sum(long long n) {
    // The XOR sum of numbers from 0 to n-1 follows a pattern:
    // n % 4 == 0: n
    // n % 4 == 1: 1
    // n % 4 == 2: n + 1
    // n % 4 == 3: 0
    if (n % 4 == 0) {
        return n;
    } else if (n % 4 == 1) {
        return 1;
    } else if (n % 4 == 2) {
        return n + 1;
    } else { // n % 4 == 3
        return 0;
    }
}

int main() {
    // Optimize C++ standard streams for faster input/output.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t; // Read the number of test cases.
    while (t--) {
        long long a, b;
        std::cin >> a >> b; // Read MEX (a) and XOR (b) for each test case.

        // The array must contain all integers from 0 to a-1 to have MEX equal to a.
        // Let's calculate the XOR sum of these required elements.
        long long xor_sum_required = prefix_xor_sum(a);

        // We need to find additional elements such that the total XOR sum is b.
        // Let the XOR sum of the additional elements be 'target_xor_additional'.
        // xor_sum_required ^ target_xor_additional = b
        // target_xor_additional = xor_sum_required ^ b

        long long target_xor_additional = xor_sum_required ^ b;

        // Case 1: If target_xor_additional is 0.
        // This means the XOR sum of elements from 0 to a-1 already equals b.
        // In this case, we have two possibilities for the shortest length:
        //   a) Length 'a': The array [0, 1, ..., a-1] has MEX 'a' and XOR 'b'. This is a valid array.
        //   b) Length 'a + 2': We can add two elements to change the XOR sum while maintaining MEX 'a'.
        //      For example, add a large number X and X to the array. The XOR sum doesn't change
        //      (X ^ X = 0), and MEX remains 'a' if X is not in [0, a-1].
        //      This is not relevant if length 'a' works.
        //      However, if we cannot use just 'a' elements to get XOR 'b', we might need more.
        //      If xor_sum_required == b, then we have the array [0, 1, ..., a-1]. Length is 'a'.
        //      If we need to add elements, it must be because xor_sum_required != b.
        //      But if xor_sum_required == b, then the length is 'a'.
        //      Consider the case where xor_sum_required == b:
        //      The array [0, 1, ..., a-1] has MEX 'a' and XOR 'b'.
        //      The shortest length is 'a'.
        //      Example: a=1, b=1. prefix_xor_sum(1) = 1. target_xor_additional = 1 ^ 1 = 0.
        //      Output should be 3 for this example. Why? Because [0] has MEX 1 and XOR 0. We need XOR 1.
        //      So we need to add elements.
        //      The example says [0, 2020, 2021] for a=1, b=1. Length 3.
        //      This implies that if target_xor_additional is 0, and target_xor_additional is one of the existing elements (0 to a-1)
        //      OR if target_xor_additional is 'a', we need to add 2 more elements.
        //      If target_xor_additional is 0: The array [0, 1, ..., a-1] satisfies the MEX property.
        //      Its XOR sum is `xor_sum_required`.
        //      If `xor_sum_required == b`, then the array `[0, 1, ..., a-1]` has length `a`.
        //      However, the problem statement says "shortest possible length".
        //      If we can't achieve 'b' with just [0, ..., a-1], we need to add elements.
        //      Consider the values we can add: `target_xor_additional`.
        //      If `target_xor_additional == 0`: We need to add something that XORs to 0.
        //          This means we need to add two identical numbers, say `X` and `X`, such that `X != a` and `X` is not in `[0, a-1]`.
        //          For example, `[0, ..., a-1, X, X]`. This makes the length `a + 2`.
        //          This covers the `a=1, b=1` case. `prefix_xor_sum(1) = 1`. `target_xor_additional = 1 ^ 1 = 0`.
        //          The proposed length is `a + 2 = 1 + 2 = 3`. This matches the example.
        //      So, if `target_xor_additional == 0`, the length is `a + 2`.

        // Case 2: If target_xor_additional is not 0.
        // We need to add at least one element. Let this element be `target_xor_additional`.
        //   a) If `target_xor_additional == a`:
        //      This means the element `a` itself would make the XOR sum equal to `b`.
        //      However, we cannot add `a` because that would change the MEX to something greater than `a`.
        //      So, we cannot just add `a`.
        //      We need to add two elements, say `X` and `Y`, such that `X ^ Y = target_xor_additional`,
        //      and `X, Y` are not `a` and not in `[0, a-1]`.
        //      One way is to add `target_xor_additional` and `0` (if `0` is not in `[0, a-1]`, which it always is).
        //      A better way is to add `target_xor_additional ^ X` and `X`.
        //      If `target_xor_additional == a`, we have `xor_sum_required ^ a = b`.
        //      If we include `a` in the array, the MEX would be > a. We can't do that.
        //      So we can't use `a`. We need to add two distinct numbers `X` and `Y` such that `X^Y = target_xor_additional`
        //      and neither `X` nor `Y` are in `[0, a-1]` and neither is `a`.
        //      This seems to imply we need length `a + 2`.
        //      Example: a=2, b=0. prefix_xor_sum(2) = 0 ^ 1 = 1. target_xor_additional = 1 ^ 0 = 1.
        //      Here, `target_xor_additional` (1) is in `[0, a-1]` (which is `[0, 1]`).
        //      The array `[0, 1]` has MEX 2 and XOR 1. We need XOR 0.
        //      Since `target_xor_additional` (1) is already present in `[0, a-1]`, we can't just add it.
        //      If we try to add `target_xor_additional` (which is 1), the MEX changes.
        //      So, we cannot simply add `target_xor_additional` if it's already in `[0, a-1]` or if it's `a`.
        //      If `target_xor_additional` is in `[0, a-1]` (i.e., `target_xor_additional < a`):
        //          This means that `target_xor_additional` is already one of the required elements.
        //          If `xor_sum_required ^ b` is `target_xor_additional` and `target_xor_additional < a`.
        //          Then adding `target_xor_additional` (which is already present) makes the XOR sum `b`.
        //          The current array has `[0, ..., a-1]`. Its XOR sum is `xor_sum_required`.
        //          We need final XOR sum `b`.
        //          If `target_xor_additional = xor_sum_required ^ b`.
        //          If `target_xor_additional < a`, it means `target_xor_additional` is already in the array `[0, ..., a-1]`.
        //          Adding another `target_xor_additional` would make the XOR sum `b`, but `target_xor_additional`
        //          would appear twice. If `target_xor_additional` is already in the set, we cannot just add it.
        //          This would mean we need to find two new numbers, say `X` and `Y`, that are not in `[0, a-1]`
        //          and `X ^ Y = target_xor_additional`.
        //          This would result in length `a + 2`.
        //          Example: a=2, b=0. `xor_sum_required = 1`. `target_xor_additional = 1 ^ 0 = 1`.
        //          Since `1 < a` (1 < 2), this means `target_xor_additional` is already in `[0, 1]`.
        //          The array `[0, 1]` has MEX 2, XOR 1. We need XOR 0.
        //          We need to add two numbers `X, Y` such that `X^Y = 1` and `X, Y` are not `0` or `1`.
        //          Example: `[0, 1, 2, 3]` has MEX 2, XOR `0^1^2^3 = 0`. Length 4.
        //          The proposed solution is `a + 2 = 2 + 2 = 4`. This matches the logic.
        //          The example for a=2, b=0 shows output 3. This means my logic for `target_xor_additional < a` is flawed.
        //          Let's re-evaluate the states.

        // The minimum length of the array must contain `0, 1, ..., a-1`.
        // The XOR sum of these elements is `current_xor_sum = prefix_xor_sum(a)`.
        // We want the final XOR sum to be `b`.
        // So we need to add elements such that their XOR sum, when XORed with `current_xor_sum`, results in `b`.
        // Let `needed_xor = current_xor_sum ^ b`.
        //
        // Case 1: `needed_xor == 0`.
        // This means `current_xor_sum == b`.
        // The array `[0, 1, ..., a-1]` already satisfies both MEX `a` and XOR `b`.
        // So, the shortest length is `a`.
        // BUT, consider `a=1, b=1`. `prefix_xor_sum(1) = 1`. `needed_xor = 1 ^ 1 = 0`.
        // According to the above, length should be `a=1`. But example says 3.
        // Why? Because if `needed_xor == 0`, we need to add elements that XOR to 0.
        // For example, add `X` and `X`. `X` must be `a` or greater to not affect MEX.
        // Array: `[0, 1, ..., a-1, X, X]`. Length `a+2`.
        // This seems to be the correct logic for `needed_xor == 0`.
        // So if `current_xor_sum == b`, we need `a + 2` elements. This is counter-intuitive for competitive programming.
        // Let's re-read the examples carefully.
        // Example 1: a=1, b=1. Output 3. Array: [0, 2020, 2021].
        // current_xor_sum = prefix_xor_sum(1) = 1.
        // needed_xor = 1 ^ 1 = 0.
        // Here, length is `a + 2 = 1 + 2 = 3`. This matches.
        //
        // Example 2: a=2, b=1. Output 2. Array: [0, 1].
        // current_xor_sum = prefix_xor_sum(2) = 0 ^ 1 = 1.
        // needed_xor = 1 ^ 1 = 0.
        // Here, length is `a = 2`. This contradicts the `a + 2` rule for `needed_xor == 0`.
        // This means the array `[0, 1]` is valid. Its MEX is 2, XOR is 1. Both match the inputs.
        // So if `current_xor_sum == b`, the length is `a`.
        // My initial understanding for `a=1, b=1` was wrong. Why did the example provide `[0, 2020, 2021]`?
        // It says "one of the shortest arrays".
        // For a=1, b=1:
        // current_xor_sum = prefix_xor_sum(1) = 1.
        // current_xor_sum == b, so length should be 'a' = 1.
        // The array [0] has MEX 1, XOR 0. We need XOR 1. So [0] is not a solution.
        //
        // Let's reset the logic.
        // Array must contain `0, 1, ..., a-1`.
        // `current_xor_sum = prefix_xor_sum(a)`.
        // We need the final XOR sum to be `b`.
        //
        // Possibility 1: Length `a`.
        // If `current_xor_sum == b`.
        // The array `[0, 1, ..., a-1]` has MEX `a` and XOR `current_xor_sum`.
        // If `current_xor_sum == b`, then this array satisfies both conditions.
        // The length is `a`.
        // Example: a=2, b=1. `current_xor_sum = prefix_xor_sum(2) = 1`. `b=1`.
        // `current_xor_sum == b`. Output is 2. Length `a`. This matches.
        // This explains `a=2, b=1` case.

        // Possibility 2: Length `a + 1`.
        // This means we add one extra element `X` to the array `[0, 1, ..., a-1]`.
        // The array becomes `[0, 1, ..., a-1, X]`.
        // The MEX must remain `a`. This means `X` cannot be `0, 1, ..., a-1`. So `X >= a`.
        // The XOR sum will be `current_xor_sum ^ X`. This must equal `b`.
        // So, `X = current_xor_sum ^ b`.
        // For this to be a valid solution of length `a + 1`:
        // 1. `X = current_xor_sum ^ b` must be `>= a`.
        // 2. We must not have `current_xor_sum == b` (because that would make `X = 0`, which is `< a`).
        //    If `current_xor_sum == b`, then `X = 0`, which is already in `[0, a-1]`.
        //    Adding 0 would not change the XOR sum, but it would not increase the array length or change MEX.
        //    Essentially, if `current_xor_sum == b`, we are already in Case 1.
        // So, if `current_xor_sum != b` and `(current_xor_sum ^ b) >= a`, then length is `a + 1`.
        // Example: a=1, b=10000. `current_xor_sum = prefix_xor_sum(1) = 1`.
        // `b=10000`. `current_xor_sum != b`.
        // `X = 1 ^ 10000 = 10001`.
        // Is `X >= a`? `10001 >= 1`. Yes.
        // So length `a + 1 = 1 + 1 = 2`. Output is 2. This matches.
        // Example: a=2, b=10000. `current_xor_sum = prefix_xor_sum(2) = 1`.
        // `b=10000`. `current_xor_sum != b`.
        // `X = 1 ^ 10000 = 10001`.
        // Is `X >= a`? `10001 >= 2`. Yes.
        // So length `a + 1 = 2 + 1 = 3`. Output is 3. This matches.

        // Possibility 3: Length `a + 2`.
        // This happens if neither of the above two cases works.
        // This implies:
        // 1. `current_xor_sum != b` (so we need to add elements).
        // 2. `(current_xor_sum ^ b) < a` (meaning `X` would be one of `0, ..., a-1`).
        //    In this situation, if we just add `X = current_xor_sum ^ b`, it would be an element already present.
        //    This doesn't increase the array length. We need to introduce new elements.
        //    We need to add two elements, say `Y` and `Z`, such that `Y ^ Z = needed_xor`.
        //    And `Y, Z` must be `>= a` and not equal to `a`.
        //    A common strategy is to pick `Y = a` (which would change MEX, so we need to pick `Y` and `Z`
        //    such that neither is `a`, and neither is in `[0, a-1]`).
        //    Pick `Y` to be a large number (e.g., `2 * (a + b)` or something distinct).
        //    And `Z = Y ^ needed_xor`.
        //    If `Y` is chosen appropriately (e.g., `Y = 2^k` for large enough `k`),
        //    then `Y` will not be in `[0, a-1]` or equal to `a`.
        //    Then `Z` will also not be in `[0, a-1]` or equal to `a` (unless `Y^needed_xor` makes it so, which we need to avoid).
        //    The simplest way to ensure `Y, Z` don't affect MEX is to pick them very large and distinct from `a`.
        //    For example, `Y = max(a, needed_xor) + 1` and `Z = Y ^ needed_xor`. This generally works.
        //    The key is that if we need to adjust XOR sum, and the needed value `needed_xor` itself is problematic (i.e., `< a`),
        //    we can always add two new elements `X` and `Y` such that `X ^ Y = needed_xor`, and `X, Y >= a`.
        //    For example, take `X = a`. Then `Y = a ^ needed_xor`.
        //    The array would be `[0, 1, ..., a-1, a, a ^ needed_xor]`.
        //    This changes the MEX to `a+1` (if `a^needed_xor != a+1`) or more.
        //    No, this does not work for MEX.
        //    We MUST ensure that `a` is not present in the array.
        //    If we need `needed_xor`, and `needed_xor < a`, we must add two elements `X, Y` such that:
        //    1. `X, Y` are not in `[0, a-1]`.
        //    2. `X != a`.
        //    3. `Y != a`.
        //    4. `X ^ Y = needed_xor`.
        //    Let's pick `X` to be a number `K` much larger than `a` and `b`. For example, `K = 2 * (a + b) + 7`.
        //    Then `Y = K ^ needed_xor`.
        //    Since `K` is very large, and `needed_xor` is much smaller, `Y` will also be very large.
        //    Neither `X` nor `Y` will affect the MEX `a`.
        //    So the array `[0, 1, ..., a-1, K, K ^ needed_xor]` has length `a + 2`.
        //    This handles the cases where `needed_xor == 0` (where `X=K, Y=K` and length `a+2`).
        //    And cases where `needed_xor < a` and `needed_xor != 0`.
        //    Example: a=1, b=1. `current_xor_sum = 1`. `b=1`. `needed_xor = 0`. Length `a+2 = 3`. Matches example.
        //    Example: a=2, b=0. `current_xor_sum = 1`. `b=0`. `needed_xor = 1 ^ 0 = 1`.
        //    `needed_xor = 1`. Since `needed_xor < a` (1 < 2), we cannot use length `a+1`.
        //    So length `a+2 = 2+2 = 4`.
        //    The example output for a=2, b=0 is 3. My logic leads to 4. Why?
        //    For `a=2, b=0`:
        //    Array must contain `0, 1`. `XOR(0, 1) = 1`. We need XOR `0`.
        //    So `needed_xor = 1 ^ 0 = 1`.
        //    We need to add elements that XOR to `1`.
        //    If we add `X` such that `X = 1`, this is already in `[0, 1]`. Cannot add.
        //    If we add `X` such that `X >= a` (i.e. `X >= 2`) and `X = 1` (impossible).
        //    So `a+1` is not possible.
        //    Consider length `a+2`: `[0, 1, K, K^1]`.
        //    We need to find `K, K^1` such that `K != 0, 1, K^1 != 0, 1`.
        //    If we take `K = 2`, then `K^1 = 2^1 = 3`.
        //    Array: `[0, 1, 2, 3]`. MEX is 4. This fails the MEX condition (we need MEX 2).
        //    This means `K` and `K^1` must be `>= a`.
        //    And crucially, if `K = a`, then `a` is included, which changes MEX.
        //    So `K` and `K^1` must be strictly greater than `a-1`.
        //    AND `K` and `K^1` must not be `a`.
        //    This condition `X != a` for new elements is problematic.
        //    The array must contain `0, 1, ..., a-1`.
        //    The MEX value is `a`. This means `a` itself CANNOT be in the array.
        //    So any elements we add must be `>= a+1`.
        //    Let `current_xor_sum = prefix_xor_sum(a)`.
        //    Let `required_xor_value = current_xor_sum ^ b`.

        // If `required_xor_value == 0`:
        // The array `[0, 1, ..., a-1]` has XOR `b`.
        // But for `a=1, b=1`, `prefix_xor_sum(1) = 1`. `required_xor_value = 1^1 = 0`.
        // Expected output 3. `[0, 2020, 2021]`. Length `a+2`.
        // This implies that if `required_xor_value == 0`, we need `a+2` elements.
        // The array `[0, ..., a-1]` has MEX `a` and XOR `b`.
        // BUT, what if `a=1, b=1` implies something special?
        // `[0]` has MEX 1, XOR 0. We need XOR 1.
        // We cannot get XOR 1 with length 1.
        // We can get XOR 1 with length 2: `[0, X]`. `X = 0^1 = 1`.
        // But `X=1` would change MEX to 2. So `[0, 1]` is not a solution for MEX 1.
        // So length 2 is not possible.
        // So length 3: `[0, X, Y]` where `X^Y = 1`.
        // `X, Y` must be `!= 0`, `X != 1`, `Y != 1`.
        // Example: `[0, 2020, 2021]`. Here `2020^2021 = 1`. Both are not 0 or 1. MEX is 1. Length 3.
        // So for `a=1, b=1`, `needed_xor=0`, but we require `a+2` because `a` itself is 1.
        // And we cannot add `X = 0 ^ 1 = 1` because it will change the MEX.
        // This is tricky.
        // The key is that `X` must be `X >= a` to not affect MEX if it's not `a`.
        // But if `X = a`, it changes MEX.

        // Correct logic:
        // 1. Array must contain `0, 1, ..., a-1`. This takes `a` elements.
        //    The XOR sum of these `a` elements is `current_xor_sum = prefix_xor_sum(a)`.

        // 2. We need the final XOR sum to be `b`.
        //    Let `needed_val = current_xor_sum ^ b`.
        //    This `needed_val` is the XOR sum of any additional elements we must add.

        // 3. Minimum length cases:
        //    a) Length `a`: Achievable if `needed_val == 0`.
        //       This means `current_xor_sum == b`.
        //       The array `[0, 1, ..., a-1]` works.
        //       Example: `a=2, b=1`. `prefix_xor_sum(2) = 1`. `needed_val = 1 ^ 1 = 0`.
        //       Output: `a = 2`. This matches.

        //    b) Length `a + 1`: Achievable if `needed_val != 0` AND `needed_val != a`.
        //       We add one element `needed_val`.
        //       The array `[0, 1, ..., a-1, needed_val]` has length `a+1`.
        //       For this to be valid:
        //       - MEX must remain `a`. This means `needed_val` must not be in `[0, a-1]`.
        //         So `needed_val >= a`.
        //       - XOR sum must be `b`. This is satisfied by `needed_val = current_xor_sum ^ b`.
        //       So, if `needed_val != 0` AND `needed_val > a`, then length is `a + 1`.
        //       Example: `a=1, b=10000`. `prefix_xor_sum(1)=1`. `needed_val = 1 ^ 10000 = 10001`.
        //       `needed_val != 0` and `needed_val > a` (10001 > 1).
        //       Output: `a + 1 = 2`. This matches.
        //       Example: `a=2, b=10000`. `prefix_xor_sum(2)=1`. `needed_val = 1 ^ 10000 = 10001`.
        //       `needed_val != 0` and `needed_val > a` (10001 > 2).
        //       Output: `a + 1 = 3`. This matches.

        //    c) Length `a + 2`: This is the fallback case.
        //       This happens when neither `a` nor `a+1` length is possible.
        //       This means:
        //       - `needed_val == 0` (we are in case a, but it's specifically `a=1, b=1` problem)
        //         OR
        //       - `needed_val != 0` AND (`needed_val <= a`).
        //         If `needed_val < a`, then `needed_val` is already in `[0, a-1]`. Adding it won't change length.
        //         If `needed_val == a`, then adding `a` changes MEX.
        //       So if `needed_val == 0` (case a) OR `needed_val <= a` (part of case b failure), we need `a+2`.
        //       How to achieve `a+2`? Add two numbers, say `X` and `Y`, such that `X ^ Y = needed_val`.
        //       And `X, Y` are both `> a` (to not affect MEX).
        //       For example, choose `X` to be a very large number (e.g., `2^19` which is `524288`, greater than `3e5`),
        //       then `Y = X ^ needed_val`.
        //       Since `needed_val` is relatively small, `Y` will also be very large.
        //       Neither `X` nor `Y` will affect MEX, and their XOR sum is `needed_val`.
        //       Example: `a=1, b=1`. `prefix_xor_sum(1)=1`. `needed_val = 1 ^ 1 = 0`.
        //       This falls into `needed_val == 0`. Output `a+2 = 3`. This matches.
        //       Example: `a=2, b=0`. `prefix_xor_sum(2)=1`. `needed_val = 1 ^ 0 = 1`.
        //       Here `needed_val = 1`. Is `needed_val <= a`? Yes, `1 <= 2`.
        //       Output `a+2 = 4`.
        //       But the example for `a=2, b=0` has output `3`.
        //       This implies my analysis of `a+2` is still not fully correct.

        // Let's re-examine `a=2, b=0`.
        // Array must contain `0, 1`. XOR sum is `0^1 = 1`.
        // We need XOR sum `0`.
        // So we need to add elements that XOR to `1 ^ 0 = 1`.
        //
        // Try length `a=2`: `[0, 1]`. XOR is `1`. We need `0`. So length 2 not possible.
        // Try length `a+1=3`: `[0, 1, X]`. XOR is `1 ^ X`. We need `1 ^ X = 0`, so `X = 1`.
        // If we add `1`, the array becomes `[0, 1, 1]`. MEX is still 2. XOR sum is `0^1^1 = 0`.
        // This array `[0, 1, 1]` satisfies MEX 2 and XOR 0. Length 3.
        // This means `X` CAN be an element already in `[0, a-1]`.
        // But what if it's `a`? If `X = a`, then MEX changes.
        // So the rules are:
        // If `X = current_xor_sum ^ b`:
        //   - If `X = 0`, it means `current_xor_sum == b`.
        //     Array `[0, ..., a-1]` has desired XOR sum. Length `a`.
        //   - If `X > 0` AND `X < a`:
        //     `X` is already present in `[0, ..., a-1]`. Adding it again means `[0, ..., a-1, X]`.
        //     The MEX remains `a` because all `0..a-1` are present. XOR sum becomes `b`.
        //     So length `a+1`.
        //   - If `X > a`:
        //     `X` is not in `[0, ..., a-1]` and `X != a`.
        //     Array `[0, ..., a-1, X]`. MEX remains `a`. XOR sum becomes `b`.
        //     So length `a+1`.
        //   - If `X = a`:
        //     Adding `a` means `[0, ..., a-1, a]`. This changes MEX to `a+1`.
        //     This is not allowed. We need to add something else.
        //     In this case, we need to add two elements `Y, Z` such that `Y^Z = X = a`.
        //     `Y, Z` must be `> a`.
        //     e.g., `[0, ..., a-1, large_num, large_num ^ a]`. Length `a+2`.

        // Finalized Logic:
        // Calculate `current_xor_sum = prefix_xor_sum(a)`.
        // Calculate `needed_val = current_xor_sum ^ b`.

        int length;
        if (needed_val == 0) {
            // Case: XOR sum of [0, ..., a-1] is already b.
            // So [0, ..., a-1] is a valid array. Length is 'a'.
            length = a;
        } else if (needed_val > 0 && needed_val != a) {
            // Case: We need to add one element 'needed_val'.
            // If needed_val is not 'a' and is not 0 (covered by needed_val > 0),
            // we can add 'needed_val'.
            // If needed_val < a, it means needed_val is already in [0, ..., a-1].
            // Adding it again works: [0, ..., a-1, needed_val].
            // The MEX remains 'a' (all 0..a-1 are present). XOR sum becomes 'b'.
            // If needed_val > a, it means needed_val is not in [0, ..., a-1] and not 'a'.
            // Adding it works: [0, ..., a-1, needed_val].
            // The MEX remains 'a' (a is not present). XOR sum becomes 'b'.
            // So length is 'a + 1'.
            length = a + 1;
        } else { // (needed_val == a)
            // Case: We need to add 'a'.
            // If we add 'a', the array becomes [0, ..., a-1, a].
            // The MEX changes to 'a+1'. This is not allowed.
            // Therefore, we cannot just add 'a'.
            // We must add two elements, say `X` and `Y`, such that `X ^ Y = a`,
            // and neither `X` nor `Y` is `a` or in `[0, ..., a-1]`.
            // We can pick `X` to be a large number (e.g., `2^19`, a safe large number).
            // Then `Y = X ^ a`. Both `X` and `Y` will be large and distinct from `0, ..., a`.
            // So the array becomes `[0, ..., a-1, X, Y]`. This has length `a + 2`.
            length = a + 2;
        }

        std::cout << length << "\n"; // Output the shortest length.
    }
    return 0;
}