#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> b[i];
    }

    // Combine all points into a single array and sort them by x-coordinate.
    vector<pair<int, int>> points;
    for (int i = 0; i < n; ++i) {
        points.emplace_back(a[i], 0); // 0 indicates it's from sequence 'a'
    }
    for (int i = 0; i < n; ++i) {
        points.emplace_back(b[i], 1); // 1 indicates it's from sequence 'b'
    }
    sort(points.begin(), points.end());

    ll m;
    cin >> m;

    ll result = 1;
    int cnt_total = 0; // Total elements processed so far
    int cnt_a = 0;     // Count of elements from sequence 'a' in current group
    int cnt_b = 0;     // Count of elements from sequence 'b' in current group

    for (int i = 0; i < 2 * n; ) {
        int current_x = points[i].first;
        int j = i;
        // Process all points with the same x-coordinate
        while (j < 2 * n && points[j].first == current_x) {
            if (points[j].second == 0) {
                cnt_a++;
            } else {
                cnt_b++;
            }
            j++;
        }
        int k = j - i; // Total elements in this group
        cnt_total += k;

        // Calculate the factorial of k, but account for pairs (a_i, b_j) where a_i == b_j
        // Each such pair reduces the factorial by a factor of 2 (since they are indistinct in x)
        ll ways = 1;
        for (int l = 1; l <= k; ++l) {
            int num = l;
            // If num is even and we have at least one pair (a_i == b_j), divide by 2
            // To handle this, we count the number of such pairs and adjust the factorial accordingly
            // However, it's easier to track during the multiplication
            // So, for each pair (a_i, b_j) where a_i == b_j, the total ways is (k! / (2^p)), where p is the number of such pairs
            // But since we don't know which a_i and b_j are equal, we need to find the number of overlaps
            // However, in the current group, cnt_a and cnt_b are the counts of a's and b's with the same x
            // The number of pairs is min(cnt_a, cnt_b)
            // So, the total ways is (k! / (2^p)), where p is min(cnt_a, cnt_b)
            // So, during the multiplication of l, if l is even and p > 0, we can divide by 2 and decrement p
            // But since we don't know the order, we can precompute p and then adjust the factorial accordingly
            // So, p is the number of overlapping pairs, which is min(cnt_a, cnt_b)
            // So, the total ways is (k! / (2^p))
            // So, we can compute k! and then divide by 2^p mod m
            // But since m can be any number, we need to compute it carefully
            // So, first compute k! mod m, then compute 2^p mod m, then multiply by the modular inverse of 2^p mod m
            // But since m may not be prime, we need to handle it differently
            // Alternatively, during the multiplication of l, if l is even and p > 0, we can divide l by 2 and decrement p
            // This way, we avoid division and handle it during multiplication
            if (num % 2 == 0 && min(cnt_a, cnt_b) > 0) {
                num /= 2;
                cnt_a--;
                cnt_b--;
            }
            ways = (ways * num) % m;
        }
        result = (result * ways) % m;
        i = j;
    }

    cout << result << '\n';
    return 0;
}