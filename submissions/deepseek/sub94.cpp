#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    string s;
    cin >> s;

    long long total = 0;
    int i = 0;
    while (i < n) {
        int j = i;
        // Find the end of the current consecutive character block
        while (j < n && s[j] == s[i]) {
            ++j;
        }
        // If the block size is <= k, take all hits
        if (j - i <= k) {
            for (int l = i; l < j; ++l) {
                total += a[l];
            }
        } else {
            // Otherwise, take the top k hits in the block
            vector<int> temp(a.begin() + i, a.begin() + j);
            sort(temp.begin(), temp.end(), greater<int>());
            for (int l = 0; l < k; ++l) {
                total += temp[l];
            }
        }
        i = j;
    }
    cout << total << '\n';
    return 0;
}