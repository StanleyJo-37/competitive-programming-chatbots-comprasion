#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

int main() {
    int n, k, x;
    cin >> n >> k >> x;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    // Since k can be large (1e5), but the pattern might repeat after a certain number of operations,
    // we can find the cycle length and reduce k to k % cycle_length.
    // However, given the constraints (a_i <= 1e3), the number of unique states is limited.
    // We'll simulate until the pattern repeats or k reaches 0.
    unordered_map<string, int> seen;
    bool cycle_found = false;
    int cycle_length = 0;

    for (int op = 0; op < k; ++op) {
        sort(a.begin(), a.end());
        string state;
        for (int num : a) {
            state += to_string(num) + ",";
        }
        if (seen.count(state)) {
            cycle_length = op - seen[state];
            k = (k - op) % cycle_length;
            cycle_found = true;
            break;
        }
        seen[state] = op;

        for (int i = 0; i < n; i += 2) {
            a[i] ^= x;
        }
    }

    if (cycle_found) {
        for (int op = 0; op < k; ++op) {
            sort(a.begin(), a.end());
            for (int i = 0; i < n; i += 2) {
                a[i] ^= x;
            }
        }
    }

    sort(a.begin(), a.end());
    cout << a.back() << " " << a[0] << endl;

    return 0;
}