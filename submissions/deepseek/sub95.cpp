#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, k, x;
    cin >> n >> k >> x;
    vector<long long> a(n);
    for (auto &num : a) {
        cin >> num;
    }
    sort(a.begin(), a.end());

    vector<long long> gaps;
    for (int i = 1; i < n; ++i) {
        long long diff = a[i] - a[i-1];
        if (diff > x) {
            gaps.push_back(diff);
        }
    }
    sort(gaps.begin(), gaps.end());

    int groups = gaps.size() + 1;
    for (auto gap : gaps) {
        long long needed = (gap - 1) / x;
        if (k >= needed) {
            k -= needed;
            groups--;
        } else {
            break;
        }
    }
    cout << groups << '\n';
    return 0;
}