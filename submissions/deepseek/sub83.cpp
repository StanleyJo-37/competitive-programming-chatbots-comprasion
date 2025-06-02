#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    vector<int> b = a;
    int additional = 0;

    // Ensure the first day meets the condition with the day before (k walks)
    if (n >= 1) {
        int required = k - b[0];
        if (required > 0) {
            b[0] += required;
            additional += required;
        }
    }

    // Iterate through the days to ensure consecutive days meet the condition
    for (int i = 1; i < n; ++i) {
        int sum = b[i-1] + b[i];
        if (sum < k) {
            int needed = k - sum;
            b[i] += needed;
            additional += needed;
        }
    }

    cout << additional << endl;
    for (int i = 0; i < n; ++i) {
        cout << b[i] << " ";
    }
    cout << endl;

    return 0;
}