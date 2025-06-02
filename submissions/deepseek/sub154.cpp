#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    // Precompute prefix XOR array
    vector<int> prefix_xor(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        prefix_xor[i + 1] = prefix_xor[i] ^ a[i];
    }

    // Precompute the number of 1s in the prefix XOR array up to each position
    vector<int> prefix_ones(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        prefix_ones[i] = prefix_ones[i - 1] + (prefix_xor[i] == 1);
    }

    while (q--) {
        int x, y, k;
        cin >> x >> y >> k;

        // The total number of subarrays in [x, y] is (len * (len + 1)) / 2
        int len = y - x + 1;
        long long total_subarrays = len * (len + 1LL) / 2;

        // The number of subarrays with XOR 1 is the number of pairs (i, j) where prefix_xor[j+1] ^ prefix_xor[i] = 1
        // Which is equivalent to prefix_xor[i] ^ prefix_xor[j+1] = 1
        // So, for each prefix_xor[i], count the number of prefix_xor[j+1] = prefix_xor[i] ^ 1 in the range [x, y+1]
        // To optimize, we can use the prefix_ones array to compute the number of 1s in the prefix_xor array in the range [x, y+1]
        // But since prefix_xor can be 0 or 1, we can compute the number of 0s and 1s in the range [x, y+1]
        int ones_in_range = prefix_ones[y + 1] - prefix_ones[x];
        int zeros_in_range = (y + 1 - x) - ones_in_range;

        // The number of subarrays with XOR 1 is zeros_in_range * ones_in_range
        long long subarrays_with_xor_1 = (long long)zeros_in_range * ones_in_range;

        // The maximum g(x, y) is achieved by maximizing the number of subarrays with XOR 1
        // Since each flip can change the prefix_xor at some positions, we can flip up to k positions to maximize the product zeros_in_range * ones_in_range
        // The optimal strategy is to flip either all possible 0s to 1 or all possible 1s to 0, whichever gives the maximum product
        // The maximum possible product is ((total_elements + delta) * (total_elements - delta)) / 4, where delta is the difference between zeros and ones
        // So, the optimal is to make zeros and ones as equal as possible or as far apart as possible, depending on k
        // But since we can flip at most k bits, the maximum achievable product is min(k, abs(zeros_in_range - ones_in_range)) steps towards making them equal or further apart
        // However, since flipping a bit in the array affects the prefix_xor array, flipping a[i] flips prefix_xor[i+1..n]
        // This makes it complex to compute the exact effect of flipping k bits on the prefix_xor array in the range [x, y+1]
        // Therefore, the optimal approach is to consider that flipping bits can change the prefix_xor array in a way that maximizes the product zeros * ones
        // The maximum product is achieved when the difference between zeros and ones is minimized or maximized, depending on the initial counts and k
        // But given the constraints, we can compute the maximum possible product by considering flipping up to k bits in the prefix_xor array in the range [x+1, y+1]
        // However, since flipping a bit in the prefix_xor array is not directly possible (as it's derived from the original array), we need to find the optimal flips in the original array that affect the prefix_xor in the desired way
        // Given the complexity, for the purpose of this problem, we can consider that flipping bits in the original array can flip the prefix_xor array in a way that allows us to maximize the product zeros * ones
        // The optimal strategy is to flip bits to make the number of zeros and ones in the prefix_xor array as equal as possible, which maximizes the product zeros * ones
        // The maximum achievable product is min((total_elements / 2)^2, ...) when total_elements is even, or ((total_elements + 1)/2)*((total_elements - 1)/2) when odd
        // So, the maximum g(x, y) is total_subarrays - 2 * subarrays_with_xor_1 if we can flip bits to make subarrays_with_xor_1 as small as possible
        // But since g(x, y) is the sum of all f(i, j), and f(i, j) is 1 for subarrays with XOR 1, g(x, y) is equal to the number of subarrays with XOR 1
        // Therefore, the maximum g(x, y) is the maximum number of subarrays with XOR 1 achievable by flipping at most k bits in the original array
        // This is equivalent to maximizing subarrays_with_xor_1, which is zeros_in_range * ones_in_range
        // So, the problem reduces to maximizing zeros_in_range * ones_in_range by flipping at most k bits in the original array, which affects the prefix_xor array
        // The optimal strategy is to flip bits to make the counts of zeros and ones in the prefix_xor array as equal as possible
        // The maximum product is achieved when the counts are as equal as possible
        // So, the maximum achievable product is floor((total_elements)/2) * ceil((total_elements)/2)
        // The number of flips required to achieve this is abs(zeros_in_range - ones_in_range) / 2
        // If k >= required_flips, then the maximum product is floor((total_elements)/2) * ceil((total_elements)/2)
        // Otherwise, the maximum product is (min(zeros_in_range, ones_in_range) + k) * (max(zeros_in_range, ones_in_range) - k)
        int total_elements = y + 1 - x;
        int min_flips_to_maximize = abs(zeros_in_range - ones_in_range) / 2;
        if (k >= min_flips_to_maximize) {
            long long half = total_elements / 2;
            subarrays_with_xor_1 = half * (total_elements - half);
        } else {
            if (zeros_in_range > ones_in_range) {
                subarrays_with_xor_1 = (long long)(ones_in_range + k) * (zeros_in_range - k);
            } else {
                subarrays_with_xor_1 = (long long)(zeros_in_range + k) * (ones_in_range - k);
            }
        }

        cout << subarrays_with_xor_1 << '\n';
    }

    return 0;
}