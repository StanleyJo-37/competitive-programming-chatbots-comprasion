#include <iostream>
using namespace std;

int main() {
    long long a;
    cin >> a;
    
    // The sequence of jumps is 1, 2, 3, 1, 2, 3, ... repeating.
    // The total after n full cycles (each cycle is 1+2+3=6) is 6*n.
    // The possible points after m jumps (m = 3n + k, where k is 0, 1, or 2) are:
    // - 6n (k=0)
    // - 6n + 1 (k=1, after 1-jump)
    // - 6n + 3 (k=2, after 1+2 jumps)
    // So, a must be congruent to 0, 1, or 3 modulo 6.
    // Additionally, a=0 is always reachable (starting point).
    if (a == 0 || a % 6 == 0 || a % 6 == 1 || a % 6 == 3) {
        cout << "yes" << endl;
    } else {
        cout << "no" << endl;
    }
    
    return 0;
}