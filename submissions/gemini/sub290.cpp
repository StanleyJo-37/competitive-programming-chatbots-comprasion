#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <numeric>

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    std::vector<int> pos(n + 1);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
        pos[a[i]] = i;
    }

    std::string ans(n, '0');

    // For k=1
    std::vector<bool> seen(n + 1, false);
    bool is_perm_k1 = true;
    for (int x : a) {
        if (x < 1 || x > n || seen[x]) {
            is_perm_k1 = false;
            break;
        }
        seen[x] = true;
    }
    if (is_perm_k1) {
        ans[0] = '1';
    }

    // For k=n
    bool has_one = false;
    for (int x : a) {
        if (x == 1) {
            has_one = true;
            break;
        }
    }
    if (has_one) {
        ans[n - 1] = '1';
    }

    int current_min_val = 1;
    int current_left = pos[1];
    int current_right = pos[1];

    for (int k = 2; k < n; ++k) {
        int next_val = current_min_val + 1;
        if (next_val > n) break;

        int next_pos = pos[next_val];

        int new_left = std::min(current_left, next_pos);
        int new_right = std::max(current_right, next_pos);

        if (new_right - new_left + 1 == k) {
            ans[k - 1] = '1';
            current_min_val = next_val;
            current_left = new_left;
            current_right = new_right;
        } else {
            break;
        }
    }

    std::cout << ans << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}