#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        b[i] = a[i]; // Initialize b with a
    }

    int add = 0; // Total additional walks needed

    // We need to ensure that for every i (0 <= i < n-1), b[i] + b[i+1] >= k
    for (int i = 0; i < n - 1; ++i) {
        int sum = b[i] + b[i+1];
        if (sum < k) {
            int need = k - sum;
            b[i+1] += need; // Add the needed walks to the next day
            add += need;    // Accumulate the total additional walks
        }
    }

    // Output the result
    cout << add << endl;
    for (int i = 0; i < n; ++i) {
        cout << b[i] << (i == n-1 ? '\n' : ' ');
    }
    return 0;
}