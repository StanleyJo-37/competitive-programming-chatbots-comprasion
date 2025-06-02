#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<long long> a(n);
    vector<long long> prefix(n + 1, 0); // prefix[i] = sum of first i dormitories

    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        prefix[i + 1] = prefix[i] + a[i];
    }

    for (int i = 0; i < m; ++i) {
        long long b;
        cin >> b;
        // Binary search to find the smallest f where prefix[f] >= b
        int left = 1, right = n, f = n;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (prefix[mid] >= b) {
                f = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        long long k = b - prefix[f - 1];
        cout << f << " " << k << "\n";
    }

    return 0;
}