#include <iostream>
#include <string>
using namespace std;

int main() {
    int l, w;
    cin >> l >> w;

    // The minimum possible weight is l*1 = l (all 'a')
    // The maximum possible weight is l*26 (all 'z')
    if (w < l || w > l * 26) {
        cout << "impossible" << endl;
        return 0;
    }

    string res(l, 'a'); // Start with all 'a', each has weight 1
    int remaining = w - l; // The extra weight we need to distribute

    // Fill from the end to get lexicographically smallest string (optional)
    for (int i = l - 1; i >= 0 && remaining > 0; --i) {
        int add = min(25, remaining); // Max we can add to 'a' is 25 (to get to 'z')
        res[i] = 'a' + add;
        remaining -= add;
    }

    cout << res << endl;
    return 0;
}