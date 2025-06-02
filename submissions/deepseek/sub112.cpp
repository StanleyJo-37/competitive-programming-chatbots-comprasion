#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>

using namespace std;

// Function to compute the greatest common divisor (gcd) of two numbers
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to simplify a fraction a/b to its simplest form
void simplifyFraction(int &a, int &b) {
    int common_divisor = gcd(a, b);
    a /= common_divisor;
    b /= common_divisor;
    if (b < 0) { // Ensure denominator is positive
        a = -a;
        b = -b;
    }
}

void solve() {
    int T;
    cin >> T;
    while (T--) {
        int N, K;
        cin >> N >> K;
        string S;
        cin >> S;
        
        vector<int> values;
        for (char c : S) {
            values.push_back(c - 'a' + 1); // Convert each character to its corresponding value (a=1, b=2, etc.)
        }
        
        // The problem reduces to choosing which characters to replace with their numeric values to maximize:
        // P = (letters_count) - (numbers_count) + (sum_of_numbers / K)
        // Since letters_count + numbers_count = N (total characters), we can rewrite P as:
        // P = (N - numbers_count) - numbers_count + (sum_of_numbers / K) = N - 2*numbers_count + (sum_of_numbers / K)
        // To maximize P, we need to maximize (sum_of_numbers / K - 2*numbers_count)
        // For each character, the contribution to the sum if replaced is (value / K - 2)
        // We should replace a character if (value / K - 2) > 0, i.e., value > 2*K
        
        int sum_numbers = 0;
        int numbers_count = 0;
        for (int val : values) {
            if (val > 2 * K) { // Replace if it increases P
                sum_numbers += val;
                numbers_count++;
            }
        }
        
        // Compute the maximum power P = N - 2*numbers_count + (sum_numbers / K)
        // Represent P as a fraction to handle division precisely
        int numerator = N * K - 2 * numbers_count * K + sum_numbers;
        int denominator = K;
        
        simplifyFraction(numerator, denominator);
        
        cout << numerator << " " << denominator << endl;
    }
}

int main() {
    solve();
    return 0;
}