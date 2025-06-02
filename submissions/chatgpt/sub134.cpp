#include <iostream>
#include <string>

// Function to check if a string represents a single digit number
bool isSingleDigit(const std::string& s) {
    return s.size() == 1;
}

// Function to convert a decimal number (as string) to binary and return the sum of its binary digits
int sumOfBinaryDigits(const std::string& num) {
    std::string n = num;
    int sum = 0;
    // While n is not zero
    while (n != "0") {
        // Get the last bit (n % 2)
        int lastBit = (n.back() - '0') % 2;
        sum += lastBit;
        // Divide n by 2 (as string)
        std::string result;
        int carry = 0;
        for (char c : n) {
            int current = carry * 10 + (c - '0');
            result += (current / 2) + '0';
            carry = current % 2;
        }
        // Remove leading zeros
        size_t pos = result.find_first_not_of('0');
        if (pos != std::string::npos)
            n = result.substr(pos);
        else
            n = "0";
    }
    return sum;
}

int main() {
    std::string n;
    std::cin >> n; // Read the input as string to handle very large numbers

    // If already a single digit, output and return
    if (isSingleDigit(n)) {
        std::cout << n << std::endl;
        return 0;
    }

    // Repeat the process until the result is a single digit
    while (true) {
        int sum = sumOfBinaryDigits(n);
        if (sum < 10) {
            std::cout << sum << std::endl;
            break;
        }
        n = std::to_string(sum);
    }
    return 0;
}