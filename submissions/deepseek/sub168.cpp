#include <iostream>
using namespace std;

// Function to check if a number is pretty (ends with 2, 3, or 9)
bool isPretty(int num) {
    int lastDigit = num % 10;
    return (lastDigit == 2 || lastDigit == 3 || lastDigit == 9);
}

// Precompute prefix sums of pretty numbers up to 1e5 for O(1) range queries
const int MAX = 1e5 + 5;
int prefix[MAX];

void precompute() {
    prefix[0] = 0;
    for (int i = 1; i < MAX; ++i) {
        prefix[i] = prefix[i - 1] + (isPretty(i) ? 1 : 0);
    }
}

int main() {
    // Precompute prefix sums once for all test cases
    precompute();
    
    int T;
    cin >> T;
    while (T--) {
        int L, R;
        cin >> L >> R;
        // Answer is prefix[R] - prefix[L-1] (inclusive range)
        cout << prefix[R] - prefix[L - 1] << endl;
    }
    return 0;
}