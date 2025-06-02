#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin >> q;
    while (q--) {
        int n;
        cin >> n;
        if (n < 4) {
            // Numbers less than 4 can't be split into composite summands
            cout << "-1\n";
        } else if (n % 4 == 0) {
            // Best case: split into all 4's (4 is the smallest composite)
            cout << n / 4 << "\n";
        } else if (n % 4 == 1) {
            // Replace two 4's with one 9 (4+4+1 = 9)
            if (n >= 9) {
                cout << (n - 9) / 4 + 1 << "\n";
            } else {
                // Not possible (e.g., 5)
                cout << "-1\n";
            }
        } else if (n % 4 == 2) {
            // Replace one 4 with one 6 (4+2 = 6)
            if (n >= 6) {
                cout << (n - 6) / 4 + 1 << "\n";
            } else {
                // Not possible (e.g., 2)
                cout << "-1\n";
            }
        } else if (n % 4 == 3) {
            // Replace three 4's with two 9's (4+4+4+3 = 9+9+1, but 1 is invalid)
            // So, replace one 4 and one 9 with one 6 and one 7 (but 7 is prime)
            // Alternatively, ensure n >= 15 (4*3 + 3 = 15 → 9 + 6)
            if (n >= 15) {
                cout << (n - 15) / 4 + 2 << "\n";
            } else {
                // Not possible (e.g., 7, 11)
                cout << "-1\n";
            }
        }
    }
    return 0;
}