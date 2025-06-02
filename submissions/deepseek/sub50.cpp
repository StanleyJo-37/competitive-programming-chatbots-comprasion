#include <iostream>
#include <string>

using namespace std;

string numberToWords(int s) {
    // Arrays to hold the words for numbers
    const string units[] = {
        "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
        "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen",
        "seventeen", "eighteen", "nineteen"
    };
    const string tens[] = {
        "", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"
    };

    if (s < 20) {
        return units[s];
    } else {
        int ten = s / 10;
        int unit = s % 10;
        if (unit == 0) {
            return tens[ten];
        } else {
            return tens[ten] + "-" + units[unit];
        }
    }
}

int main() {
    int s;
    cin >> s;
    cout << numberToWords(s) << endl;
    return 0;
}