#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool solve() {
    int n, k;
    cin >> n >> k;
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    
    // We need to check if all elements can be represented as sums of distinct powers of k.
    // The approach is to decompose each element into powers of k and ensure no power is used more than once.
    // We process each power of k from the smallest to the largest.
    
    long long max_power = 0;
    for (long long num : a) {
        if (num > 0) {
            max_power = max(max_power, num);
        }
    }
    
    // Find the maximum exponent needed to cover the largest number in the array.
    int max_exp = 0;
    if (max_power > 0) {
        while (max_power > 0) {
            max_power /= k;
            max_exp++;
        }
    }
    
    vector<bool> used(max_exp + 1, false);
    
    for (int i = 0; i < n; ++i) {
        long long num = a[i];
        int exp = 0;
        while (num > 0) {
            long long remainder = num % k;
            if (remainder > 1) {
                // If remainder is >1, it's impossible since we can only add k^i once.
                return false;
            }
            if (remainder == 1) {
                if (used[exp]) {
                    // This power was already used in another element.
                    return false;
                }
                used[exp] = true;
            }
            num /= k;
            exp++;
        }
    }
    
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    while (T--) {
        if (solve()) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    
    return 0;
}