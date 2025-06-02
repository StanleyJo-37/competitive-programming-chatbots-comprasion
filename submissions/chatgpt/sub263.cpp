#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false); // Fast IO
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        // Read the array
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }

        // Separate the array into odds and evens
        vector<int> odds, evens;
        for (int i = 0; i < n; ++i) {
            if (a[i] % 2 == 0)
                evens.push_back(a[i]);
            else
                odds.push_back(a[i]);
        }

        // If both odds and evens are sorted individually, then the answer is "Yes"
        // Because we can only swap adjacent odd-even pairs, so the relative order
        // of odds among odds and evens among evens cannot be changed.
        bool ok = true;
        for (int i = 1; i < (int)odds.size(); ++i) {
            if (odds[i] < odds[i-1]) {
                ok = false;
                break;
            }
        }
        for (int i = 1; i < (int)evens.size(); ++i) {
            if (evens[i] < evens[i-1]) {
                ok = false;
                break;
            }
        }

        if (ok)
            cout << "Yes\n";
        else
            cout << "No\n";
    }
    return 0;
}