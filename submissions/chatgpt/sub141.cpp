#include <iostream>
#include <string>
using namespace std;

// Function to convert a 32-bit unsigned integer to its IPv4 string representation
string uint32ToIP(uint32_t num) {
    // Extract each octet by shifting and masking with 0xFF (255)
    // The most significant octet is at the highest 8 bits
    string ip = to_string((num >> 24) & 0xFF) + "." +
                to_string((num >> 16) & 0xFF) + "." +
                to_string((num >> 8) & 0xFF) + "." +
                to_string(num & 0xFF);
    return ip;
}

int main() {
    // Test cases as per the problem statement
    cout << uint32ToIP(2149583361) << endl; // Output: 128.32.10.1
    cout << uint32ToIP(32) << endl;         // Output: 0.0.0.32
    cout << uint32ToIP(0) << endl;          // Output: 0.0.0.0

    // Additional test cases can be added here if needed
    return 0;
}