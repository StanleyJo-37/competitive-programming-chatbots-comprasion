#include <iostream>
using namespace std;

int main() {
    // Read the input value 'a'
    long long a;
    cin >> a;

    // The sequence of positions Chef can reach is:
    // 0, 1, 3, 6, 7, 9, 12, 13, 15, 18, ...
    // The pattern is: after every 3 jumps, the sum increases by 6 (1+2+3).
    // So, for k = 0,1,2,..., the positions are:
    // S = 6*k + offset, where offset is 0,1,3 for each cycle.

    // We need to check if there exists k >= 0 such that:
    // a == 6*k + 0
    // a == 6*k + 1
    // a == 6*k + 3

    // So, a mod 6 must be 0, 1, or 3.

    long long rem = a % 6;
    if (rem == 0 || rem == 1 || rem == 3) {
        cout << "yes" << endl;
    } else {
        cout << "no" << endl;
    }

    return 0;
}