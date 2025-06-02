#include <iostream>
using namespace std;

// Function to compute sXORe of n (0 XOR 1 XOR ... XOR n)
long long sXORe(long long n) {
    // The result of XOR from 0 to n follows a pattern based on n % 4:
    // If n % 4 == 0 -> result is n
    // If n % 4 == 1 -> result is 1
    // If n % 4 == 2 -> result is n + 1
    // If n % 4 == 3 -> result is 0
    if (n % 4 == 0) return n;
    if (n % 4 == 1) return 1;
    if (n % 4 == 2) return n + 1;
    return 0;
}

int main() {
    long long n;
    cin >> n;
    cout << sXORe(n) << endl;
    return 0;
}