#include <iostream>
#include <string>
using namespace std;

int main() {
    int s;
    cin >> s;

    // Arrays for number words
    string ones[] = {
        "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
        "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"
    };
    string tens[] = {
        "", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"
    };

    // For numbers less than 20, use the ones array directly
    if (s < 20) {
        cout << ones[s] << endl;
    } else {
        int t = s / 10; // tens digit
        int o = s % 10; // ones digit
        if (o == 0) {
            // Exact tens (20, 30, ..., 90)
            cout << tens[t] << endl;
        } else {
            // Numbers like 21, 32, ..., 99
            cout << tens[t] << "-" << ones[o] << endl;
        }
    }
    return 0;
}