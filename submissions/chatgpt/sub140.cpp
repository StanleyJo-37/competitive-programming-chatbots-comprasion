#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Function to count number of 1 bits in an integer using Kernighan's algorithm
int countOnes(int n) {
    int count = 0;
    while (n) {
        n &= (n - 1); // clear the least significant bit set
        count++;
    }
    return count;
}

// Function to count number of 0 bits in an integer (excluding leading zeros)
int countZeros(int n) {
    if (n == 0) return 0; // 0 is neutral, not counted
    int zeros = 0;
    // Count bits in n
    int bits = 0;
    int temp = n;
    while (temp) {
        bits++;
        temp >>= 1;
    }
    // Number of zeros is total bits minus number of ones
    zeros = bits - countOnes(n);
    return zeros;
}

int main() {
    int n;
    // Read number of elements
    cin >> n;
    vector<int> arr(n);
    // Read the list of numbers
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    int odd_ones = 0;
    int even_zeros = 0;

    for (int num : arr) {
        if (num == 0) continue; // 0 is neutral, skip
        if (num % 2 == 1) {
            // Odd number: count 1 bits
            odd_ones += countOnes(num);
        } else {
            // Even number: count 0 bits (excluding leading zeros)
            even_zeros += countZeros(num);
        }
    }

    // Output result according to the rules
    if (odd_ones > even_zeros) {
        cout << "odds win" << endl;
    } else if (odd_ones < even_zeros) {
        cout << "evens win" << endl;
    } else {
        cout << "tie" << endl;
    }

    return 0;
}