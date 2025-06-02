#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

// Structure to represent a breakfast item
struct Breakfast {
    int id; // Original index
    int a, c, l, r; // Attractiveness, Cost, Left bound, Right bound
};

// Custom comparison function for sorting by cost in descending order
bool compareBreakfasts(const Breakfast& x, const Breakfast& y) {
    return x.c > y.c;
}

int main() {
    ios_base::sync_with_stdio(false); // Optimize C++ standard streams for competitive programming
    cin.tie(NULL); // Untie cin from cout

    int T;
    cin >> T; // Read the number of test cases

    while (T--) {
        int N;
        cin >> N; // Read the number of breakfasts for the current test case

        vector<Breakfast> breakfasts(N);
        for (int i = 0; i < N; ++i) {
            breakfasts[i].id = i; // Store original index
            cin >> breakfasts[i].a >> breakfasts[i].c >> breakfasts[i].l >> breakfasts[i].r;
        }

        // Sort breakfasts by cost in descending order.
        // This is crucial because a breakfast 'j' is overshadowed if there's an 'i' such that A_i >= A_j and C_i < C_j.
        // By processing from highest cost to lowest cost, when we consider a breakfast 'j',
        // any previously processed breakfast 'i' will have C_i >= C_j.
        // The condition C_i < C_j will never be met for 'i' processed earlier than 'j' if we sort by C descending.
        // So, we need to sort by C descending to correctly identify breakfasts that *might* be overshadowed by cheaper ones later.
        sort(breakfasts.begin(), breakfasts.end(), compareBreakfasts);

        // dp[i] will store the minimum number of changes needed to make the first 'i' breakfasts
        // (after sorting by cost) valid, considering only their relative attractiveness.
        // The value stored in dp[i] will be the minimum 'A_i' needed to make the i-th breakfast valid
        // given that it's part of an optimal subsequence.
        // Or more precisely, dp will store the maximum attractiveness values that form a valid non-decreasing sequence
        // for some number of changes.
        // We are looking for the longest subsequence of breakfasts that do *not* need to be changed.
        // The problem can be rephrased: find the maximum number of breakfasts that can retain their original attractiveness
        // (or can be set to their original attractiveness within their [L, R] bounds)
        // such that for any two breakfasts i and j in this subsequence, if C_i < C_j, then A_i < A_j.
        // However, the condition for being overshadowed is A_i >= A_j and C_i < C_j.
        // If we sort by C descending, then for any breakfast 'j' we consider, any 'i' that was processed before it
        // will have C_i >= C_j.
        // To avoid 'j' being overshadowed by an 'i' with C_i < C_j, we are actually interested in the condition
        // A_i < A_j when C_i < C_j.
        // The problem statement says: "nobody takes the j^{th} breakfast if there exists at least one breakfast i such that A_{i} ≥ A_{j} and C_{i} < C_{j}."
        // This means a breakfast 'j' is "safe" if for all 'i' such that C_i < C_j, we have A_i < A_j.
        // Since we sorted by C in descending order, we iterate from highest cost to lowest.
        // When we are at breakfast 'j', any breakfast 'i' that has already been considered has C_i >= C_j.
        // So we only care about breakfasts 'i' that have C_i < C_j. These are breakfasts *after* 'j' in our sorted list.
        // This makes it a bit tricky.
        // A better approach is to consider what makes a breakfast *not* taken.
        // It's not taken if there exists 'i' such that A_i >= A_j AND C_i < C_j.
        // To make all breakfasts taken, for every 'j', for all 'i' with C_i < C_j, we must have A_i < A_j.
        // This implies that if we arrange all breakfasts in increasing order of cost, say $B_1, B_2, ..., B_N$ such that $C_{B_1} < C_{B_2} < ... < C_{B_N}$,
        // then we must have $A_{B_1} < A_{B_2} < ... < A_{B_N}$.
        // If this condition holds, no breakfast can be overshadowed. Why?
        // Suppose $B_j$ is overshadowed by $B_i$. Then $A_{B_i} \ge A_{B_j}$ and $C_{B_i} < C_{B_j}$.
        // But if $A_{B_1} < A_{B_2} < ... < A_{B_N}$ and $C_{B_1} < C_{B_2} < ... < C_{B_N}$
        // then $C_{B_i} < C_{B_j}$ implies $i < j$, which implies $A_{B_i} < A_{B_j}$.
        // This contradicts $A_{B_i} \ge A_{B_j}$.
        // So the problem reduces to finding the minimum changes to make the sequence of attractiveness values
        // strictly increasing when sorted by cost.

        // Sort by cost in ascending order for LIS approach
        sort(breakfasts.begin(), breakfasts.end(), [](const Breakfast& x, const Breakfast& y) {
            return x.c < y.c;
        });

        // The values we are interested in for LIS are the attractiveness values.
        // We need to find the longest subsequence of breakfasts (after sorting by cost)
        // such that their attractiveness values can be chosen to be strictly increasing,
        // and for each chosen breakfast, its attractiveness A_k is within [L_k, R_k].
        // If we choose to keep breakfast 'k' (i.e., not change it), its attractiveness will be A_k.
        // If we change it, its attractiveness can be any value in [L_k, R_k].
        // We want to minimize the number of changes, which is equivalent to maximizing the number of breakfasts
        // that are *not* changed.
        // This is a variation of the Longest Increasing Subsequence (LIS) problem.
        // Let dp[k] be the smallest ending attractiveness value of an increasing subsequence of length k+1.
        // We want to find the longest such subsequence using original A_i values.

        // dp will store the tails of all increasing subsequences found so far.
        // dp[i] will store the minimum A value of an increasing subsequence of length i+1.
        // Using `vector<long long>` to store values, as attractiveness can be up to 10^9.
        vector<long long> dp;

        for (int i = 0; i < N; ++i) {
            // Option 1: Don't change breakfast[i]'s attractiveness.
            // We need to find if breakfast[i].a can extend an existing increasing subsequence.
            // That is, find the largest k such that dp[k-1] < breakfast[i].a.
            // `lower_bound` finds the first element not less than breakfast[i].a.
            // If it finds an element equal to or greater than breakfast[i].a,
            // it means we can potentially replace that element (making a shorter or same length sequence with a smaller end)
            // or extend a sequence if breakfast[i].a is larger than everything currently in dp.
            auto it = lower_bound(dp.begin(), dp.end(), breakfasts[i].a);

            // If it is the end, it means breakfast[i].a is greater than all existing tail values,
            // so it can extend the longest increasing subsequence.
            if (it == dp.end()) {
                dp.push_back(breakfasts[i].a);
            } else {
                // If it's not the end, it means we found a tail value `*it` such that `*it >= breakfasts[i].a`.
                // If we replace `*it` with `breakfasts[i].a`, we get an increasing subsequence of the same length
                // but with a smaller end value, which is always better for future extensions.
                // However, this is for finding LIS based on the original values.
                // The problem is that if we don't change breakfast[i], its value *must* be A_i.
                // If we change it, its value can be in [L_i, R_i].

                // The crucial part is that if we fix A_i for some breakfast, then for any breakfast j with C_j > C_i,
                // we must ensure A_j > A_i. And for any breakfast k with C_k < C_i, we must ensure A_k < A_i.
                // This means the sequence of A values, when sorted by C, must be strictly increasing.

                // Let's re-think the DP state.
                // We want to find the longest subsequence of breakfasts (when sorted by cost in ascending order)
                // that can form a strictly increasing sequence of attractiveness values,
                // where each chosen attractiveness value 'x' for breakfast 'i' must satisfy L_i <= x <= R_i.
                // For breakfasts *not* in this subsequence, we will change their attractiveness.

                // The value `dp[k]` should represent the minimum possible *last attractiveness value*
                // for an increasing subsequence of length `k+1`.
                // When considering breakfast `i` (sorted by cost):
                // 1. If we choose to *not* change `breakfasts[i].a`:
                //    We look for the largest `k` such that `dp[k-1] < breakfasts[i].a`.
                //    If such `k` exists and `breakfasts[i].a` is within `[L_i, R_i]`,
                //    we can potentially update `dp[k]` with `breakfasts[i].a`.
                //    This is just the standard LIS.
                //    `lower_bound(dp.begin(), dp.end(), breakfasts[i].a)` gives an iterator to the first element
                //    that is >= `breakfasts[i].a`. If `breakfasts[i].a` is in `[L_i, R_i]`, we can use it.
                //    If `*it == breakfasts[i].a`, it means we found an existing sequence that ends with `breakfasts[i].a`.
                //    If `*it > breakfasts[i].a`, we can potentially shorten the end of a sequence.
                //    This `it` points to the position where `breakfasts[i].a` could be placed to maintain sorted order
                //    in `dp`. If `breakfasts[i].a` is within its allowed range `[L_i, R_i]`, we can try to
                //    use it.
                if (it == dp.end()) {
                    dp.push_back(max((long long)breakfasts[i].l, (dp.empty() ? -1 : dp.back() + 1)));
                    // This is problematic. We need to choose *a* value.
                    // If we use LIS with `dp[k]` as the smallest ending element of an increasing subsequence of length `k+1`,
                    // then for each `breakfasts[i]`:
                    // We need to find `x` such that `L_i <= x <= R_i` and `x` can extend the sequence.
                    // The optimal `x` to extend a sequence ending at `prev_val` would be `max(L_i, prev_val + 1)`.
                    // If `max(L_i, prev_val + 1) <= R_i`, then we can extend.
                    // The actual `A_i` value is irrelevant if we decide to change it.
                    // The `A_i` value is only relevant if we decide *not* to change it, in which case `x` must be `A_i`.

                    // Let's refine the LIS state. `dp[k]` stores the *minimum possible right endpoint*
                    // of an increasing subsequence of length `k+1`, where each attractiveness value `x`
                    // for breakfast `j` is chosen such that `L_j <= x <= R_j`.
                    // We want to maximize the length of such a subsequence.
                    // For each breakfast `i` (after sorting by cost):
                    // We are looking for a `prev_val` in `dp` such that we can choose `x` for `breakfasts[i]` where `x > prev_val`.
                    // The smallest `x` we can choose is `L_i`.
                    // So we are looking for `prev_val` such that `prev_val < L_i`.
                    // The `lower_bound` will find the first element `>= L_i`. If this element is `it`,
                    // it means `*it` is the smallest ending value of a sequence which `L_i` *cannot* extend.
                    // The previous element `*(it-1)` (if `it != dp.begin()`) is the largest ending value
                    // that `L_i` *can* extend.
                    // If `it == dp.begin()`, then `L_i` can start a new sequence (or extend an implicit -infinity start).

                    // We are trying to find the longest subsequence of breakfasts (sorted by cost)
                    // that can be assigned valid attractiveness values $x_1, x_2, \ldots, x_k$
                    // such that $L_{idx_j} \le x_j \le R_{idx_j}$ and $x_1 < x_2 < \ldots < x_k$.
                    // For each breakfast $i$:
                    // Let $val = L_i$. We try to place $val$ in our `dp` array.
                    // Find `it = lower_bound(dp.begin(), dp.end(), val)`.
                    // If `it` points to the end, it means `val` can extend the longest current sequence.
                    // `dp.push_back(val)`.
                    // If `it` points to an element `*it`, then `*it >= val`. We can replace `*it` with `val`
                    // if `val` is better (smaller). `*it = val`.

                    // This standard LIS with `lower_bound` works if we can pick *any* value `x` for `A_i`
                    // such that `L_i <= x <= R_i`.
                    // The smallest `x` we can pick is `L_i`.
                    // So, if we are considering breakfast `i`, and we want to extend a subsequence
                    // ending with `prev_val`, we need to pick `x` such that `max(L_i, prev_val + 1) <= R_i`.
                    // If this condition holds, the new ending value will be `max(L_i, prev_val + 1)`.
                    // We want to find the minimum such `max(L_i, prev_val + 1)` for a given length.

                    // Let `dp[len]` be the minimum possible `R_i` for an increasing subsequence of length `len+1`.
                    // This is incorrect.

                    // Let `dp[len]` be the smallest `A_k` for an increasing subsequence of length `len+1`.
                    // For each breakfast `i`:
                    // We can either:
                    // 1. Keep `A_i` unchanged.
                    //    Find `pos = lower_bound(dp.begin(), dp.end(), breakfasts[i].a) - dp.begin()`.
                    //    If `pos == 0` (starts new sequence) or `dp[pos-1] < breakfasts[i].a` (can extend),
                    //    AND `L_i <= breakfasts[i].a <= R_i`.
                    //    Then we can potentially update `dp[pos]` with `breakfasts[i].a`.
                    // 2. Change `A_i` to some `x` where `L_i <= x <= R_i`.
                    //    We want to find `x` such that `x` is as small as possible but greater than the previous element.
                    //    Find `pos = lower_bound(dp.begin(), dp.end(), breakfasts[i].l) - dp.begin()`.
                    //    If `pos == 0` or `dp[pos-1] < breakfasts[i].l`.
                    //    If we use `L_i` as the value, it might be possible.
                    //    The smallest value we can pick is `L_i`.
                    //    The largest value we can pick is `R_i`.

                    // The constraint is that if we have a subsequence of chosen breakfasts
                    // $B_{p_1}, B_{p_2}, \ldots, B_{p_k}$ sorted by cost,
                    // we must have $A'_{p_1} < A'_{p_2} < \ldots < A'_{p_k}$, where $A'_{p_j} \in [L_{p_j}, R_{p_j}]$.
                    // To maximize the length of this subsequence, for each $B_i$, we want to pick the smallest possible $A'_i$
                    // such that $A'_i > A'_{prev}$. This smallest possible value is $max(L_i, A'_{prev} + \epsilon)$.
                    // Since attractiveness can be real numbers, we can always find a value $A'_{prev} + \delta$ where $\delta > 0$
                    // and sufficiently small. So we can consider $A'_{prev} + 1$ (as they are integers, this logic applies).
                    // So we want to find $x = max(L_i, dp[pos-1] + 1)$. If $x \le R_i$, then we can extend.
                    // And we should place this $x$ into `dp`.

                    // `dp` stores the smallest possible ending value of an increasing subsequence of a given length.
                    // `dp[k]` stores the smallest $x$ such that there's an increasing subsequence of length $k+1$
                    // ending with $x$, where each element $A'_j$ in the subsequence satisfies $L_j \le A'_j \le R_j$.
                    // For each breakfast `i`:
                    // We consider placing `breakfasts[i]` into an increasing subsequence.
                    // The minimum possible value for `breakfasts[i]` is `breakfasts[i].l`.
                    // The maximum possible value for `breakfasts[i]` is `breakfasts[i].r`.

                    // Find the position `pos` where `breakfasts[i].l` could be inserted to maintain sorted order in `dp`.
                    // This `pos` indicates the length of the subsequence if `breakfasts[i].l` is used to extend it.
                    // `it = lower_bound(dp.begin(), dp.end(), breakfasts[i].l)`.
                    // If `it == dp.begin()`: `breakfasts[i].l` can start a new sequence (length 1).
                    // If `it != dp.begin()`: `prev_val = *(it - 1)`.
                    // We need `x > prev_val`. The smallest `x` for current breakfast is `max(breakfasts[i].l, prev_val + 1)`.
                    // If this `x` is `<= breakfasts[i].r`, then this breakfast can extend the subsequence.
                    // We then try to update `*it` with `x`.

                    // `temp_val` will store the attractiveness value we will try to place.
                    long long temp_val;
                    auto it_pos = lower_bound(dp.begin(), dp.end(), breakfasts[i].l);

                    if (it_pos == dp.begin()) {
                        // If breakfasts[i].l can start a new sequence or extend from -infinity
                        temp_val = breakfasts[i].l;
                    } else {
                        // It can extend a sequence ending at *(it_pos - 1)
                        long long prev_val = *(it_pos - 1);
                        temp_val = max((long long)breakfasts[i].l, prev_val + 1);
                    }

                    // Check if this `temp_val` is within the allowed range [L_i, R_i]
                    if (temp_val <= breakfasts[i].r) {
                        // If it's valid, update the `dp` array.
                        // `it_pos` is where `temp_val` should go to maintain sorted order and potentially shorten the tail.
                        // If `it_pos` is already at `dp.end()`, it means `temp_val` extends the longest subsequence.
                        if (it_pos == dp.end()) {
                            dp.push_back(temp_val);
                        } else {
                            // If `*it_pos` is greater than `temp_val`, we can update it with `temp_val`
                            // to get a shorter ending value for the same length subsequence.
                            // If `*it_pos` is already equal to `temp_val`, no change needed.
                            *it_pos = min(*it_pos, temp_val);
                        }
                    }
                }

        // The length of the longest increasing subsequence found is `dp.size()`.
        // This is the maximum number of breakfasts that do *not* need to be changed.
        // The minimum number of changes is N - `dp.size()`.

        cout << N - dp.size() << endl;
    }

    return 0;
}